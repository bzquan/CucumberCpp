﻿#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "String_calculator_TestModel.h"

using namespace ::testing;

String_calculator_TestModel::String_calculator_TestModel() :
    m_Calculator(m_MockDisplay)
{
}

void String_calculator_TestModel::SetUp()
{
}

void String_calculator_TestModel::TearDown()
{
}

void String_calculator_TestModel::VerifyExpectations()
{
    ASSERT_EQ(m_ExpectedSum, m_ActualSum);
}

void String_calculator_TestModel::Input(string input)
{
    m_Calculator.Input(input);
}

void String_calculator_TestModel::CalculateSum()
{
    m_Calculator.CalculateSum();
}

void String_calculator_TestModel::ExpectedSum(int sum)
{
    m_MockDisplay.ExpectSum(sum);
}