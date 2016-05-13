#ifdef WIN32
// Disable warning C4819: The file contains a character that cannot be represented in the current code page
#pragma warning(disable : 4819)
// Disable warning C4800: 'int' : forcing value to bool 'true' or 'false'(performance warning)
#pragma warning(disable : 4800)
#endif

#include "FeatureTestModel.h"
#include "文字列電卓Mock_Steps.h"


// 文字列電卓Mock_Feature

class 文字列電卓Mock_Feature : public FeatureTestModel
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
    文字列電卓Mock_Steps steps;
};

class 文字列電卓Mock_Feature_数字文字列の合計 :
    public 文字列電卓Mock_Feature,
    public WithParamInterface<GherkinRow>
{
public:
    void SetUp() override
    {
        文字列電卓Mock_Feature::SetUp();
        Spec("@guid-05692578-2ff0-d490-487b-473121d9acfa");
    }
};

TEST_P(文字列電卓Mock_Feature_数字文字列の合計, ScenarioOutline)
{
    GherkinRow param = GetParam();

    Then(L"<合計>が通知されること[[mock]]", param);
    When(L"<数字文字列>を入力する", param);
    ExecuteTest();
}

GherkinTable 文字列電卓Mock_Feature_0_ExampleTable = GherkinTable(
        L"|数字文字列  |合計|\n"
        L"|            |0   |\n"
        L"|18          |18  |\n"
        L"|1 + 2 + 3   |6   |\n"
        L"|4, 5, 6     |15  |\n"
        L"|7; 8; 9     |24  |\n"
        L"|1, 2; 3     |0   |\n"
        L"|a1 + a2 + a3|0   |");

INSTANTIATE_TEST_CASE_P(
        文字列電卓Mock_Feature_0,
        文字列電卓Mock_Feature_数字文字列の合計,
        testing::ValuesIn(文字列電卓Mock_Feature_0_ExampleTable.Rows()));


