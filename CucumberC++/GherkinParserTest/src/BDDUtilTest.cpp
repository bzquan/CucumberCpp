﻿/* The MIT License (MIT)
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

#include <regex>
#include "BDDUtil.h"

using namespace std;
using namespace testing;
using namespace CucumberCpp;

class BDDUtilTest : public testing::Test {
public:
    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(BDDUtilTest, MakeIdentifier)
{
    // Given
    wstring str1(L" 日本$語\t");
    wstring str2(L" ^计邓凤#\t");

    // When
    wstring ident1 = BDDUtil::MakeIdentifier(str1);
    wstring ident2 = BDDUtil::MakeIdentifier(str2);

    // Then
    ASSERT_EQ(wstring(L"_日本語_"), ident1);
    bool equal = wstring(L"_计邓凤_") == ident2;
    ASSERT_TRUE(equal);
}

TEST_F(BDDUtilTest, ReplaceWhiteSpaceWithUnderBar)
{
    // Given
    wstring str(L" 日本語\t");

    // When
    wstring result = BDDUtil::ReplaceWhiteSpaceWithUnderBar(str);

    // Then
    ASSERT_EQ(wstring(L"_日本語_"), result);
}

TEST_F(BDDUtilTest, ToTitleCase)
{
    // Given
    wstring str(L"japanese 日本語 chinese");

    // When
    wstring result = BDDUtil::ToTitleCase(str);

    // Then
    ASSERT_EQ(wstring(L"Japanese_日本語_Chinese"), result);
}

TEST_F(BDDUtilTest, ToLowerCaseWithUnderBar)
{
    // Given
    wstring str(L"JAPANESE 日本語 CHINESE");

    // When
    wstring result = BDDUtil::ToLowerCaseWithUnderBar(str);

    // Then
    ASSERT_EQ(wstring(L"japanese_日本語_chinese"), result);
}

TEST_F(BDDUtilTest, ToCPPwstringLiteral)
{
    // Given
    wstring str1(L"L\"a\"1\"z\"");
    wstring str2(L"a\"1\"z");
    wstring str3(L"\"a\"1\"z\"");
    wstring str4(L"\"a\"1\"z");

    // When
    wstring result1 = BDDUtil::ToCPPwstringLiteral(str1);
    wstring result2 = BDDUtil::ToCPPwstringLiteral(str2);
    wstring result3 = BDDUtil::ToCPPwstringLiteral(str3);
    wstring result4 = BDDUtil::ToCPPwstringLiteral(str4);

    // Then
    wstring expected_literal(L"L\"a\"\"1\"\"z\"");
    ASSERT_EQ(expected_literal, result1);
    ASSERT_EQ(expected_literal, result2);
    ASSERT_EQ(expected_literal, result3);
    ASSERT_EQ(expected_literal, result4);
}


TEST_F(BDDUtilTest, regex_multi_match)
{
    // Given
    wstring stepText{ L"column <col1> and <col2> number 123 and 123.4 string \"str1\"" };

    // When
    wregex  stepRegex{ BDDUtil::StepPattern };
    wsmatch match;

    wstring matched_text;
    int match_count = 0;
    wstring str(stepText);
    while (regex_search(str, match, stepRegex)) {
        matched_text = match[0];

        str = match.suffix().str();
        match_count++;
    }
    // Then
    ASSERT_EQ(5, match_count);
}