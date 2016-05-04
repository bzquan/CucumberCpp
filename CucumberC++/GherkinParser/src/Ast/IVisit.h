#pragma once

#include "IVisitable.h"

namespace GherkinAst
{
    class IVisit
    {
    public:
        virtual ~IVisit() {}
        virtual void Visit(IVisitable& visitable) = 0;
    };
}
