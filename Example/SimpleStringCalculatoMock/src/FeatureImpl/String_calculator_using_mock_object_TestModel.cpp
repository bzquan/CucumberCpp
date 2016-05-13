#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "String_calculator_using_mock_object_TestModel.h"

using namespace ::testing;

void String_calculator_using_mock_object_TestModel::SetUp()
{
}

void String_calculator_using_mock_object_TestModel::TearDown()
{
}

void String_calculator_using_mock_object_TestModel::VerifyExpectations()
{
    ASSERT_EQ(m_ExpectedSum, m_ActualSum);
}

void String_calculator_using_mock_object_TestModel::Input(string input)
{
    m_Calculator.Input(input);
}

void String_calculator_using_mock_object_TestModel::CalculateSum()
{
    m_Calculator.CalculateSum();
}

void String_calculator_using_mock_object_TestModel::ExpectedSum(int sum)
{
    m_MockDisplay.ExpectSum(sum);
}
