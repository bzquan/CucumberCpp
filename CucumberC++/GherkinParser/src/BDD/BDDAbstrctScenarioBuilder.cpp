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

#include <algorithm>
#include <QDebug>
#include "Tag.h"
#include "BDDStepBuilder.h"
#include "BDDUtil.h"
#include "BDDAbstrctScenarioBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

void BDDAbstrctScenarioBuilder::AddScenarioStep(BDDStepBuilder* pStepBuilder)
{
    const wchar_t* MOCK_ATTR{L"[[mock]]"};
    if (pStepBuilder->HasAttribute(MOCK_ATTR))
    {
        InsertAtBegining(pStepBuilder, MOCK_ATTR);
    }
    else
    {
        m_StepBuilderList.push_back(pStepBuilder);
    }
}

void BDDAbstrctScenarioBuilder::InsertAtBegining(BDDStepBuilder* pStepBuilder, const wchar_t* attr)
{
    auto step_with_mock_attr = [&attr](BDDStepBuilder* pParam) { return pParam->HasAttribute(attr); };
    list<BDDStepBuilder*>::reverse_iterator iter = std::find_if(m_StepBuilderList.rbegin(), m_StepBuilderList.rend(), step_with_mock_attr);
    if (iter != m_StepBuilderList.rend())
    {
        m_StepBuilderList.insert(iter.base(), pStepBuilder);
    }
    else
    {
        m_StepBuilderList.push_front(pStepBuilder);
    }
}

wstring BDDAbstrctScenarioBuilder::BuildGUIDTag()
{
    if (m_ScenarioTags.size() > 0)
    {
        auto isGUID = [](Tag& tag) { return tag.IsGUID(); };
        vector<Tag>::iterator iter = std::find_if(m_ScenarioTags.begin(), m_ScenarioTags.end(), isGUID);
        if (iter != m_ScenarioTags.end())
        {
            Tag guidTag = *iter;
            return wstring(L"Spec(\"") + guidTag.Name() + L"\");";
        }
    }

    return L"Spec(\"GUID has not been defined!\");";
}

wstring BDDAbstrctScenarioBuilder::BuildSteps(wstring indent)
{
    wstring stepOfScenario;
    for (BDDStepBuilder* pStepBuilder : m_StepBuilderList)
    {
        stepOfScenario
            .append(pStepBuilder->BuildStepForScenario(indent))
            .append(BDDUtil::NEW_LINE);
    }

    return stepOfScenario;
}

void BDDAbstrctScenarioBuilder::MakeTableAndDocStringSeqNo()
{
    int tableSeqNo = 0;
    int docStringSeqNo = 0;
    for (BDDStepBuilder* pStepBuilder : m_StepBuilderList)
    {
        if (pStepBuilder->TableArg() != nullptr)
        {
            pStepBuilder->TableSeqNo(tableSeqNo++);
        }
        if (pStepBuilder->DocStringArg() != nullptr)
        {
            pStepBuilder->DocStringSeqNo(docStringSeqNo++);
        }
    }
}

