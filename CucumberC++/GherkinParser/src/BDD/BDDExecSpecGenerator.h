#pragma once

#include <string>
#include <memory>
#include "BDDFeatureBuilder.h"
#include "BDDStepImplBuilderManager.h"
#include "BDDASTVisitor.h"

namespace GherkinAst
{
    class Feature;
}

namespace CucumberCpp
{
    class BDDExecSpecGenerator
    {
    public:
        BDDExecSpecGenerator();
        void GenExecSpec(GherkinAst::Feature* pFeature);
        std::wstring StepHeaderFileName();
        std::wstring StepImplFileName();
        std::wstring StepModelTemplateHeaderFileName();
        std::wstring StepModelTemplateImplFileName();
        std::wstring FeatureFileName();
        std::wstring StepDefsHeader();
        std::wstring StepDefsImpl();
        std::wstring StepModelTemplateHeader();
        std::wstring StepModelTemplateImpl();
        std::wstring FeatureImpl();

    private:
        std::unique_ptr<BDDASTVisitor> m_BDDASTVisitor;
        std::unique_ptr<BDDFeatureBuilder> m_FeatureBuilder;
        std::unique_ptr<BDDStepImplBuilderManager> m_StepImplBuilderManager;
    };
}
