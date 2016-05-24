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

#include "BDDStepImplBuilderContext.h"
#include "BDDStepImplHeaderBuilder.h"
#include "BDDStepImplCppBuilder.h"
#include "BDDTestModelBuilder.h"
#include "BDDStepImplBuilderManager.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

void BDDStepImplBuilderManager::FeatureTitle(wstring title)
{
    BDDAbstractBuilder::FeatureTitle(title);
    BDDStepImplBuilderContext::FeatureTitle(title);
}

BDDStepBuilder* BDDStepImplBuilderManager::NewStep(Step& step)
{
    m_pCurrentStep = BDDStepImplBuilderContext::CreateNewStepBuilder(step);
    return m_pCurrentStep;
}

void BDDStepImplBuilderManager::AddArg(DataTable* pDdataTable)
{
    if (m_pCurrentStep != nullptr)
    {
        m_pCurrentStep->TableArg(pDdataTable);
    }
}

void BDDStepImplBuilderManager::AddArg(DocString* pDocString)
{
    if (m_pCurrentStep != nullptr)
    {
        m_pCurrentStep->DocStringArg(pDocString);
    }
}

wstring BDDStepImplBuilderManager::BuildStepImplHeader()
{
    return BDDStepImplHeaderBuilder::BuildStepImplHeader();
}

wstring BDDStepImplBuilderManager::BuildStepImplCpp()
{
    return BDDStepImplCppBuilder::BuildStepImplCpp();
}

wstring BDDStepImplBuilderManager::BuildTestModelHeader()
{
    return BDDStepModelTemplateBuilder::BuildTestModelHeader();
}

wstring BDDStepImplBuilderManager::BuildTestModelImplementation()
{
    return BDDStepModelTemplateBuilder::BuildTestModelImplementation();
}
