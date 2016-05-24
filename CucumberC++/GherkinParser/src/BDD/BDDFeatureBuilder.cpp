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

#include "Scenario.h"
#include "Example.h"
#include "BDDUtil.h"
#include "BDDScenarioBuilder.h"
#include "BDDScenarioOutlineBuilder.h"
#include "BDDStepBuilder.h"
#include "BDDFeatureBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

BDDFeatureBuilder::~BDDFeatureBuilder()
{
    for (BDDAbstrctScenarioBuilder* pBuilder : m_ScenarioBuilderList)
    {
        delete pBuilder;
    }

    m_ScenarioBuilderList.clear();
}

wstring BDDFeatureBuilder::FeatureFileName()
{
    return FeatureTitle() + L"_Feature.cpp";
}

wstring BDDFeatureBuilder::Build()
{
    m_featureImpl.clear();
    m_featureImpl
        .append(DisableWarning_C4819())
        .append(BDDUtil::NEW_LINE)
        .append(BuildIncludes())
        .append(BDDUtil::NEW_LINE)
        .append(BuildFeatureTestClass())
        .append(BDDUtil::NEW_LINE)
        .append(BuildScenarioes())
        .append(BDDUtil::NEW_LINE);


    return m_featureImpl;
}

void BDDFeatureBuilder::CreateBackgound()
{
    m_pCurrentScenarioBuilder = &m_BackgoundBuilder;
}

void BDDFeatureBuilder::NewScenario(Scenario& scenario)
{
    AddNewScenario(new BDDScenarioBuilder(scenario));
}

void BDDFeatureBuilder::NewScenarioOutline(ScenarioOutline& scenarioOutline)
{
    AddNewScenario(new BDDScenarioOutlineBuilder(scenarioOutline));
}

void BDDFeatureBuilder::NewExamples(Example& example)
{
    BDDScenarioOutlineBuilder* pScenarioOutlineBuilder = dynamic_cast<BDDScenarioOutlineBuilder*>(m_pCurrentScenarioBuilder);
    if (pScenarioOutlineBuilder != nullptr)
    {
        pScenarioOutlineBuilder->AddExamples(example);
    }
}

void BDDFeatureBuilder::AddNewScenario(BDDAbstrctScenarioBuilder* pScenarioBuilder)
{
    pScenarioBuilder->FeatureClassName(FeatureClassName());
    pScenarioBuilder->ScenarioTags(m_ScenarioTags);
    m_ScenarioBuilderList.push_back(pScenarioBuilder);

    m_pCurrentScenarioBuilder = pScenarioBuilder;
    m_ScenarioTags.clear();
}

void BDDFeatureBuilder::AddScenarioStep(BDDStepBuilder* pStepBuilder)
{
    if (m_pCurrentScenarioBuilder != nullptr)
    {
        m_pCurrentScenarioBuilder->AddScenarioStep(pStepBuilder);
    }
}

wstring BDDFeatureBuilder::DisableWarning_C4819()
{
    wstring disable_warning;
    disable_warning
        .append(L"#ifdef WIN32\n")
        .append(L"// Disable warning C4819: The file contains a character that cannot be represented in the current code page\n")
        .append(L"#pragma warning(disable : 4819)\n")
        .append(L"// Disable warning C4800: 'int' : forcing value to bool 'true' or 'false'(performance warning)\n")
        .append(L"#pragma warning(disable : 4800)\n")
        .append(L"#endif\n");

    return disable_warning;
}

wstring BDDFeatureBuilder::BuildIncludes()
{
    wstring includes;
    includes
        .append(L"#include \"FeatureTestModel.h\"\n")
        .append(L"#include \"" + StepHeaderFileName() + L"\"\n")
        .append(BDDUtil::NEW_LINE);

    return includes;
}

wstring BDDFeatureBuilder::BuildFeatureTestClass()
{
    wstring testClass;
    testClass
        .append(wstring(L"// ") + FeatureClassName() + L"\n")
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"class ") + BDDUtil::to_ident(FeatureClassName()) + L" : public FeatureTestModel\n")
        .append(L"{\n")
        .append(BuildSetupAndTearDown())
        .append(BDDUtil::NEW_LINE)
        .append(BuildGetStepModelFunction())
        .append(BDDUtil::NEW_LINE)
        .append(m_BackgoundBuilder.BuildScenario())
        .append(BDDUtil::NEW_LINE)
        .append(BuildExecuteFunction())
        .append(BDDUtil::NEW_LINE)
        .append(BuildStepMemberVar())
        .append(BDDUtil::NEW_LINE)
        .append(L"};\n");

    return testClass;
}

wstring BDDFeatureBuilder::FeatureClassName()
{
    return FeatureTitle() + L"_Feature";
}


wstring BDDFeatureBuilder::BuildSetupAndTearDown()
{
    wstring setupAndTearDown;
    setupAndTearDown
        .append(L"public:\n")
        .append(BDDUtil::INDENT + L"void SetUp() override\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BDDUtil::INDENT_DOUBLE + L"steps.SetUp();\n")
        .append(BDDUtil::INDENT_DOUBLE + L"FeatureBackground();\n")
        .append(BDDUtil::INDENT + L"}\n")
        .append(BDDUtil::INDENT + L"void TearDown() override\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BDDUtil::INDENT_DOUBLE + L"steps.TearDown();\n")
        .append(BDDUtil::INDENT + L"}\n");

    return setupAndTearDown;
}

wstring BDDFeatureBuilder::BuildGetStepModelFunction()
{
    wstring getStepDefFunc;
    getStepDefFunc
        .append(L"protected:\n")
        .append(BDDUtil::INDENT + L"AbstractStepModel* GetStepModel() override\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BDDUtil::INDENT_DOUBLE + L"return &steps;\n")
        .append(BDDUtil::INDENT + L"}\n");

    return getStepDefFunc;
}

wstring BDDFeatureBuilder::BuildExecuteFunction()
{
    wstring execteFunc;
    execteFunc
        .append(BDDUtil::INDENT + L"void ExecuteTest()\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BDDUtil::INDENT_DOUBLE + L"steps.ExecuteTest();\n")
        .append(BDDUtil::INDENT + L"}\n");

    return execteFunc;
}

wstring BDDFeatureBuilder::BuildStepMemberVar()
{
    wstring stepMemberVar;
    stepMemberVar
        .append(L"private:\n");
    if (!BDDUtil::supportUnicode())
    {
        stepMemberVar
            .append(BDDUtil::INDENT + L"// " + m_StepClassName + L" steps;")
            .append(BDDUtil::NEW_LINE);
    }

    stepMemberVar
        .append(BDDUtil::INDENT + BDDUtil::to_ident(m_StepClassName) + L" steps;");

    return stepMemberVar;
}

wstring BDDFeatureBuilder::BuildScenarioes()
{
    wstring scenarioes;

    for (BDDAbstrctScenarioBuilder* pScenarioBuilder : m_ScenarioBuilderList)
    {
        scenarioes
            .append(pScenarioBuilder->BuildScenario())
            .append(BDDUtil::NEW_LINE);
    }

    return scenarioes;
}
