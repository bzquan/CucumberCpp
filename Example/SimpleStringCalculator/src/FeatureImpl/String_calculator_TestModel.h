#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AbstractTestModel.h"
#include "StringCalculator.h"

//String_calculator_TestModel
class String_calculator_TestModel : public AbstractTestModel
{
public:
    void SetUp();
    void TearDown();
    void VerifyExpectations() override;

    void Input(string input);
    void Sum();
    void ExpectedSum(int sum);

private:
    StringCalculator m_Calculator;
    int m_ExpectedSum;
    int m_ActualSum;
};
