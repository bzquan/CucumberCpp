﻿#include "ScenarioOutline.h"
#include "Example.h"
#include "BDDUtil.h"
#include "BDDInstantiatedTestClassBuilder.h"
#include "BDDStepBuilder.h"
#include "BDDScenarioOutlineBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

wstring BDDScenarioOutlineBuilder::BuildScenarioImpl()
{
    wstring scenarioOutlineIml;
    scenarioOutlineIml
        .append(BuildParameterizedTestClass())
        .append(BDDUtil::NEW_LINE)
        .append(BuildTestBody())
        .append(BDDUtil::NEW_LINE)
        .append(BuildInstantiatedTestClassBuildTestCases());

    return scenarioOutlineIml;
}

void BDDScenarioOutlineBuilder::AddExamples(Example& example)
{
    m_ExamplesList.push_back(example);
}

wstring BDDScenarioOutlineBuilder::ScenarioOutlineClassName()
{
    return FeatureClassName() + L"_" + BDDUtil::MakeIdentifier(m_ScenarioOutline.Title());
}

wstring BDDScenarioOutlineBuilder::BuildParameterizedTestClass()
{
    wstring scenarioOutlineClass;
    if (!BDDUtil::supportUnicode())
    {
        scenarioOutlineClass
            .append(wstring(L"// ") + ScenarioOutlineClassName() + L" : " + FeatureClassName())
            .append(BDDUtil::NEW_LINE);
    }
    scenarioOutlineClass
        .append(wstring(L"class ") + BDDUtil::to_ident(ScenarioOutlineClassName()) + L" :\n")
        .append(BDDUtil::INDENT + L"public " + BDDUtil::to_ident(FeatureClassName()) + L",\n")
        .append(BDDUtil::INDENT + L"public WithParamInterface<GherkinRow>\n")
        .append(L"{\n")
        .append(L"public:\n")
        .append(BuildSetupFunction())
        .append(L"};\n");

    return scenarioOutlineClass;
}

wstring BDDScenarioOutlineBuilder::BuildTestBody()
{
    wstring scenarioOutlineTestBody;
    if (!BDDUtil::supportUnicode())
    {
        scenarioOutlineTestBody
            .append(wstring(L"// TEST_P(") + ScenarioOutlineClassName() + L", ScenarioOutline)\n");
    }

    scenarioOutlineTestBody
        .append(wstring(L"TEST_P(") + BDDUtil::to_ident(ScenarioOutlineClassName()) + L", ScenarioOutline)\n")
        .append(L"{\n")
        .append(BDDUtil::INDENT + L"GherkinRow param = GetParam();\n")
        .append(BDDUtil::NEW_LINE)
        .append(BuildSteps(BDDUtil::INDENT))
        .append(BDDUtil::INDENT + L"ExecuteTest();\n")
        .append(L"}\n");

    return scenarioOutlineTestBody;
}

wstring BDDScenarioOutlineBuilder::BuildInstantiatedTestClassBuildTestCases()
{
    BDDInstantiatedTestClassBuilder instantiatedTestClassBuilder;
    instantiatedTestClassBuilder.StartToBuild(FeatureClassName(), ScenarioOutlineClassName());
    wstring testCases;
    for (Example& example : m_ExamplesList)
    {
        testCases.append(instantiatedTestClassBuilder.Build(example));
    }

    return testCases;
}

wstring BDDScenarioOutlineBuilder::BuildSetupFunction()
{
    wstring setupFunction;
    setupFunction
        .append(BDDUtil::INDENT + L"void SetUp() override\n")
        .append(BDDUtil::INDENT + L"{\n");
    if (!BDDUtil::supportUnicode())
    {
        setupFunction
            .append(wstring(L"// ") + BDDUtil::INDENT_DOUBLE + FeatureClassName() + L"::SetUp();\n");
    }

    setupFunction
        .append(BDDUtil::INDENT_DOUBLE + BDDUtil::to_ident(FeatureClassName()) + L"::SetUp();\n")
        .append(BDDUtil::INDENT_DOUBLE + BuildGUIDTag())
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::INDENT + L"}\n");

    return setupFunction;
}
