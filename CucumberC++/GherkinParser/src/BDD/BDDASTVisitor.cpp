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

#include "Feature.h"
#include "BDDStepImplBuilderContext.h"
#include "BDDFeatureBuilder.h"
#include "BDDStepImplBuilderManager.h"
#include "BDDASTVisitor.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

BDDASTVisitor::BDDASTVisitor(BDDFeatureBuilder& featureBuilder, BDDStepImplBuilderManager& stepImplBuilderManager) :
    m_FeatureBuilder(featureBuilder),
    m_StepImplBuilderManager(stepImplBuilderManager)
{
}

// implementation of IVisitable interface

void BDDASTVisitor::Accept(GherkinAst::Feature& feature)
{
    m_StepImplBuilderManager.FeatureTitle(feature.Title());
    m_FeatureBuilder.FeatureTitle(feature.Title());
}

void BDDASTVisitor::Accept(GherkinAst::Background& /*background*/)
{
    m_FeatureBuilder.CreateBackgound();
}

void BDDASTVisitor::Accept(GherkinAst::ScenarioOutline& scenarioOutline)
{
    m_FeatureBuilder.NewScenarioOutline(scenarioOutline);
}

void BDDASTVisitor::Accept(GherkinAst::Example& example)
{
    m_FeatureBuilder.NewExamples(example);
}

void BDDASTVisitor::Accept(GherkinAst::DataTable& dataTable)
{
    m_StepImplBuilderManager.AddArg(&dataTable);
}

void BDDASTVisitor::Accept(GherkinAst::DocString& docString)
{
    m_StepImplBuilderManager.AddArg(&docString);
}

void BDDASTVisitor::Accept(GherkinAst::Step& step)
{
    BDDStepBuilder* pStepBuilder = m_StepImplBuilderManager.NewStep(step);
    m_FeatureBuilder.AddScenarioStep(pStepBuilder);
}

void BDDASTVisitor::Accept(GherkinAst::Scenario& scenario)
{
    m_FeatureBuilder.NewScenario(scenario);
}

void BDDASTVisitor::AcceptSenarioTags(std::vector<GherkinAst::Tag>& tags)
{
    m_FeatureBuilder.ScenarioTags(tags);
}
