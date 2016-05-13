#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "文字列電卓Mock_TestModel.h"

using namespace ::testing;

void 文字列電卓Mock_TestModel::SetUp()
{
}

void 文字列電卓Mock_TestModel::TearDown()
{
}

void 文字列電卓Mock_TestModel::VerifyExpectations()
{
}

void 文字列電卓Mock_TestModel::Input(string input)
{
    m_Calculator.Input(input);
    m_Calculator.CalculateSum();
}

void 文字列電卓Mock_TestModel::ExpectedSum(int sum)
{
    m_MockDisplay.ExpectSum(sum);
}
