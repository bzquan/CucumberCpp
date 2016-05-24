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

#include "Feature.h"
#include "BDDStepImplBuilderContext.h"
#include "BDDExecSpecGenerator.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

BDDExecSpecGenerator::BDDExecSpecGenerator()
{
    m_FeatureBuilder = std::make_unique<BDDFeatureBuilder>();
    m_StepImplBuilderManager = std::make_unique<BDDStepImplBuilderManager>();
    m_BDDASTVisitor = std::make_unique<BDDASTVisitor>(*m_FeatureBuilder.get(), *m_StepImplBuilderManager.get());
}

void BDDExecSpecGenerator::GenExecSpec(Feature* pFeature)
{
    BDDStepImplBuilderContext::Clear();
    if ((pFeature != nullptr) && (m_BDDASTVisitor != nullptr))
    {
        BDDASTVisitor* pVisitor = m_BDDASTVisitor.get();
        pFeature->Visit(*pVisitor);
    }
}

wstring BDDExecSpecGenerator::StepHeaderFileName()
{
    return BDDStepImplBuilderContext::StepHeaderFileName();
}

wstring BDDExecSpecGenerator::StepImplFileName()
{
    return BDDStepImplBuilderContext::StepImplementationFileName();
}

wstring BDDExecSpecGenerator::StepModelTemplateHeaderFileName()
{
    return BDDStepImplBuilderContext::StepModelTemplateHeaderFileName();
}

wstring BDDExecSpecGenerator::StepModelTemplateImplFileName()
{
    return BDDStepImplBuilderContext::StepModelTemplateImplFileName();
}

wstring BDDExecSpecGenerator::FeatureFileName()
{
    return m_FeatureBuilder->FeatureFileName();
}

wstring BDDExecSpecGenerator::StepDefsHeader()
{
    return m_StepImplBuilderManager->BuildStepImplHeader();
}

wstring BDDExecSpecGenerator::StepDefsImpl()
{
    return m_StepImplBuilderManager->BuildStepImplCpp();
}

wstring BDDExecSpecGenerator::StepModelTemplateHeader()
{
    return m_StepImplBuilderManager->BuildTestModelHeader();
}
wstring BDDExecSpecGenerator::StepModelTemplateImpl()
{
    return m_StepImplBuilderManager->BuildTestModelImplementation();
}

wstring BDDExecSpecGenerator::FeatureImpl()
{
    m_FeatureBuilder->StepHeaderFileName(StepHeaderFileName());
    m_FeatureBuilder->StepClassName(BDDStepImplBuilderContext::StepImplClassName());
    return m_FeatureBuilder->Build();
}
