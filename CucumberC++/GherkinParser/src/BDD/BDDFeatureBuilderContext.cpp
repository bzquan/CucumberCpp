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

#include "BDDFeatureBuilderContext.h"

using namespace std;
using namespace CucumberCpp;

BDDUnicodeNameDefinitions BDDFeatureBuilderContext::s_NameDefinitions;

namespace
{
    const wstring GOOGLE_TEST =
            L"#define TEST_FF(test_case_name, test_name) TEST_F(test_case_name, test_name)\n"
            L"#define INSTANTIATE_TEST_CASE_PP(InstantiationName, parameterized, value) INSTANTIATE_TEST_CASE_P(InstantiationName, parameterized, value)\n"
            L"#define TEST_PP(parameterized, ScenarioOutline) TEST_P(parameterized, ScenarioOutline)\n";
}

void BDDFeatureBuilderContext::Clear()
{
    s_NameDefinitions.Clear();
}

void BDDFeatureBuilderContext::AppendName(std::wstring name)
{
    s_NameDefinitions.Append(name);
}

std::wstring BDDFeatureBuilderContext::GetUnicodeNameDefines()
{
    wstring defines{GOOGLE_TEST};
    defines.append(s_NameDefinitions.GetDefines());

    return defines;
}
