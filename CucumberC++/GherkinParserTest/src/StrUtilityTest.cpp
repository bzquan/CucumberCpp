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

#include "StrUtility.h"
#include <sstream>
#include "guid.h"

using namespace std;
using namespace testing;

class StrUtilityTest : public testing::Test {
public:
    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(StrUtilityTest, GuidGenerator)
{
    // Given

    // When
    wstring guid = StrUtility::NewGuid();

    // Then
    ASSERT_TRUE(guid.length() == 36);
}

TEST_F(StrUtilityTest, ReplaceAll_1)
{
    // Given
    wstring text {
        L"line1\r\n"
        L"line2\r\n"
        L"line3\r\n"
    };

    // When
    StrUtility::ReplaceAll(text, L"\r\n", L"\n");

    // Then
    wstring expected{
        L"line1\n"
        L"line2\n"
        L"line3\n"
    };
    ASSERT_EQ(expected, text);
}

TEST_F(StrUtilityTest, ReplaceAll_2)
{
    // Given
    wstring text{
        L"line1\n"
        L"line2\n"
        L"line3\n"
    };

    // When
    StrUtility::ReplaceAll(text, L"\n", L"\r\n");

    // Then
    wstring expected{
        L"line1\r\n"
        L"line2\r\n"
        L"line3\r\n"
    };
    ASSERT_EQ(expected, text);
}

TEST_F(StrUtilityTest, GUID)
{
    // Given
    GuidGenerator gen;

    // When
    Guid guid = gen.newGuid();
    stringstream ss;
    ss << guid;


    // Then
    string str = ss.str();
    ASSERT_TRUE(str.length() > 10);
}
