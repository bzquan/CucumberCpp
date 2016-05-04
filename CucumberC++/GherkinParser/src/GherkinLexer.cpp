#include <regex>
#include <algorithm>

#include "StrUtility.h"
#include "Comment.h"
#include "YYTableParam.h"
#include "AstBuilder.h"
#include "GherkinParser.h"
#include "Definitions.h"
#include "GherkinLexer.h"

extern YYSTYPE yylval;

using namespace std;
using namespace GherkinAst;

namespace {
    wstring g_eof{ L"$$$EOF$$$" };

    struct RegexAndTag
    {
        wstring     regex;
        yytokentype token;
        size_t      valIndex;
    };
    vector<RegexAndTag> g_tokens{
        { LR"(^\s*(#\s*language:\s*)([a-z]{2}))", LANGUAGE, 2 },           // # language: en
        { TAG_LINE_REGEX, TAG_LINE, 0 },                                   // @tag1 @tag2
        { LR"(^\s*Feature\s*:(.+))", FEATURE_LINE, 1 },                    // Feature: feature title
        { LR"(^\s*Background\s*:(.*))", BACKGROUND_LINE, 1 },              // Background: [title]
        { LR"(^\s*Examples\s*:(.*))", EXAMPLE_LINE, 1 },                   // Examples: [title]
        { LR"(^\s*Scenario\s*:(.+))", SCENARIO_LINE, 1 },                  // Scenario: title
        { LR"(^\s*Scenario Outline\s*:(.+))", SCENARIO_OUTLINE_LINE, 1 },  // Scenario Outline: title
        { LR"(^\s*Given\s+(.+))", GIVEN_STEP, 1 },                         // Given a precondition
        { LR"(^\s*When\s+(.+))", WHEN_STEP, 1 },                           // When an action
        { LR"(^\s*Then\s+(.+))", THEN_STEP, 1 },                           // Then expectation
        { LR"(^\s*And\s+(.+))", AND_STEP, 1 },                             // And a step
        { LR"(^\s*But\s+(.+))", BUT_STEP, 1 },                             // But a step
    };
}

Token::Token(yytokentype t, std::wstring v, int currentLineNo, std::wstring vtype) :
    token(t),
    lineNo(currentLineNo)
{
    yylval = (token != DECRIPTION) ? StrUtility::Trim(v) : v;
    type = StrUtility::Trim(vtype);
}

namespace
{
    GherkinLexer* g_GherkinLexer = nullptr;
}

GherkinLexer::GherkinLexer(std::wistream& is, GherkinParser& parser) :
    m_istream(is),
    m_Parser(parser)
{
    g_GherkinLexer = this;
    yylval.pwstr = nullptr;
}

Token GherkinLexer::yylex()
{
    wstring line = skipEmptyLines();

    if (line == g_eof)
        return Token(YYEOF_TOKEN, wstring(), m_lineNo);
        
    wstring docStringType;
    if (isDocStringSeparator(line, docStringType))
    {
        Token token = scanDocString(docStringType);
        m_Parser.lastToken(token.lineNo, token.token);
        return token;
    }
            
    int index = getMatchedKeywordIndex(line);
    if (index >= 0)
    {
        Token token = match(line, index);
        m_Parser.lastToken(token.lineNo, token.token);
        return token;
    }

    if (isTableRow(line))
    {
        m_Parser.lastToken(m_lineNo, TABLE_ROW);
        return Token(TABLE_ROW, StrUtility::Trim(line), m_lineNo);
    }

    if (isCommentLine(line))
    {
        m_Parser.astBuilder().addComment(Comment(m_lineNo, line));
        return yylex(); // scan recursively
    }

    Token token = scanDescription(line);
    m_Parser.lastToken(token.lineNo, token.token);
    return token;
}

wstring GherkinLexer::skipEmptyLines()
{
    wstring line = getLine();
    while ((line != g_eof) && (line.length() == 0))
    {
        line = getLine();
    }
    return line;
}

Token GherkinLexer::match(const std::wstring& line, int index)
{
    RegexAndTag& token = g_tokens[index];
    wregex wideMatch(token.regex);
    wsmatch match;
    if (regex_match(line, match, wideMatch))
    {
        return Token(token.token, match[token.valIndex], m_lineNo);
    }
    return Token();
}

int GherkinLexer::getMatchedKeywordIndex(const std::wstring& line)
{
    wregex wideMatch;
    wsmatch match;
    for (size_t i = 0; i < g_tokens.size(); i++)
    {
        wideMatch.assign(g_tokens[i].regex);
        if (regex_match(line, match, wideMatch)) return i;
    }
    return -1;
}

bool GherkinLexer::isTableRow(const std::wstring& line)
{
    wstring text = StrUtility::Trim(line);
    return ((text.length() > 1) && (text[0] == L'|') && (text[text.length() - 1] == L'|'));
}

bool GherkinLexer::isCommentLine(const std::wstring& line)
{
    wregex wideMatch(LR"(^\s*(#|//).*)");
    wsmatch match;
    return regex_match(line, match, wideMatch);
}

bool GherkinLexer::isDocStringSeparator(const std::wstring& line, std::wstring& type)
{
    wregex wideMatch(LR"(^\s*"""(.*))");
    wsmatch match;
    const bool res = regex_match(line, match, wideMatch);
    if (res) type = match[1];

    return res;
}

Token GherkinLexer::scanDocString(const std::wstring& docStringType)
{
    const int lineNo = m_lineNo;
    wstring docString;
    wstring dummyDocStringType;
    wstring line = getLine();
    while ((line != g_eof) && !isDocStringSeparator(line, dummyDocStringType))
    {
        if (docString.length() > 0) docString.append(NEWLINE);
        docString.append(StrUtility::Trim(line));
        line = getLine();
    }
    
    return Token(DOC_STRING, docString, lineNo, docStringType);
}

Token GherkinLexer::scanDescription(const std::wstring& text)
{
    const int lineNo = m_lineNo;
    vector<wstring> desc;
    desc.push_back(StrUtility::TrimEnd(text));

    wstring line = getLine();
    while ((line != g_eof) && (getMatchedKeywordIndex(line) < 0))
    {
        desc.push_back(StrUtility::TrimEnd(line));
        line = getLine();
    }
    if (line != g_eof) rewind();

    wstring descText = createDescText(desc);
    return Token(DECRIPTION, descText, lineNo);
}

wstring GherkinLexer::createDescText(vector<wstring>& desc)
{
    size_t empty_lines = 0;
    for (size_t i = desc.size() - 1; i > 0; i--)
    {
        if (desc[i].length() > 0)
            break;
        else
            empty_lines++;
    }

    wstring descText;
    const size_t line_count = desc.size() - empty_lines;
    for (size_t i = 0; i < line_count; i++)
    {
        descText.append(desc[i]);
        const bool is_not_last_line = (line_count > 0) && (i < line_count - 1);
        if (is_not_last_line)
            descText.append(NEWLINE);
    }
    return descText;
}

std::wstring GherkinLexer::getLine()
{
    extern YYLTYPE yylloc;

    if (!m_istream.eof())
    {
        m_lineNo++;
        yylloc.first_line = m_lineNo;
        m_seekPos = m_istream.tellg();

        return getLineCRLF();
    }
    else
    {
        return g_eof;
    }
}

std::wstring GherkinLexer::getLineCRLF()
{
    std::wstring line;
    std::getline(m_istream, line);
    if (line.size() > 0 && line[line.size() - 1] == L'\r')
        line.erase(line.size() - 1);

    return StrUtility::TrimEnd(line);
}

void GherkinLexer::rewind()
{
    m_istream.seekg(m_seekPos);
    if (m_lineNo > 0) m_lineNo--;
}

int yylex(void)
{
    extern YYSTYPE yylval;

    Token token = g_GherkinLexer->yylex();
    if (token.token != YYEOF_TOKEN)
    {
        if (token.token != DOC_STRING)
            yylval.pwstr = new wstring(token.yylval);
        else
        {
            yylval.pDocStringParam = new DocStringParam(token.yylval, token.type);
        }
        return static_cast<int>(token.token);
    }
    else
    {
        const int YYEOF = 0; // defined in gherkin.tab.cpp

        yylval.pwstr = nullptr;
        return YYEOF;
    }
}

