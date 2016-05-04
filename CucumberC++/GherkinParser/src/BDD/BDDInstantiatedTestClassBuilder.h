#pragma once

#include <string>
#include <vector>

namespace GherkinAst
{
    class Example;
    class TableRow;
}

namespace CucumberCpp
{
    class BDDInstantiatedTestClassBuilder
    {
        // This is new interface for BDD
    public:
        void StartToBuild(std::wstring featureClassName, std::wstring scenarioOutlineClassName);
        std::wstring Build(GherkinAst::Example& examples);

    private:
        std::wstring BuildParameters(std::vector<GherkinAst::TableRow>& rows);

    private:
        std::wstring m_FeatureClassName;
        std::wstring m_ScenarioOutlineClassName;
        int m_InstanceNo = 0;
    };
}
