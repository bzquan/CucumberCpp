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

