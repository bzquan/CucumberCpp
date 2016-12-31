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
#include "BDDStepImplBuilderContext.h"
#include "BDDUnicodeNameDefinitions.h"
#include "BDDTestModelBuilder.h"

using namespace std;
using namespace CucumberCpp;

wstring BDDStepModelTemplateBuilder::BuildTestModelHeader()
{
    BDDUnicodeNameDefinitions nameDefinition;
    nameDefinition.Append(BDDStepImplBuilderContext::FeatureTestModelName());

    wstring stepModelTemplate;
    stepModelTemplate
        .append(L"#pragma once\n")
        .append(BDDUtil::NEW_LINE)
        .append(L"#include \"gtest/gtest.h\"\n")
        .append(L"#include \"gmock/gmock.h\"\n")
        .append(L"#include \"AbstractTestModel.h\"\n")
        .append(BDDUtil::NEW_LINE)
        .append(nameDefinition.GetDefines())
        .append(BDDUtil::NEW_LINE)
        .append(wstring(L"class ") + BDDStepImplBuilderContext::FeatureTestModelName() + L" : public AbstractTestModel\n")
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
        .append(wstring(L"#include \"") + BDDStepImplBuilderContext::FeatureTestModelName() + L".h\"\n")
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
