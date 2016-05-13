#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "StringCalculator.h"
#include "AbstractTestModel.h"

//文字列電卓_TestModel
class 文字列電卓_TestModel : public AbstractTestModel
{
public:
    void SetUp();
    void TearDown();
    void VerifyExpectations() override;
    void Input(string input);
    void CalculateSum();
    void ExpectedSum(int sum);

private:
    StringCalculator m_Calculator;
    int m_ActualSum;
};
