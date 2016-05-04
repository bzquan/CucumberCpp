#include <algorithm>    // std::swap
#include <regex>
#include "IVisitable.h"
#include "Step.h"

using namespace std;
using namespace GherkinAst;

Step::Step(StepKind stepKind, int lineNo, std::wstring* pText, GherkinAst::StepArgument* pStepArgument) :
    m_Keyword(stepKind),
    IHasLocation(lineNo),
    m_pStepArgument(pStepArgument)
{
    if (pText != nullptr)
    {
        m_Text = *pText;
    }

    delete pText;
}

Step::~Step()
{
    delete m_pStepArgument;
}

Step::Step(const Step& other) :
    IHasLocation(other),
    m_pStepArgument(nullptr)
{
    m_Keyword = other.m_Keyword;
    m_Text = other.m_Text;
    if (other.StepArgument() != nullptr)
    {
        m_pStepArgument = other.StepArgument()->copy();
    }
}

Step& Step::operator=(const Step& other)
{
    Step temp{ other };
    swap(*this, temp);
    return *this;
}

bool Step::IsAndOrButKeyWord()
{
    return (m_Keyword == StepKind::AND_STEP) ||
           (m_Keyword == StepKind::BUT_STEP);
}

wstring Step::Keyword()
{
    switch (m_Keyword)
    {
    case StepKind::GIVEN_STEP:
        return wstring(L"Given");
    case StepKind::WHEN_STEP:
        return wstring(L"When");
    case StepKind::THEN_STEP:
        return wstring(L"Then");
    case StepKind::AND_STEP:
        return wstring(L"And");
    case StepKind::BUT_STEP:
        return wstring(L"But");
    default:
        return wstring(L"*");
    }
}

bool Step::HasColumnIndexParam()
{
    wregex expr(LR"(<[^>]+>)");
    wsmatch match;

    bool res = regex_search(m_Text, match, expr, std::regex_constants::match_any);
    return res;
}

void Step::Visit(IVisitable& visitable)
{
    visitable.Accept(*this);
    if (m_pStepArgument != nullptr)
    {
        m_pStepArgument->Visit(visitable);
    }
}
