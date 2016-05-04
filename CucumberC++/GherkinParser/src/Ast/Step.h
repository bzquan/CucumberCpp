#pragma once

#include <string>
#include "Definitions.h"
#include "StepArgument.h"
#include "IHasLocation.h"
#include "IVisit.h"

namespace GherkinAst
{
    class Step : public IHasLocation, public IVisit
    {
    public:
        Step(StepKind stepKind, int lineNo, std::wstring* pText, GherkinAst::StepArgument* pStepArgument);
        ~Step();

        Step(const Step& other);
        Step& operator=(const Step& other);

        std::wstring Keyword();
        std::wstring& Text() { return m_Text; }

        GherkinAst::StepArgument* StepArgument() const
        {
            return m_pStepArgument;
        }

        bool IsAndOrButKeyWord();
        bool HasColumnIndexParam();
        void Visit(IVisitable& visitable) override;

    private:
        StepKind      m_Keyword;
        std::wstring  m_Text;
        GherkinAst::StepArgument*  m_pStepArgument;
    };
}
