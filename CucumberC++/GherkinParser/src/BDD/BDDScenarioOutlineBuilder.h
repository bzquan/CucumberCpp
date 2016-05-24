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

#include <string>
#include "BDDAbstrctScenarioBuilder.h"

namespace GherkinAst
{
    class ScenarioOutline;
    class Example;
}

namespace CucumberCpp
{
    class BDDScenarioOutlineBuilder : public BDDAbstrctScenarioBuilder
    {
    public:
        BDDScenarioOutlineBuilder(GherkinAst::ScenarioOutline& scenarioOutline) : 
            m_ScenarioOutline(scenarioOutline)
        {
        }

        std::wstring BuildScenarioImpl() override;
        void AddExamples(GherkinAst::Example& example);
        std::wstring ScenarioOutlineClassName();

    private:
        std::wstring BuildParameterizedTestClass();
        std::wstring BuildTestBody();
        std::wstring BuildInstantiatedTestClassBuildTestCases();
        std::wstring BuildSetupFunction();

    private:
        GherkinAst::ScenarioOutline& m_ScenarioOutline;
        std::vector<GherkinAst::Example> m_ExamplesList;
    };
}
