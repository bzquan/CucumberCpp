#pragma once

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IDisplay.h"

using namespace testing;

class MockDisplay : public IDisplay
{
public:
    MOCK_METHOD1(Sum, void(int sum));

    void ExpectSum(int sum)
    {
        EXPECT_CALL(*this, Sum(sum));
    }
};
