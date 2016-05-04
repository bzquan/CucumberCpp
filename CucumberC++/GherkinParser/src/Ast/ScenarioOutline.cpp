#include "Example.h"
#include "IVisitable.h"
#include "ScenarioOutline.h"

using namespace GherkinAst;

ScenarioOutline::ScenarioOutline(
    std::vector<GherkinAst::Tag>* pTags,
    int lineNo,
    std::wstring* title, std::wstring* description,
    std::vector<GherkinAst::Step>* pStepSeq,
    std::vector<GherkinAst::Example*>* pExamples) :
    ScenarioDefinition(pTags, lineNo, L"Scenario Outline", title, description, pStepSeq)
{
    if (pExamples != nullptr)
    {
        for (GherkinAst::Example* example : *pExamples)
        {
            m_Examples.push_back(example);
        }
        delete pExamples;
    }
}

void ScenarioOutline::Visit(IVisitable& visitable)
{
    ScenarioDefinition::Visit(visitable);

    for (GherkinAst::Example* example : m_Examples)
    {
        example->Visit(visitable);
    }
}
