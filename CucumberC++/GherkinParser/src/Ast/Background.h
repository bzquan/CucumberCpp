#pragma once

#include "IHasLocation.h"
#include "IHasDescription.h"
#include "IHasTags.h"
#include "IVisit.h"
#include "IHasSteps.h"
#include "Tag.h"
#include "Location.h"

namespace GherkinAst
{
    class Background : public IHasLocation, public IHasDescription, public IHasSteps, public IVisit
    {
    public:
        Background(int lineNo, std::wstring* pTitle, std::wstring* pDescription, std::vector<GherkinAst::Step>* pSteps);

        void Visit(IVisitable& visitable) override;
    };
}