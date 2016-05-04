#include "Example.h"
#include "TableRow.h"
#include "BDDUtil.h"
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
        .append(L"Values(")
        .append(BDDUtil::INDENT_TABLE_HEADER)
        .append(example.ExampleTable().Rows()[0].TrimmedFormattedText) // 1st row is as table header
        .append(BDDUtil::NEW_LINE)
        .append(BuildParameters(example.ExampleTable().Rows()))
        .append(BDDUtil::INDENT_DOUBLE)
        .append(L"));\n")
        .append(BDDUtil::NEW_LINE);

    m_InstanceNo++;
    return instantiatedTestClass;
}

wstring BDDInstantiatedTestClassBuilder::BuildParameters(vector<TableRow>& rows)
{
    wstring parameters;
    size_t ROWS = rows.size();

    // out put from 2nd row because 1st row has been outputted as table header
    for (size_t index = 1; index < ROWS; ++index)
    {
        if (!BDDUtil::supportUnicode())
        {
            parameters
                .append(wstring(L"// ") + BDDUtil::ParameterClassName)
                .append(BDDUtil::NEW_LINE);
        }
        parameters
            .append(BDDUtil::INDENT_DOUBLE_PLUS)
            .append(BDDUtil::to_ident(BDDUtil::ParameterClassName) + L"(")
            .append(L"L\"")
            .append(rows[index].TrimmedFormattedText)
            .append(L"\")");

        if (index < ROWS - 1)
        {
            parameters.append(L",\n");
        }
        else
        {
            parameters.append(BDDUtil::NEW_LINE);
        }
    }

    return parameters;
}
