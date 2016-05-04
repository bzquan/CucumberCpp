#include "BDDUtil.h"
#include "BDDStepBuilder.h"
#include "BDDStepImplBuilderContext.h"
#include "BDDStepImplCppBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

wstring BDDStepImplCppBuilder::BuildStepImplCpp()
{
    wstring stepImplCpp;
    stepImplCpp
        .append(wstring(L"#include \"") + BDDStepImplBuilderContext::StepHeaderFileName() + L"\"")
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::NEW_LINE)
        .append(BuildStepImps())
        .append(BDDUtil::NEW_LINE);

    return stepImplCpp;
}

wstring BDDStepImplCppBuilder::BuildStepImps()
{
    wstring stepImps;
    for (BDDStepBuilder* pStepBuilder : BDDStepImplBuilderContext::NonDuplicateStepBuilders())
    {
        stepImps
            .append(MakeStepComments(*pStepBuilder))
            .append(pStepBuilder->BuildStepImp())
            .append(BDDUtil::NEW_LINE)
            .append(BDDUtil::NEW_LINE);
    }

    return stepImps;
}

wstring BDDStepImplCppBuilder::MakeStepComments(BDDStepBuilder& stepBuilder)
{
    wstring comments;
    for (wstring str : stepBuilder.StepComments())
    {
        comments
            .append(L"// " + str)
            .append(BDDUtil::NEW_LINE);
    }

    return comments;
}
