#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>
#include <regex>
#include "GherkinIF.h"

using namespace std;
using namespace testing;

class parseErrorTest : public testing::Test {
public:
    virtual void SetUp(){}
    virtual void TearDown(){}

protected:
    GherkinIF parser;
};

TEST_F(parseErrorTest, WrongStep)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When- action
          )"
    };

    // When
    wstring formattedGherkin;
    parser.prettyGherkin(is, formattedGherkin);
    std::vector<GherkinErrorMsg> errors = parser.errorMsgs();

    // Then
    ASSERT_EQ((size_t)1, errors.size());
    ASSERT_EQ(5, errors[0].lineNo());
    ASSERT_EQ(wstring(L"Syntax error: Expect scenario steps."), errors[0].errorMsg());
}

TEST_F(parseErrorTest, TableColumnsInconsistent)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
                |Col1|Col2 |Col3|
                |IBM |25   |USD ||
                |Sony|1,500|JPY |
              Given precondition
            )"
    };

    // When
    wstring formattedGherkin;
    bool res = parser.prettyGherkin(is, formattedGherkin);
    std::vector<GherkinErrorMsg> errors = parser.errorMsgs();

    // Then
    ASSERT_FALSE(res);
    ASSERT_EQ((size_t)1, errors.size());
}

TEST_F(parseErrorTest, TableColumnsIndex_4_scenario)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given <Col1> is share name
                |Col1|Col2 |Col3|
                |IBM |25   |USD |
                |Sony|1,500|JPY |
              Given precondition
            )"
    };

    // When
    wstring formattedGherkin;
    bool res = parser.prettyGherkin(is, formattedGherkin);
    std::vector<GherkinErrorMsg> errors = parser.errorMsgs();

    // Then
    ASSERT_FALSE(res);
    ASSERT_EQ((size_t)1, errors.size());
}
