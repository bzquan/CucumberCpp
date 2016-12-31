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

#include "BDDUtil.h"
#include "BDDStepBuilder.h"
#include "BDDStepImplBuilderContext.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

vector<BDDStepBuilder*> BDDStepImplBuilderContext::s_StepBuilderList;
vector<BDDStepBuilder*> BDDStepImplBuilderContext::s_NonDuplicateStepBuilderList;
wstring BDDStepImplBuilderContext::s_FeatureTitle;
BDDUnicodeNameDefinitions BDDStepImplBuilderContext::s_UnicodeNameDefinitions;

void BDDStepImplBuilderContext::Clear()
{
    for (BDDStepBuilder* pStepBuilder : s_StepBuilderList)
    {
        delete pStepBuilder;
    }
    s_StepBuilderList.clear();
    s_NonDuplicateStepBuilderList.clear();
    s_FeatureTitle = wstring();
    s_UnicodeNameDefinitions.Clear();
}

vector<BDDStepBuilder*>& BDDStepImplBuilderContext::StepBuilders()
{
    return s_StepBuilderList;
}

wstring BDDStepImplBuilderContext::FeatureTitle()
{
    return s_FeatureTitle;
}

void BDDStepImplBuilderContext::FeatureTitle(std::wstring title)
{
    s_FeatureTitle = title;
}

wstring BDDStepImplBuilderContext::StepImplClassName()
{
    return ToIdentifier(s_FeatureTitle) + L"_Steps";
}

wstring BDDStepImplBuilderContext::StepHeaderFileName()
{
    return StepImplClassName() + L".h";
}

wstring BDDStepImplBuilderContext::StepImplementationFileName()
{
    return StepImplClassName() + L".cpp";
}

wstring BDDStepImplBuilderContext::StepModelTemplateHeaderFileName()
{
    return FeatureTestModelName() + L".h";
}

wstring BDDStepImplBuilderContext::StepModelTemplateImplFileName()
{
    return FeatureTestModelName() + L".cpp";
}

wstring BDDStepImplBuilderContext::FeatureTestModelName()
{
    return ToIdentifier(s_FeatureTitle) + L"_TestModel";
}

BDDStepBuilder* BDDStepImplBuilderContext::CreateNewStepBuilder(GherkinAst::Step& step)
{
    BDDStepBuilder* pNewStepBuilder = new BDDStepBuilder(step, StepImplClassName());
    s_StepBuilderList.push_back(pNewStepBuilder);
    return pNewStepBuilder;
}

vector<BDDStepBuilder*>& BDDStepImplBuilderContext::NonDuplicateStepBuilders()
{
    MakeNonDuplicateStepBuilders();
    return s_NonDuplicateStepBuilderList;
}

void BDDStepImplBuilderContext::AppendName(std::wstring name)
{
    s_UnicodeNameDefinitions.Append(name);
}

std::wstring BDDStepImplBuilderContext::GetUnicodeNameDefines()
{
    return s_UnicodeNameDefinitions.GetDefines();
}

void BDDStepImplBuilderContext::MakeNonDuplicateStepBuilders()
{
    if (s_NonDuplicateStepBuilderList.size() == 0)
    {
        for (BDDStepBuilder* pStepBuilder : s_StepBuilderList)
        {
            BDDStepBuilder* sameStepBuilder = GetSameStepBuilder(pStepBuilder);
            if (sameStepBuilder == nullptr)
            {
                s_NonDuplicateStepBuilderList.push_back(pStepBuilder);
                sameStepBuilder = pStepBuilder;
            }

            sameStepBuilder->AddStepComments(pStepBuilder->StepText());
        }
    }
}

BDDStepBuilder* BDDStepImplBuilderContext::GetSameStepBuilder(BDDStepBuilder* pNewStepBuilder)
{
    wstring stepFuncHeader = BDDUtil::TrimWhiteSpaces(pNewStepBuilder->BuildStepHeader());
    for (BDDStepBuilder* pStepBuilder : s_NonDuplicateStepBuilderList)
    {
        wstring tmpStepFuncHeader = BDDUtil::TrimWhiteSpaces(pStepBuilder->BuildStepHeader());
        if (stepFuncHeader == tmpStepFuncHeader)
        {
            return pStepBuilder;
        }
    }

    return nullptr;
}

wstring BDDStepImplBuilderContext::ToIdentifier(const std::wstring& str)
{
    return BDDUtil::MakeIdentifier(str);
}
