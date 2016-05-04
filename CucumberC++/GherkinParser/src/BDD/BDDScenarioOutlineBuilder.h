#pragma once

#include <string>
#include "BDDAbstrctScenarioBuilder.h"

namespace GherkinAst
{
    class ScenarioOutline;
    class Example;
}

namespace CucumberCpp
{
    class BDDScenarioOutlineBuilder : public BDDAbstrctScenarioBuilder
    {
    public:
        BDDScenarioOutlineBuilder(GherkinAst::ScenarioOutline& scenarioOutline) : 
            m_ScenarioOutline(scenarioOutline)
        {
        }

        std::wstring BuildScenarioImpl() override;
        void AddExamples(GherkinAst::Example& example);
        std::wstring ScenarioOutlineClassName();

    private:
        std::wstring BuildParameterizedTestClass();
        std::wstring BuildTestBody();
        std::wstring BuildInstantiatedTestClassBuildTestCases();
        std::wstring BuildSetupFunction();

    private:
        GherkinAst::ScenarioOutline& m_ScenarioOutline;
        std::vector<GherkinAst::Example> m_ExamplesList;
    };
}
