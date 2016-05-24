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
#include "BDDAbstractBuilder.h"
#include "BDDBackgroundBuilder.h"

namespace GherkinAst
{
    class Tag;
    class Example;
    class Scenario;
    class ScenarioOutline;
}

namespace CucumberCpp
{
    class BDDStepBuilder;
    class BDDAbstrctScenarioBuilder;

    class BDDFeatureBuilder : public BDDAbstractBuilder
    {
    public:
        BDDFeatureBuilder() = default;
        ~BDDFeatureBuilder();
        
        std::wstring FeatureFileName();
        std::wstring StepHeaderFileName() { return m_StepHeaderFileName; }
        void StepHeaderFileName(std::wstring headerFileName) { m_StepHeaderFileName = headerFileName; }

        std::wstring StepClassName() { return m_StepClassName; }
        void StepClassName(std::wstring stepClassName) { m_StepClassName = stepClassName; }

        std::vector<GherkinAst::Tag>& ScenarioTags() { return m_ScenarioTags; }
        void ScenarioTags(std::vector<GherkinAst::Tag>& tags) { m_ScenarioTags = tags; }

        std::wstring Build();
        void CreateBackgound();
        void NewScenario(GherkinAst::Scenario& scenario);
        void NewScenarioOutline(GherkinAst::ScenarioOutline& scenarioOutline);
        void NewExamples(GherkinAst::Example& example);
        void AddScenarioStep(BDDStepBuilder* pStepBuilder);

    private:
        void AddNewScenario(BDDAbstrctScenarioBuilder* pScenarioBuilder);
        std::wstring DisableWarning_C4819();
        std::wstring BuildIncludes();
        std::wstring BuildFeatureTestClass();
        std::wstring FeatureClassName();
        std::wstring BuildSetupAndTearDown();
        std::wstring BuildGetStepModelFunction();
        std::wstring BuildExecuteFunction();
        std::wstring BuildStepMemberVar();
        std::wstring BuildScenarioes();

    private:
        std::wstring m_StepHeaderFileName;
        std::wstring m_StepClassName;
        std::vector<GherkinAst::Tag> m_ScenarioTags;
        BDDAbstrctScenarioBuilder* m_pCurrentScenarioBuilder = nullptr;

        std::wstring m_featureImpl;
        BDDBackgroundBuilder m_BackgoundBuilder;
        std::vector<BDDAbstrctScenarioBuilder*> m_ScenarioBuilderList;
    };
}
