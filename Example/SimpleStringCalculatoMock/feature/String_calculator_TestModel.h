#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AbstractTestModel.h"

//String_calculator_TestModel
class String_calculator_TestModel : public AbstractTestModel
{
public:
    void SetUp();
    void TearDown();
    void VerifyExpectations() override;
};
