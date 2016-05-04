#ifdef WIN32
// Disable warning C4800: 'int' : forcing value to bool 'true' or 'false'(performance warning)
#pragma warning(disable : 4800)
#endif

#include "FeatureTestModel.h"
#include "Pretty_Gherkin_Steps.h"


// Pretty_Gherkin_Feature

class Pretty_Gherkin_Feature : public FeatureTestModel
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
    // Pretty_Gherkin_Steps steps;
    Pretty_Gherkin_Steps steps;
};

// TEST_F(Pretty_Gherkin_Feature, GUIDなしのGherkin)
TEST_F(Pretty_Gherkin_Feature, GUIDu12394uuu12375uuu12398uuGherkin)
{
    Spec("@guid-09204ed5-1af8-472c-8f3f-3b564c2a3aae");


    std::wstring docString0 = L"Feature : 機能概要"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: 機能概要"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given 前提条件";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, GUIDありのGherkin)
TEST_F(Pretty_Gherkin_Feature, GUIDu12354uuu12426uuu12398uuGherkin)
{
    Spec("@guid-25558861-e8c0-46df-bca2-2b5c524791be");


    std::wstring docString0 = L"Feature : 機能概要"
                              L"\n"
                              L"@guid-25558861-e8c0-46df-bca2-2b5c524791be"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");

    std::wstring docString1 = L"Feature: 機能概要"
                              L"\n"
                              L""
                              L"\n"
                              L"@guid-25558861-e8c0-46df-bca2-2b5c524791be"
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given 前提条件";
    Then(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, FeatureのTag)
TEST_F(Pretty_Gherkin_Feature, Featureu12398uuTag)
{
    Spec("@guid-d4f6d044-762b-4714-9aa4-f12935cf8ced");


    std::wstring docString0 = L"@tag1"
                              L"\n"
                              L"@tag2"
                              L"\n"
                              L"Feature : 機能概要"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"@tag1 @tag2"
                              L"\n"
                              L"Feature: 機能概要"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given 前提条件";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, FeatureのBackground)
TEST_F(Pretty_Gherkin_Feature, Featureu12398uuBackground)
{
    Spec("@guid-4e299a51-b12c-412c-bf38-8f54c60207cb");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Background: background title"
                              L"\n"
                              L"Description of background"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L""
                              L"\n"
                              L"@guid-xxxxx"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"When action";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Background: background title"
                              L"\n"
                              L"Description of background"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L""
                              L"\n"
                              L"@guid-xxxxx"
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  When action";
    Then(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, ScenarioのTagは最後尾に)
TEST_F(Pretty_Gherkin_Feature, Scenariou12398uuTagu12399uuu26368uuu24460uuu23614uuu12395uu)
{
    Spec("@guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558");


    std::wstring docString0 = L"Feature : 機能概要"
                              L"\n"
                              L"@guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558"
                              L"\n"
                              L"@tag1"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");

    std::wstring docString1 = L"Feature: 機能概要"
                              L"\n"
                              L""
                              L"\n"
                              L"@tag1"
                              L"\n"
                              L"@guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558"
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given 前提条件";
    Then(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, 複数のScenario)
TEST_F(Pretty_Gherkin_Feature, u35079uuu25968uuu12398uuScenario)
{
    Spec("@guid-dd9cce71-75cb-4375-84db-abf98ee5d1b3");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L"Background: background title"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"Scenario : title1"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"Scenario : title2"
                              L"\n"
                              L"Description of scenario2"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"When action"
                              L"\n"
                              L"Then expectation";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Background: background title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title1"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title2"
                              L"\n"
                              L"Description of scenario2"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L"^  When action"
                              L"\n"
                              L"^  Then expectation";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, DocString_argument)
TEST_F(Pretty_Gherkin_Feature, DocString_argument)
{
    Spec("@guid-6bb754fa-1838-4c87-8716-390f441dc0a1");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"^\"\"\""
                              L"\n"
                              L"line1"
                              L"\n"
                              L"line2"
                              L"\n"
                              L"^\"\"\"";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L"^    \"\"\""
                              L"\n"
                              L"^    line1"
                              L"\n"
                              L"^    line2"
                              L"\n"
                              L"^    \"\"\"";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, Table_argument)
TEST_F(Pretty_Gherkin_Feature, Table_argument)
{
    Spec("@guid-d0908cd3-0ac3-44c0-af91-161b306ac151");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"|col1|col2|"
                              L"\n"
                              L"|v11|v12|"
                              L"\n"
                              L"|v21|v22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L"^    |col1|col2|"
                              L"\n"
                              L"^    |v11 |v12 |"
                              L"\n"
                              L"^    |v21 |v22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, 規則性なしのTable_argument)
TEST_F(Pretty_Gherkin_Feature, u35215uuu21063uuu24615uuu12394uuu12375uuu12398uuTable_argument)
{
    Spec("@guid-adbfcca8-6ca6-4f78-8511-6032fa9f7473");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"|col1|col2|"
                              L"\n"
                              L"|v11abc|v12|"
                              L"\n"
                              L"|v21|v22abc|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L"^    |col1  |col2  |"
                              L"\n"
                              L"^    |v11abc|v12   |"
                              L"\n"
                              L"^    |v21   |v22abc|";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, CommentありのGherkin)
TEST_F(Pretty_Gherkin_Feature, Commentu12354uuu12426uuu12398uuGherkin)
{
    Spec("@guid-2f7ad31c-346e-4fde-bf8e-c14b1b449580");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L"Description of feature"
                              L"\n"
                              L"# comment1"
                              L"\n"
                              L"Scenario : title"
                              L"\n"
                              L"// comment2"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"|col1|col2|"
                              L"\n"
                              L"|v11|v12|"
                              L"\n"
                              L"|v21|v22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L"Description of feature"
                              L"\n"
                              L"# comment1"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario: title"
                              L"\n"
                              L""
                              L"\n"
                              L"// comment2"
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L"^    |col1|col2|"
                              L"\n"
                              L"^    |v11 |v12 |"
                              L"\n"
                              L"^    |v21 |v22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, scenario_outline)
TEST_F(Pretty_Gherkin_Feature, scenario_outline)
{
    Spec("@guid-ed3062ed-df5c-4bd5-8740-c1bd7eae7386");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L"Scenario Outline: title"
                              L"\n"
                              L"Description of scenario outline"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"Examples:"
                              L"\n"
                              L"|col1|col2|"
                              L"\n"
                              L"|v11|v12|"
                              L"\n"
                              L"|v21|v22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario Outline: title"
                              L"\n"
                              L"Description of scenario outline"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L"^"
                              L"\n"
                              L"^  Examples:"
                              L"\n"
                              L"^    |col1|col2|"
                              L"\n"
                              L"^    |v11 |v12 |"
                              L"\n"
                              L"^    |v21 |v22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

// TEST_F(Pretty_Gherkin_Feature, scenario_outline_with_multi_examples)
TEST_F(Pretty_Gherkin_Feature, scenario_outline_with_multi_examples)
{
    Spec("@guid-28675d82-8d7a-4e50-b87b-54835112e155");


    std::wstring docString0 = L"Feature : feature title"
                              L"\n"
                              L"Scenario Outline: title"
                              L"\n"
                              L"Given precondition"
                              L"\n"
                              L"Examples: example1"
                              L"\n"
                              L"|col1|col2|"
                              L"\n"
                              L"|v11|v12|"
                              L"\n"
                              L"|v21|v22|"
                              L"\n"
                              L"Examples: example2"
                              L"\n"
                              L"|col1|col2|"
                              L"\n"
                              L"|b11|b12|"
                              L"\n"
                              L"|b21|b22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title"
                              L"\n"
                              L""
                              L"\n"
                              L"Scenario Outline: title"
                              L"\n"
                              L""
                              L"\n"
                              L"^  Given precondition"
                              L"\n"
                              L"^"
                              L"\n"
                              L"^  Examples: example1"
                              L"\n"
                              L"^    |col1|col2|"
                              L"\n"
                              L"^    |v11 |v12 |"
                              L"\n"
                              L"^    |v21 |v22 |"
                              L"\n"
                              L"^"
                              L"\n"
                              L"^  Examples: example2"
                              L"\n"
                              L"^    |col1|col2|"
                              L"\n"
                              L"^    |b11 |b12 |"
                              L"\n"
                              L"^    |b21 |b22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}


