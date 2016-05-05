#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AbstractTestModel.h"
#include "StringCalculator.h"
#include "MockDisplay.h"

//String_calculator_TestModel
class String_calculator_TestModel : public AbstractTestModel
{
public:
    String_calculator_TestModel();
    void SetUp();
    void TearDown();
    void VerifyExpectations() override;

    void Input(string input);
    void CalculateSum();
    void ExpectedSum(int sum);

private:
    MockDisplay      m_MockDisplay;
    StringCalculator m_Calculator;
    int m_ExpectedSum;
    int m_ActualSum;
};
