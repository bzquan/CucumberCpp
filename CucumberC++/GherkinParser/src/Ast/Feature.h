/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
