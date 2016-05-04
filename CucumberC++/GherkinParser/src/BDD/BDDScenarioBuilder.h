#pragma once

#include <string>
#include "BDDAbstrctScenarioBuilder.h"

namespace GherkinAst
{
    class Scenario;
}

namespace CucumberCpp
{
    class BDDScenarioBuilder : public BDDAbstrctScenarioBuilder
    {
    public:
        BDDScenarioBuilder(GherkinAst::Scenario& scenario);

        std::wstring BuildScenarioImpl() override;

    private:
        std::wstring ScenarioName();

    private:
        GherkinAst::Scenario& m_Scenario;
    };
}
