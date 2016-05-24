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

    wstring exampleTableName;
    exampleTableName
        .append(BDDUtil::to_ident(m_ScenarioOutlineClassName))
        .append(L"_")
        .append(std::to_wstring(m_InstanceNo))
        .append(L"_ExampleTable");

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
