﻿#include "BDDUtil.h"
#include "BDDStepImplBuilderContext.h"
#include "BDDTestModelBuilder.h"

using namespace std;
using namespace CucumberCpp;

wstring BDDStepModelTemplateBuilder::BuildTestModelHeader()
{
    wstring stepModelTemplate;
    stepModelTemplate
        .append(L"#pragma once\n")
        .append(BDDUtil::NEW_LINE)
        .append(L"#include \"gtest/gtest.h\"\n")
        .append(L"#include \"gmock/gmock.h\"\n")
        .append(L"#include \"AbstractTestModel.h\"\n")
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"//") + BDDStepImplBuilderContext::FeatureTestModelName())
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"class ") + BDDUtil::to_ident(BDDStepImplBuilderContext::FeatureTestModelName()) + L" : public AbstractTestModel\n")
        .append(L"{\n")
        .append(L"public:\n")
        .append(BDDUtil::INDENT + L"void SetUp();\n")
        .append(BDDUtil::INDENT + L"void TearDown();\n")
        .append(BDDUtil::INDENT + L"void VerifyExpectations() override;\n")
        .append(L"};\n");

    return stepModelTemplate;
}

wstring BDDStepModelTemplateBuilder::BuildTestModelImplementation()
{
    wstring stepModelTemplate;
    stepModelTemplate
        .append(wstring(L"#include \"gmock/gmock.h\"\n"))
        .append(wstring(L"#include \"gtest/gtest.h\"\n"))
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"#include \"") + BDDUtil::to_ident(BDDStepImplBuilderContext::FeatureTestModelName()) + L".h\"\n")
        .append(BDDUtil::NEW_LINE)
        .append(L"using namespace ::testing;\n")
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"void ") + BDDStepImplBuilderContext::FeatureTestModelName() + L"::SetUp()\n")
        .append(L"{\n")
        .append(L"}\n")
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"void ") + BDDStepImplBuilderContext::FeatureTestModelName() + L"::TearDown()\n")
        .append(L"{\n")
        .append(L"}\n")
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"void ") + BDDStepImplBuilderContext::FeatureTestModelName() + L"::VerifyExpectations()\n")
        .append(L"{\n")
        .append(L"}\n");

    return stepModelTemplate;
}