#include <regex>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Definitions.h"
#include "Comment.h"
#include "GherkinLexer.h"
#include "StrUtility.h"
#include "GherkinParser.h"

int yyparse(void);

GherkinParser* g_pParser = nullptr;
AstBuilder* g_pAstBuilder = nullptr;

//////// GherkinParser ////////
GherkinParser::GherkinParser()
{
    g_pParser = this;
    g_pAstBuilder = &m_AstBuilder;
}

bool GherkinParser::parse(std::wistream& is)
{
    GherkinLexer lexer(is, *this);  // initialize global lexer,
    (void)lexer;                    // which is defined in GherkinLexer.cpp

    m_GherkinErrors.clear();
    m_LastToken = TokenInfo();
    m_pParsingState = ParsingState::Start();
    
    int result = 0;
    try
    {
        result = yyparse();
    }
    catch (GherkinError& ex)
    {
        for (GherkinErrorInfo& err : ex.AllErrors())
            addError(err.LineNo, err.ErrorMsg);
    }
    catch (std::exception& ex)
    {
        wstring err = StrUtility::string2wstring(ex.what());
        addError(yylloc.first_line, wstring(L"Internal fatal error: " + err));
    }
    catch (...)
    {
        addError(yylloc.first_line, wstring(L"Unknown internal fatal error!"));
    }

    printErrorMessages();

    return ( (result == 0) && (m_GherkinErrors.size() == 0) );
}

void GherkinParser::lastToken(int lineNo, yytokentype token)
{
    m_LastToken = TokenInfo(lineNo, token);
    m_pParsingState = m_pParsingState->tokenScanned(token);
}

void GherkinParser::addSyntaxError()
{
    std::wstring msg = L"Syntax error: ";
    msg.append(m_pParsingState->expectation());

    addError(m_LastToken.lineNo, msg);
}

void GherkinParser::addError(int lineNo, std::wstring error)
{
    m_GherkinErrors.push_back(GherkinErrorMsg(lineNo, error));
}

void GherkinParser::printErrorMessages()
{
#if false
    for (GherkinErrorMsg& error : m_GherkinErrors)
    {
        std::cout << "line(" << error.lineNo() << "): ";
        std::wcout << error.errorMsg() << std::endl;
    }
#endif
}


