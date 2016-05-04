#pragma once

#include <string>
#include <vector>
#include "IVisitable.h"

namespace CucumberCpp
{
    class BDDFeatureBuilder;
    class BDDStepImplBuilderManager;

    class BDDASTVisitor : public GherkinAst::IVisitable
    {
    public:
        BDDASTVisitor(BDDFeatureBuilder& featureBuilder, BDDStepImplBuilderManager& stepImplBuilderManager);

        void Accept(GherkinAst::Feature& feature) override;
        void Accept(GherkinAst::Background& background) override;
        void Accept(GherkinAst::ScenarioOutline& scenarioOutline) override;
        void Accept(GherkinAst::Example& example) override;
        void Accept(GherkinAst::DataTable& dataTable) override;
        void Accept(GherkinAst::DocString& docString) override;
        void Accept(GherkinAst::Step& step) override;
        void Accept(GherkinAst::Scenario& scenario) override;
        void AcceptSenarioTags(std::vector<GherkinAst::Tag>& tags) override;

        /////// Not relevant functions of IVisitable //////

        void Accept(GherkinAst::Language& /*language*/)  override { }
        void Accept(std::vector<GherkinAst::Tag>& /*tags*/)  override { }

    private:
        BDDFeatureBuilder& m_FeatureBuilder;
        BDDStepImplBuilderManager& m_StepImplBuilderManager;
    };
}
