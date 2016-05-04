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
