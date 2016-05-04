#pragma once

#include <list>
#include <string>

namespace GherkinAst
{
    class Tag;
}

namespace CucumberCpp
{
    class BDDStepBuilder;

    class BDDAbstrctScenarioBuilder
    {
    public:
        virtual ~BDDAbstrctScenarioBuilder() {}
        std::wstring FeatureClassName() { return m_FeatureClassName; }
        void FeatureClassName(std::wstring name) { m_FeatureClassName = name; }

        std::vector<GherkinAst::Tag> ScenarioTags() { return m_ScenarioTags; }
        void ScenarioTags(std::vector<GherkinAst::Tag>& tags) { m_ScenarioTags = tags; }
        void AddScenarioStep(BDDStepBuilder* pStepBuilder);

        std::wstring BuildScenario()
        {
            MakeTableAndDocStringSeqNo();
            return BuildScenarioImpl();
        }

        virtual std::wstring BuildScenarioImpl() = 0;

    protected:
        std::wstring BuildGUIDTag();
        std::wstring BuildSteps(std::wstring indent);
        void MakeTableAndDocStringSeqNo();

    private:
        void InsertAtBegining(BDDStepBuilder* pStepBuilder, const wchar_t* attr);

    protected:
        std::list<BDDStepBuilder*> m_StepBuilderList;

    private:
        std::wstring m_FeatureClassName;
        std::vector<GherkinAst::Tag> m_ScenarioTags;
    };
}
