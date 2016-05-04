#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Definitions.h"
#include "YYTableParam.h"

#include "gherkin.tab.hpp"

struct Token
{
    Token() = default;
    Token(yytokentype t, std::wstring v, int currentLineNo, std::wstring vtype = std::wstring());

    yytokentype token = DECRIPTION;
    std::wstring yylval;
    int lineNo = 1;
    std::wstring type;
};

class GherkinParser;

class GherkinLexer
{
public:
    GherkinLexer(std::wistream& is, GherkinParser& parser);
    Token yylex();
    bool parse();

    void yyerror(char const* msg);
    void lyyerror(YYLTYPE loc, const char* err_msg);

private:
    std::wstring getLine();
    std::wstring getLineCRLF();
    void rewind();
    Token match(const std::wstring& line, int index);
    int getMatchedKeywordIndex(const std::wstring& line);
    bool isTableRow(const std::wstring& line);
    bool isDocStringSeparator(const std::wstring& line, std::wstring& type);
    bool isCommentLine(const std::wstring& line);
    Token scanDocString(const std::wstring& docStringType);
    Token scanDescription(const std::wstring& text);
    std::wstring skipEmptyLines();
    std::wstring createDescText(std::vector<std::wstring>& desc);

private:
    std::wistream& m_istream;
    std::streamoff m_seekPos = 0;
    size_t m_lineNo = 0;
    GherkinParser& m_Parser;
};

