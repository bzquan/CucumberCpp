#pragma once

#include <string>
#include "BDDAbstractBuilder.h"
#include "BDDStepBuilder.h"

namespace GherkinAst
{
    class Step;
    class DocString;
    class DataTable;
}

namespace CucumberCpp
{
    class BDDStepBuilder;
    class BDDStepImplHeaderBuilder;
    class BDDStepImplCppBuilder;
    class BDDStepModelTemplateBuilder;

    class BDDStepImplBuilderManager : public BDDAbstractBuilder
    {
    public:
        BDDStepImplBuilderManager() = default;
        void FeatureTitle(std::wstring title) override;
        BDDStepBuilder* NewStep(GherkinAst::Step& step);
        void AddArg(GherkinAst::DataTable* pDataTable);
        void AddArg(GherkinAst::DocString* pDocString);
        std::wstring BuildStepImplHeader();
        std::wstring BuildStepImplCpp();
        std::wstring BuildTestModelHeader();
        std::wstring BuildTestModelImplementation();

    private:
        BDDStepBuilder* m_pCurrentStep = nullptr;
    };
}
