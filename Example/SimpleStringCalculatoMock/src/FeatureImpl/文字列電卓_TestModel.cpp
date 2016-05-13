#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "文字列電卓_TestModel.h"

using namespace ::testing;

void 文字列電卓_TestModel::SetUp()
{
}

void 文字列電卓_TestModel::TearDown()
{
}

void 文字列電卓_TestModel::VerifyExpectations()
{
}

void 文字列電卓_TestModel::Input(string input)
{
    m_Calculator.Input(input);
}

void 文字列電卓_TestModel::CalculateSum()
{
    m_ActualSum = m_Calculator.CalculateSum();
}

void 文字列電卓_TestModel::ExpectedSum(int sum)
{
    ASSERT_EQ(sum, m_ActualSum);
}
