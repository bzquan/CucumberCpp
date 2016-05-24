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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>
#include <regex>
#include "GherkinIF.h"

using namespace std;
using namespace testing;

class parseErrorTest : public testing::Test {
public:
    virtual void SetUp(){}
    virtual void TearDown(){}

protected:
    GherkinIF parser;
};

TEST_F(parseErrorTest, WrongStep)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When- action
          )"
    };

    // When
    wstring formattedGherkin;
    parser.prettyGherkin(is, formattedGherkin);
    std::vector<GherkinErrorMsg> errors = parser.errorMsgs();

    // Then
    ASSERT_EQ((size_t)1, errors.size());
    ASSERT_EQ(5, errors[0].lineNo());
    ASSERT_EQ(wstring(L"Syntax error: Expect scenario steps."), errors[0].errorMsg());
}

TEST_F(parseErrorTest, TableColumnsInconsistent)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
                |Col1|Col2 |Col3|
                |IBM |25   |USD ||
                |Sony|1,500|JPY |
              Given precondition
            )"
    };

    // When
    wstring formattedGherkin;
    bool res = parser.prettyGherkin(is, formattedGherkin);
    std::vector<GherkinErrorMsg> errors = parser.errorMsgs();

    // Then
    ASSERT_FALSE(res);
    ASSERT_EQ((size_t)1, errors.size());
}

TEST_F(parseErrorTest, TableColumnsIndex_4_scenario)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given <Col1> is share name
                |Col1|Col2 |Col3|
                |IBM |25   |USD |
                |Sony|1,500|JPY |
              Given precondition
            )"
    };

    // When
    wstring formattedGherkin;
    bool res = parser.prettyGherkin(is, formattedGherkin);
    std::vector<GherkinErrorMsg> errors = parser.errorMsgs();

    // Then
    ASSERT_FALSE(res);
    ASSERT_EQ((size_t)1, errors.size());
}
