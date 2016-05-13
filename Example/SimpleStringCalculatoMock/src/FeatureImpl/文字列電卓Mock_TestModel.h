#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AbstractTestModel.h"

#include "MockDisplay.h"
#include "StringCalculator.h"

//文字列電卓Mock_TestModel
class 文字列電卓Mock_TestModel : public AbstractTestModel
{
public:
    文字列電卓Mock_TestModel() : m_Calculator(&m_MockDisplay) {}

    void SetUp();
    void TearDown();
    void VerifyExpectations() override;
    void Input(string input);
    void ExpectedSum(int sum);

private:
    MockDisplay      m_MockDisplay;
    StringCalculator m_Calculator;
    int m_ExpectedSum;
    int m_ActualSum;
};
