#include "IVisitable.h"
#include "Background.h"

using namespace GherkinAst;
//class Background : public IHasLocation, public IHasDescription, public IHasSteps, public IVisit

Background::Background(int lineNo, std::wstring* pTitle, std::wstring* pDescription, std::vector<GherkinAst::Step>* pSteps) :
    IHasLocation(lineNo),
    IHasDescription(L"Background", pTitle, pDescription),
    IHasSteps(pSteps)
{
}

void Background::Visit(IVisitable& visitable)
{
    visitable.Accept(*this);
    for (Step& step : Steps())
    {
        step.Visit(visitable);
    }
}