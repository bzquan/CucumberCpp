#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "StringCalculator.h"
#include "MockDisplay.h"
#include "AbstractTestModel.h"

//String_calculator_using_mock_object_TestModel
class String_calculator_using_mock_object_TestModel : public AbstractTestModel
{
public:
    String_calculator_using_mock_object_TestModel() : m_Calculator(&m_MockDisplay) {}

    void SetUp();
    void TearDown();
    void VerifyExpectations() override;
    void Input(string input);
    void ExpectedSum(int sum);

private:
    MockDisplay      m_MockDisplay;
    StringCalculator m_Calculator;
};
