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
