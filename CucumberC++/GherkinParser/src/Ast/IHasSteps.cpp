#include "IHasSteps.h"

using namespace GherkinAst;

IHasSteps::IHasSteps(std::vector<Step>* pSteps)
{
    if (pSteps != nullptr)
    {
        m_Steps = *pSteps;
    }
    delete pSteps;
}

