#pragma once

#include "IVisit.h"

namespace GherkinAst
{
    class StepArgument : public IVisit
    {
    public:
        virtual StepArgument* copy() const = 0;
    };
}