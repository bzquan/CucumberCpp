#include "BDDUtil.h"
#include "BDDStepBuilder.h"
#include "BDDStepImplBuilderContext.h"
#include "BDDStepImplHeaderBuilder.h"

using namespace std;
using namespace CucumberCpp;

wstring BDDStepImplHeaderBuilder::BuildStepImplHeader()
{
    wstring stepImplHeader;

    stepImplHeader
        .append(BuildIncludes())
        .append(BDDUtil::NEW_LINE)
        .append(BuildClassBeginning())
        .append(BDDUtil::NEW_LINE)
        .append(BuildStepDefs())
        .append(BDDUtil::NEW_LINE)
        .append(BuildRegisterSteps())
        .append(BDDUtil::NEW_LINE)
        .append(BuildClassEnding())
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
    wstring beginning;
    beginning
        .append(wstring(L"class ") + BDDStepImplBuilderContext::StepImplClassName() + L" : public AbstractStepModel\n")
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
