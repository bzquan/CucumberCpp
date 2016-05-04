#include "BDDUtil.h"
#include "BDDStepBuilder.h"
#include "BDDStepImplBuilderContext.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

vector<BDDStepBuilder*> BDDStepImplBuilderContext::s_StepBuilderList;
vector<BDDStepBuilder*> BDDStepImplBuilderContext::s_NonDuplicateStepBuilderList;
wstring BDDStepImplBuilderContext::s_FeatureTitle;

void BDDStepImplBuilderContext::Clear()
{
    for (BDDStepBuilder* pStepBuilder : s_StepBuilderList)
    {
        delete pStepBuilder;
    }
    s_StepBuilderList.clear();
    s_NonDuplicateStepBuilderList.clear();
    s_FeatureTitle = wstring();
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
