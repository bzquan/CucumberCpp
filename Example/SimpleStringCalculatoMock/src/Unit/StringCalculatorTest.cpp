#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MockDisplay.h"
#include "StringCalculator.h"

using namespace testing;

class StringCalculatorTest : public testing::Test
{
public:
    StringCalculator calculator;
};

TEST_F(StringCalculatorTest, 初期状態)
{
    // Given
    
	// When
    int 合計結果 = calculator.CalculateSum();

	// Then
    ASSERT_EQ(0, 合計結果);
}

TEST_F(StringCalculatorTest, 数字一個)
{
    // Given
    calculator.Input("18");

    // When
    int 合計結果 = calculator.CalculateSum();

    // Then
    ASSERT_EQ(18, 合計結果);
}

TEST_F(StringCalculatorTest, 区切り文字がプラス記号)
{
    // Given
    calculator.Input("1 + 2 + 3");

    // When
    int 合計結果 = calculator.CalculateSum();

    // Then
    ASSERT_EQ(6, 合計結果);
}

TEST_F(StringCalculatorTest, MockObjectの使用)
{
    // Given
    MockDisplay mock;
    StringCalculator calc{ &mock };
    calc.Input("1 + 2 + 3");

    // When
//    EXPECT_CALL(mock, Sum(6));
    mock.ExpectSum(6);   // ここが簡略されました

    calc.CalculateSum();

    // Then
}
