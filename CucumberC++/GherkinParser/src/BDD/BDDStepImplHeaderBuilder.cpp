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
#include "BDDStepImplHeaderBuilder.h"

using namespace std;
using namespace CucumberCpp;

wstring BDDStepImplHeaderBuilder::BuildStepImplHeader()
{
    wstring include = BuildIncludes();
    wstring classBeginning = BuildClassBeginning();
    wstring stepDefs = BuildStepDefs();
    wstring registerSteps = BuildRegisterSteps();
    wstring classEnding = BuildClassEnding();

    wstring stepImplHeader;
    stepImplHeader
        .append(include)
        .append(BDDUtil::NEW_LINE)
        .append(BDDStepImplBuilderContext::GetUnicodeNameDefines())
        .append(classBeginning)
        .append(BDDUtil::NEW_LINE)
        .append(stepDefs)
        .append(BDDUtil::NEW_LINE)
        .append(registerSteps)
        .append(BDDUtil::NEW_LINE)
        .append(classEnding)
        .append(BDDUtil::NEW_LINE);

    return stepImplHeader;
}

wstring BDDStepImplHeaderBuilder::BuildIncludes()
{
    wstring includes;
    includes
        .append(L"#pragma once\n")
        .append(BDDUtil::NEW_LINE)
        .append(L"#include \"FeatureStepModel.h\"\n")
        .append(wstring(L"#include \"") + BDDStepImplBuilderContext::FeatureTestModelName() + L".h\"\n")
        .append(BDDUtil::NEW_LINE)
        .append(L"using namespace bdd;\n")
        .append(L"#ifdef WIN32\n")
        .append(L"#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)\n")
        .append(L"using namespace boost;\n")
        .append(L"#endif\n")
        .append(L"#endif\n");

    return includes;
}

wstring BDDStepImplHeaderBuilder::BuildClassBeginning()
{
    wstring stepClassName = BDDStepImplBuilderContext::StepImplClassName();
    BDDStepImplBuilderContext::AppendName(stepClassName);

    wstring beginning;
    beginning
        .append(wstring(L"class ") + stepClassName + L" : public AbstractStepModel\n")
        .append(L"{\n")
        .append(L"public:\n")
        .append(BDDUtil::INDENT + L"void SetUp()\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BDDUtil::INDENT_DOUBLE + L"RegisterSteps();\n")
        .append(BDDUtil::INDENT_DOUBLE + L"model.SetUp();\n")
        .append(BDDUtil::INDENT + L"}\n")
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::INDENT + L"void TearDown()\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BDDUtil::INDENT_DOUBLE + L"model.TearDown();\n")
        .append(BDDUtil::INDENT + L"}\n")
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::INDENT + L"void ExecuteTest()\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BDDUtil::INDENT_DOUBLE + L"model.Execute();\n")
        .append(BDDUtil::INDENT + L"}\n");

    return beginning;
}

wstring BDDStepImplHeaderBuilder::BuildStepDefs()
{
    wstring stepDefs;
    stepDefs.append(L"public:\n");

    for (BDDStepBuilder* pStepBuilder : BDDStepImplBuilderContext::NonDuplicateStepBuilders())
    {
        stepDefs
            .append(pStepBuilder->BuildStepHeader())
            .append(BDDUtil::NEW_LINE);
    }

    return stepDefs;
}

wstring BDDStepImplHeaderBuilder::BuildRegisterSteps()
{
    wstring registerSteps;
    registerSteps
        .append(L"public:\n")
        .append(BDDUtil::INDENT + L"void RegisterSteps() override\n")
        .append(BDDUtil::INDENT + L"{\n")
        .append(BuildStepBindings())
        .append(BDDUtil::INDENT + L"}\n");

    return registerSteps;
}

wstring BDDStepImplHeaderBuilder::BuildStepBindings()
{
    wstring stepBindings;
    for (BDDStepBuilder* pStepBuilder : BDDStepImplBuilderContext::NonDuplicateStepBuilders())
    {
        stepBindings
            .append(pStepBuilder->BuildStepBind())
            .append(BDDUtil::NEW_LINE);
    }

    return stepBindings;
}

wstring BDDStepImplHeaderBuilder::BuildClassEnding()
{
    wstring ending;
    ending
        .append(L"private:\n")
        .append(BDDUtil::INDENT + BDDStepImplBuilderContext::FeatureTestModelName() + L" model;\n")
        .append(L"};\n");

    return ending;
}
