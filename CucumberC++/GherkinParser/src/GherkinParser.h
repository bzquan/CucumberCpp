/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

