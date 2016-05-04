#pragma once

#include <vector>
#include <string>

#include "Step.h"

namespace CucumberCpp
{
    class BDDStepBuilder;

    class BDDStepImplBuilderContext
    {
    public:
        static void Clear();
        static std::vector<BDDStepBuilder*>& StepBuilders();
        static std::wstring FeatureTitle();
        static void FeatureTitle(std::wstring title);

        static std::wstring StepImplClassName();
        static std::wstring StepHeaderFileName();
        static std::wstring StepImplementationFileName();
        static std::wstring StepModelTemplateHeaderFileName();
        static std::wstring StepModelTemplateImplFileName();
        static std::wstring FeatureTestModelName();
        static BDDStepBuilder* CreateNewStepBuilder(GherkinAst::Step& step);
        static std::vector<BDDStepBuilder*>& NonDuplicateStepBuilders();

    private:
        static void MakeNonDuplicateStepBuilders();
        static BDDStepBuilder* GetSameStepBuilder(BDDStepBuilder* pNewStepBuilder);
        static std::wstring ToIdentifier(const std::wstring& str);

    private:
        static std::vector<BDDStepBuilder*> s_StepBuilderList;
        static std::vector<BDDStepBuilder*> s_NonDuplicateStepBuilderList;
        static std::wstring s_FeatureTitle;
    };
}
