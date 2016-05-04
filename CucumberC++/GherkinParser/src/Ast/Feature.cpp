#include "IVisitable.h"
#include "ScenarioDefinition.h"
#include "Scenario.h"
#include "ScenarioOutline.h"
#include "Feature.h"

using namespace GherkinAst;


Feature::Feature(int lineNo, std::wstring* pLang, std::vector<Tag>* pTags, std::wstring* pTitle, std::wstring* pDesc) :
    IHasLocation(lineNo),
    IHasTags(pTags),
    IHasDescription(L"Feature", pTitle, pDesc),
    m_pLanguage(nullptr),
    m_pBackground(nullptr)
{
    SetLanguage(pLang);
}

Feature::~Feature()
{
    delete m_pLanguage;
    delete m_pBackground;

    for (ScenarioDefinition* pScenario : m_ScenarioDefinitions)
    {
        delete pScenario;
    }
}

void Feature::SetLanguage(std::wstring* pLang)
{
    if (pLang == nullptr) return;

    m_pLanguage = new GherkinAst::Language(*pLang);
    delete pLang;
}

void Feature::Background(int lineNo, std::wstring* pTitle, std::wstring* pDescription, std::vector<GherkinAst::Step>* pSteps)
{
    m_pBackground = new GherkinAst::Background(lineNo, pTitle, pDescription, pSteps);
    CheckNoColumnIndexParam(m_pBackground->Steps());
}

void Feature::AddScenario(std::vector<Tag>* pTags, int lineNo, std::wstring* pTitle, std::wstring* pDesc, std::vector<GherkinAst::Step>* pSteps)
{
    Scenario* scenario = new Scenario(pTags, lineNo, pTitle, pDesc, pSteps);
    m_ScenarioDefinitions.push_back(scenario);
    CheckNoColumnIndexParam(scenario->Steps());
}

void Feature::AddScenarioOutline(std::vector<Tag>* pTags, int lineNo, std::wstring* pTitle, std::wstring* pDesc, std::vector<GherkinAst::Step>* pSteps, std::vector<GherkinAst::Example*>* pExamples)
{
    ScenarioOutline* scenarioOutline = new ScenarioOutline(pTags, lineNo, pTitle, pDesc, pSteps, pExamples);
    m_ScenarioDefinitions.push_back(scenarioOutline);
}

void Feature::Visit(IVisitable& visitable)
{
    if (m_pLanguage != nullptr) visitable.Accept(*m_pLanguage);
    visitable.Accept(Tags());
    visitable.Accept(*this);
    if (m_pBackground != nullptr) {
        m_pBackground->Visit(visitable);
    }

    for (ScenarioDefinition* scenario : m_ScenarioDefinitions)
    {
        scenario->Visit(visitable);
    }
}

void Feature::CheckNoColumnIndexParam(std::vector<GherkinAst::Step>& steps)
{
    GherkinError invalidColumnParamError;

    for (Step& step : steps)
    {
        if (step.HasColumnIndexParam())
        {
            invalidColumnParamError.append(step.Location().Line(), L"Invalid coloum index param. It is valid only for steps of scenario outline.");
        }
    }

    if (invalidColumnParamError.AllErrors().size() > 0)
    {
        throw invalidColumnParamError;
    }
}

