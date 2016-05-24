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

#include <algorithm>    // std::swap
#include <regex>
#include "IVisitable.h"
#include "Step.h"

using namespace std;
using namespace GherkinAst;

Step::Step(StepKind stepKind, int lineNo, std::wstring* pText, GherkinAst::StepArgument* pStepArgument) :
    m_Keyword(stepKind),
    IHasLocation(lineNo),
    m_pStepArgument(pStepArgument)
{
    if (pText != nullptr)
    {
        m_Text = *pText;
    }

    delete pText;
}

Step::~Step()
{
    delete m_pStepArgument;
}

Step::Step(const Step& other) :
    IHasLocation(other),
    m_pStepArgument(nullptr),
    m_Keyword(other.m_Keyword),
    m_Text(other.m_Text)
{
    if (other.StepArgument() != nullptr)
    {
        m_pStepArgument = other.StepArgument()->copy();
    }
}

Step& Step::operator=(const Step& other)
{
    Step temp{ other };
    swap(*this, temp);
    return *this;
}

bool Step::IsAndOrButKeyWord()
{
    return (m_Keyword == StepKind::AND_STEP) ||
           (m_Keyword == StepKind::BUT_STEP);
}

wstring Step::Keyword()
{
    switch (m_Keyword)
    {
    case StepKind::GIVEN_STEP:
        return wstring(L"Given");
    case StepKind::WHEN_STEP:
        return wstring(L"When");
    case StepKind::THEN_STEP:
        return wstring(L"Then");
    case StepKind::AND_STEP:
        return wstring(L"And");
    case StepKind::BUT_STEP:
        return wstring(L"But");
    default:
        return wstring(L"*");
    }
}

bool Step::HasColumnIndexParam()
{
    wregex expr(LR"(<[^>]+>)");
    wsmatch match;

    bool res = regex_search(m_Text, match, expr, std::regex_constants::match_any);
    return res;
}

void Step::Visit(IVisitable& visitable)
{
    visitable.Accept(*this);
    if (m_pStepArgument != nullptr)
    {
        m_pStepArgument->Visit(visitable);
    }
}
