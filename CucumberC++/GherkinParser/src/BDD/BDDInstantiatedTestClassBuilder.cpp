#include "Example.h"
#include "TableRow.h"
#include "BDDUtil.h"
#include "BDDGherkinTableBuilder.h"
#include "BDDInstantiatedTestClassBuilder.h"

using namespace std;
using namespace GherkinAst;
using namespace CucumberCpp;

void BDDInstantiatedTestClassBuilder::StartToBuild(wstring featureClassName, wstring scenarioOutlineClassName)
{
    m_FeatureClassName = featureClassName;
    m_ScenarioOutlineClassName = scenarioOutlineClassName;
}

wstring BDDInstantiatedTestClassBuilder::Build(Example& example)
{
    wstring instantiationName = m_FeatureClassName + L"_" + std::to_wstring(m_InstanceNo);
    m_InstanceNo++;

    wstring exampleTableName = BDDUtil::to_ident(instantiationName) + L"_ExampleTable";

    wstring instantiatedTestClass;
    instantiatedTestClass
        .append(BDDGherkinTableBuilder::BuildTableVariable(example.ExampleTable(), exampleTableName))
        .append(BDDUtil::NEW_LINE)
        .append(InstantiatedTestClass(instantiationName, exampleTableName));

    return instantiatedTestClass;
}

std::wstring BDDInstantiatedTestClassBuilder::InstantiatedTestClass(std::wstring instantiationName, std::wstring exampleTableName)
{
    wstring instantiatedTestClass;

    if (!BDDUtil::supportUnicode())
    {
        instantiatedTestClass
            .append(wstring(L"// ") + instantiationName)
            .append(BDDUtil::NEW_LINE);
    }

    instantiatedTestClass
        .append(L"INSTANTIATE_TEST_CASE_P(\n")
        .append(BDDUtil::INDENT_DOUBLE)
        .append(BDDUtil::to_ident(instantiationName))
        .append(L",\n");

    if (!BDDUtil::supportUnicode())
    {
        instantiatedTestClass
           .append(wstring(L"// ") + m_ScenarioOutlineClassName)
           .append(BDDUtil::NEW_LINE);
    }

    instantiatedTestClass
        .append(BDDUtil::INDENT_DOUBLE)
        .append(BDDUtil::to_ident(m_ScenarioOutlineClassName))
        .append(L",\n")
        .append(BDDUtil::INDENT_DOUBLE)
        .append(L"testing::ValuesIn(")
        .append(exampleTableName + L".Rows()));")
        .append(BDDUtil::NEW_LINE);

    return instantiatedTestClass;
}
