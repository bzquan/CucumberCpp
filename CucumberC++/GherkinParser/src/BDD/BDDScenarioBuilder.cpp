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

#include "Scenario.h"
#include "BDDUtil.h"
#include "BDDStepBuilder.h"
#include "BDDFeatureBuilderContext.h"
#include "BDDScenarioBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

BDDScenarioBuilder::BDDScenarioBuilder(Scenario& scenario) :
    m_Scenario(scenario)
{
}

wstring BDDScenarioBuilder::BuildScenarioImpl()
{
    BDDFeatureBuilderContext context;
    context.AppendName(ScenarioName());

    wstring scenarioImpl;
    scenarioImpl
        .append(wstring(L"TEST_FF(") + FeatureClassName() + L", " + ScenarioName() + L")\n")
        .append(L"{\n")
        .append(BDDUtil::INDENT + BuildGUIDTag())
        .append(BDDUtil::NEW_LINE)
        .append(BDDUtil::NEW_LINE)
        .append(BuildSteps(BDDUtil::INDENT))
        .append(BDDUtil::INDENT + L"ExecuteTest();\n")
        .append(L"}\n");

    return scenarioImpl;
}

wstring BDDScenarioBuilder::ScenarioName()
{
    return BDDUtil::MakeIdentifier(m_Scenario.Title());
}
