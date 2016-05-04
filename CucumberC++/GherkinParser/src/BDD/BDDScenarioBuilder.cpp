#include "Scenario.h"
#include "BDDUtil.h"
#include "BDDStepBuilder.h"
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
    wstring scenarioImpl;

    if (!BDDUtil::supportUnicode())
    {
        scenarioImpl
            .append(wstring(L"// TEST_F(") + FeatureClassName() + L", " + ScenarioName() + L")")
            .append(BDDUtil::NEW_LINE);
    }
    scenarioImpl
        .append(wstring(L"TEST_F(") + BDDUtil::to_ident(FeatureClassName()) + L", " + BDDUtil::to_ident(ScenarioName()) + L")\n")
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
