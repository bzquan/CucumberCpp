#pragma once

#include <vector>
#include "ScenarioDefinition.h"

namespace GherkinAst
{
    class ScenarioOutline : public ScenarioDefinition
    {
    public:
        ScenarioOutline(
            std::vector<GherkinAst::Tag>* pTags,
            int lineNo,
            std::wstring* title, std::wstring* description,
            std::vector<GherkinAst::Step>* pStepSeq,
            std::vector<GherkinAst::Example*>* pExamples);

        std::vector<GherkinAst::Example*>& Examples() { return m_Examples; }

        void Visit(IVisitable& visitable) override;

    protected:
        void AcceptVisitable(IVisitable& visitable) override
        {
            visitable.Accept(*this);
        }

    private:
        std::vector<GherkinAst::Example*> m_Examples;
    };
}
