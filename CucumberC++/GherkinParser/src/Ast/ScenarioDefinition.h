#pragma once

#include <string>
#include "IHasLocation.h"
#include "IHasDescription.h"
#include "IHasSteps.h"
#include "IHasTags.h"
#include "IVisit.h"

namespace GherkinAst
{
    class IVisitable;

    class ScenarioDefinition : public IHasLocation, public IHasDescription, public IHasSteps, public IHasTags, public IVisit
    {
    public:
        virtual ~ScenarioDefinition(){}
        void Visit(IVisitable& visitable) override;

    protected:
        ScenarioDefinition(){}
        ScenarioDefinition(
            std::vector<GherkinAst::Tag>* pTags,
            int lineNo,
            std::wstring keyword, std::wstring* title, std::wstring* description,
            std::vector<GherkinAst::Step>* pStepSeq);

        bool HasGUIDTag();

    protected:
        virtual void AcceptVisitable(IVisitable& visitable) = 0;

    private:
        void AppendGUIDTag();
    };
}