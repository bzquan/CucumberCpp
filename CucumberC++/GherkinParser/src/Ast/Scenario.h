#pragma once

#include "IVisitable.h"
#include "ScenarioDefinition.h"

namespace GherkinAst
{
    class Scenario : public ScenarioDefinition
    {
    public:
        Scenario(){}
        Scenario(
            std::vector<GherkinAst::Tag>* pTags,
            int lineNo,
            std::wstring* title, std::wstring* description,
            std::vector<GherkinAst::Step>* pStepSeq) :
            ScenarioDefinition(pTags, lineNo, L"Scenario", title, description, pStepSeq)
        {
        }

    protected:
         void AcceptVisitable(IVisitable& visitable) override
        {
            visitable.Accept(*this);
        }
    };
}