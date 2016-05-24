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

#include <vector>
#include <string>
#include <stdexcept>

constexpr auto TAG_LINE_REGEX{ LR"(^\s*(@.+)+$)" };
constexpr auto NEWLINE{ L"\n" };

namespace GherkinAst
{
    enum class StepKind {
        GIVEN_STEP,
        WHEN_STEP,
        THEN_STEP,
        AND_STEP,
        BUT_STEP
    };

    class Location;
    class Language;
    class Step;
    class Tag;
    class StepArgument;
    class Example;
    class IHasDescription;
    class ScenarioDefinition;
    class Comment;
}

struct TableParam;

struct GherkinErrorInfo
{
    GherkinErrorInfo(int lineNo = 1, std::wstring errMsg = L"Error") :
        LineNo(lineNo),
        ErrorMsg(errMsg) {}

    int LineNo;
    std::wstring ErrorMsg;
};

class GherkinError : public std::domain_error
{
public:
    GherkinError() :
        domain_error("Error")
    {
    }

    GherkinError(int lineNo, std::wstring errMsg) :
        domain_error("Error")
    {
        append(lineNo, errMsg);
    }

    void append(int lineNo, std::wstring errMsg)
    {
        m_Errors.push_back(GherkinErrorInfo(lineNo, errMsg));
    }
    std::vector<GherkinErrorInfo>& AllErrors() { return m_Errors; }

private:
    std::vector<GherkinErrorInfo> m_Errors;
};
