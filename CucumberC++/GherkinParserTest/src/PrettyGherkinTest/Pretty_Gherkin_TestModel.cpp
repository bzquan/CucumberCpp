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

#include <sstream>
#include "StrUtility.h"
#include "GherkinIF.h"
#include "Pretty_Gherkin_TestModel.h"

using namespace std;
using namespace ::testing;

void Pretty_Gherkin_TestModel::SetUp()
{
}

void Pretty_Gherkin_TestModel::TearDown()
{
}

void Pretty_Gherkin_TestModel::VerifyExpectations()
{
}

void Pretty_Gherkin_TestModel::GivenGherkin(wstring& docStr) 
{
    m_OriginGherkin = docStr;
    StrUtility::ReplaceAll(m_OriginGherkin, L"^", L"");
}

void Pretty_Gherkin_TestModel::MakePrettyGherkin()
{
    wistringstream is(m_OriginGherkin);
    GherkinIF parser;
    bool success = parser.prettyGherkin(is, m_FormattedGherkin);
    if (!success)
    {
        std::vector<GherkinErrorMsg> errors = parser.errorMsgs();
        for (GherkinErrorMsg& error : errors)
        {
            wcout << L"Line(" << error.lineNo() << L") " << error.errorMsg() << endl;
        }
    }
}

void Pretty_Gherkin_TestModel::ExpectNewGUIDCreated()
{
    std::size_t begin = m_FormattedGherkin.find(L"@guid-");
    ASSERT_TRUE(begin != std::string::npos);

    RemoveAllGUIDsFromFormattedGherkin();
}

void Pretty_Gherkin_TestModel::ExpectFormattedGherkin(wstring& docStr)
{
    wstring expectedGherkin = TakeoutLeadingDelimiter(docStr);

    ASSERT_EQ(expectedGherkin, m_FormattedGherkin);
}

wstring Pretty_Gherkin_TestModel::TakeoutLeadingDelimiter(wstring& docStr)
{
    wstringstream ss(docStr);
    wstring line;
    wstring result;
    while (getline(ss, line))
    {
        if ((line.length() > 0) && (line[0] == L'^')) line.erase(0, 1);
        result
            .append(line)
            .append(L"\n");
    }

    return result;
}

void Pretty_Gherkin_TestModel::RemoveAllGUIDsFromFormattedGherkin()
{
    std::size_t begin = m_FormattedGherkin.find(L"@guid-");
    while (begin != std::string::npos)
    {
        std::size_t end = m_FormattedGherkin.find(L'\n', begin);
        if (end != std::string::npos)
        {
            size_t len = end - begin + 1;
            wstring guid = m_FormattedGherkin.substr(begin, len);
            m_FormattedGherkin.replace(begin, len, L"");

            wcout << "New GUID: " << guid << endl;
        }
        begin = m_FormattedGherkin.find(L"@guid-");
    }
}
