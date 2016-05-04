#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "AstBuilder.h"
#include "ParsingState.h"
#include "GherkinErrorMsg.h"
#include "gherkin.tab.hpp"

class ParsingState;

struct TokenInfo
{
    TokenInfo(int n = 1, yytokentype token = INITIAL) : lineNo(n), keyword(token){}
    int lineNo;
    yytokentype keyword;
};

class GherkinParser
{
public:
    GherkinParser();

    bool parse(std::wistream& is);
    AstBuilder& astBuilder() { return m_AstBuilder; }
    bool hasErrors() { return m_GherkinErrors.size() > 0; }
    std::vector<GherkinErrorMsg>& errorMsgs() { return m_GherkinErrors; }
    void addSyntaxError();
    void addError(int lineNo, std::wstring error);
    void lastToken(int lineNo, yytokentype lastToken);
    GherkinAst::Feature* Feature() { return m_AstBuilder.Feature(); }

private:
    void printErrorMessages();

private:
    ParsingState* m_pParsingState = ParsingState::Start();
    TokenInfo m_LastToken;
    AstBuilder m_AstBuilder;
    std::vector<GherkinErrorMsg> m_GherkinErrors;
};

