#pragma once

#include <vector>
#include <string>
#include "IHasLocation.h"
#include "IHasDescription.h"
#include "IHasTags.h"
#include "IVisit.h"
#include "Tag.h"
#include "Language.h"
#include "Background.h"
#include "Comment.h"

namespace GherkinAst
{
    class ScenarioDefinition;

    class Feature : public IHasLocation, public IHasTags, public IHasDescription, public IVisit
    {
    public:
        Feature(int lineNo, std::wstring* pLang, std::vector<Tag>* pTags, std::wstring* pTitle, std::wstring* pDesc);
        ~Feature();
        GherkinAst::Language* Language() { return m_pLanguage; }

        std::vector<Comment>& comments() { return m_Comments; }
        void addComment(Comment& comment) { m_Comments.push_back(comment); }

        GherkinAst::Background* Background() { return m_pBackground; }
        void Background(int lineNo, std::wstring* pTitle, std::wstring* pDescription, std::vector<GherkinAst::Step>* pSteps);

        std::vector<ScenarioDefinition*>& ScenarioDefinitions() { return m_ScenarioDefinitions; }
        void AddScenario(std::vector<Tag>* pTags, int lineNo, std::wstring* pTitle, std::wstring* pDesc, std::vector<GherkinAst::Step>* pSteps);
        void AddScenarioOutline(std::vector<Tag>* pTags, int lineNo, std::wstring* pTitle, std::wstring* pDesc, std::vector<GherkinAst::Step>* pSteps, std::vector<GherkinAst::Example*>* pExamples);

        void Visit(IVisitable& visitable) override;

    private:
        void SetLanguage(std::wstring* pLang);
        void CheckNoColumnIndexParam(std::vector<GherkinAst::Step>& steps);

    private:
        std::vector<Comment>    m_Comments;
        GherkinAst::Language*   m_pLanguage;
        GherkinAst::Background* m_pBackground;
        std::vector<ScenarioDefinition*>   m_ScenarioDefinitions;
    };
}
