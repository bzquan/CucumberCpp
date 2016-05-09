#ifdef WIN32
// Disable warning C4819: The file contains a character that cannot be represented in the current code page
#pragma warning(disable : 4819)
// Disable warning C4800: 'int' : forcing value to bool 'true' or 'false'(performance warning)
#pragma warning(disable : 4800)
#endif

#include "FeatureTestModel.h"
#include "String_calculator_Steps.h"


// String_calculator_Feature

class String_calculator_Feature : public FeatureTestModel
{
public:
    void SetUp() override
    {
        steps.SetUp();
        FeatureBackground();
    }
    void TearDown() override
    {
        steps.TearDown();
    }

protected:
    AbstractStepModel* GetStepModel() override
    {
        return &steps;
    }

    void FeatureBackground()
    {
    }

    void ExecuteTest()
    {
        steps.ExecuteTest();
    }

private:
    String_calculator_Steps steps;
};

class String_calculator_Feature_A_separator_can_be__comma_or_semicolon :
    public String_calculator_Feature,
    public WithParamInterface<GherkinRow>
{
public:
    void SetUp() override
    {
        String_calculator_Feature::SetUp();
        Spec("@guid-0e91e40c-a065-74a9-2ba1-0c3598fd6a1a");
    }
};

TEST_P(String_calculator_Feature_A_separator_can_be__comma_or_semicolon, ScenarioOutline)
{
    GherkinRow param = GetParam();

    Then(L"The result <Sum> shall be informed[[mock]]", param);
    Given(L"Enter <Numbers> with separator", param);
    When(L"Sum all the numbers");
    ExecuteTest();
}

GherkinTable String_calculator_Feature_0_ExampleTable = GherkinTable(
        L"|Numbers  |Sum|\n"
        L"|1 + 2 + 3|6  |\n"
        L"|4, 5, 6  |15 |\n"
        L"|7; 8; 9  |24 |\n"
        L"|1, 2; 3  |-1 |");

INSTANTIATE_TEST_CASE_P(
        String_calculator_Feature_0,
        String_calculator_Feature_A_separator_can_be__comma_or_semicolon,
        testing::ValuesIn(String_calculator_Feature_0_ExampleTable.Rows()));


