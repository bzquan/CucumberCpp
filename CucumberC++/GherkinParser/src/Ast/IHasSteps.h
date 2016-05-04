#pragma once

#include <vector>
#include <Step.h>

namespace GherkinAst
{
    class IHasSteps
    {
    public:
        IHasSteps(std::vector<Step>* pSteps = nullptr);
        std::vector<Step>& Steps() { return m_Steps; }

    private:
        std::vector<Step> m_Steps;
    };
}
