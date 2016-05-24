/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifdef WIN32
// Disable warning C4819: The file contains a character that cannot be represented in the current code page
#pragma warning(disable : 4819)
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
    Pretty_Gherkin_Steps steps;
};

TEST_F(Pretty_Gherkin_Feature, GUIDなしのGherkin)
{
    Spec("@guid-09204ed5-1af8-472c-8f3f-3b564c2a3aae");


    std::wstring docString0 = L"    Feature : 機能概要\n"
                              L"    Scenario : title\n"
                              L"    Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: 機能概要\n"
                              L"\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  Given 前提条件";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, GUIDありのGherkin)
{
    Spec("@guid-25558861-e8c0-46df-bca2-2b5c524791be");


    std::wstring docString0 = L"    Feature : 機能概要\n"
                              L"    @guid-25558861-e8c0-46df-bca2-2b5c524791be\n"
                              L"    Scenario : title\n"
                              L"    Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");

    std::wstring docString1 = L"Feature: 機能概要\n"
                              L"\n"
                              L"@guid-25558861-e8c0-46df-bca2-2b5c524791be\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  Given 前提条件";
    Then(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, FeatureのTag)
{
    Spec("@guid-d4f6d044-762b-4714-9aa4-f12935cf8ced");


    std::wstring docString0 = L"    @tag1\n"
                              L"    @tag2\n"
                              L"    Feature : 機能概要\n"
                              L"    Scenario : title\n"
                              L"    Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"@tag1 @tag2\n"
                              L"Feature: 機能概要\n"
                              L"\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  Given 前提条件";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, FeatureのBackground)
{
    Spec("@guid-4e299a51-b12c-412c-bf38-8f54c60207cb");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"\n"
                              L"    Background: background title\n"
                              L"    Description of background\n"
                              L"    Given precondition\n"
                              L"\n"
                              L"    @guid-xxxxx\n"
                              L"    Scenario : title\n"
                              L"    When action";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"\n"
                              L"Background: background title\n"
                              L"    Description of background\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"\n"
                              L"@guid-xxxxx\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  When action";
    Then(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, ScenarioのTagは最後尾に)
{
    Spec("@guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558");


    std::wstring docString0 = L"    Feature : 機能概要\n"
                              L"    @guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558\n"
                              L"    @tag1\n"
                              L"    Scenario : title\n"
                              L"    Given 前提条件";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");

    std::wstring docString1 = L"Feature: 機能概要\n"
                              L"\n"
                              L"@tag1\n"
                              L"@guid-d5e16284-9fdb-4db0-bbe5-f01e3bac9558\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  Given 前提条件";
    Then(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, 複数のScenario)
{
    Spec("@guid-dd9cce71-75cb-4375-84db-abf98ee5d1b3");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"    Background: background title\n"
                              L"    Given precondition\n"
                              L"    Scenario : title1\n"
                              L"    Given precondition\n"
                              L"    Scenario : title2\n"
                              L"    Description of scenario2\n"
                              L"    Given precondition\n"
                              L"    When action\n"
                              L"    Then expectation";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"\n"
                              L"Background: background title\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"\n"
                              L"Scenario: title1\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"\n"
                              L"Scenario: title2\n"
                              L"    Description of scenario2\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"  When action\n"
                              L"  Then expectation";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, DocString_argument)
{
    Spec("@guid-6bb754fa-1838-4c87-8716-390f441dc0a1");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"    Scenario : title\n"
                              L"    Given precondition\n"
                              L"    ^\"\"\"\n"
                              L"    line1\n"
                              L"    line2\n"
                              L"    ^\"\"\"";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"^    \"\"\"\n"
                              L"    line1\n"
                              L"    line2\n"
                              L"^    \"\"\"";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, Table_argument)
{
    Spec("@guid-d0908cd3-0ac3-44c0-af91-161b306ac151");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"    Scenario : title\n"
                              L"    Given precondition\n"
                              L"    |col1|col2|\n"
                              L"    |v11|v12|\n"
                              L"    |v21|v22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"    |col1|col2|\n"
                              L"    |v11 |v12 |\n"
                              L"    |v21 |v22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, 規則性なしのTable_argument)
{
    Spec("@guid-adbfcca8-6ca6-4f78-8511-6032fa9f7473");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"    Scenario : title\n"
                              L"    Given precondition\n"
                              L"    |col1|col2|\n"
                              L"    |v11abc|v12|\n"
                              L"    |v21|v22abc|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"    |col1  |col2  |\n"
                              L"    |v11abc|v12   |\n"
                              L"    |v21   |v22abc|";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, CommentありのGherkin)
{
    Spec("@guid-2f7ad31c-346e-4fde-bf8e-c14b1b449580");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"    Description of feature\n"
                              L"    # comment1\n"
                              L"    Scenario : title\n"
                              L"    // comment2\n"
                              L"    Given precondition\n"
                              L"    |col1|col2|\n"
                              L"    |v11|v12|\n"
                              L"    |v21|v22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"    Description of feature\n"
                              L"    # comment1\n"
                              L"\n"
                              L"Scenario: title\n"
                              L"\n"
                              L"    // comment2\n"
                              L"  Given precondition\n"
                              L"    |col1|col2|\n"
                              L"    |v11 |v12 |\n"
                              L"    |v21 |v22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, scenario_outline)
{
    Spec("@guid-ed3062ed-df5c-4bd5-8740-c1bd7eae7386");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"    Scenario Outline: title\n"
                              L"    Description of scenario outline\n"
                              L"    Given precondition\n"
                              L"    Examples:\n"
                              L"    |col1|col2|\n"
                              L"    |v11|v12|\n"
                              L"    |v21|v22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"\n"
                              L"Scenario Outline: title\n"
                              L"    Description of scenario outline\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"\n"
                              L"  Examples:\n"
                              L"    |col1|col2|\n"
                              L"    |v11 |v12 |\n"
                              L"    |v21 |v22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}

TEST_F(Pretty_Gherkin_Feature, scenario_outline_with_multi_examples)
{
    Spec("@guid-28675d82-8d7a-4e50-b87b-54835112e155");


    std::wstring docString0 = L"    Feature : feature title\n"
                              L"    Scenario Outline: title\n"
                              L"    Given precondition\n"
                              L"    Examples: example1\n"
                              L"    |col1|col2|\n"
                              L"    |v11|v12|\n"
                              L"    |v21|v22|\n"
                              L"    Examples: example2\n"
                              L"    |col1|col2|\n"
                              L"    |b11|b12|\n"
                              L"    |b21|b22|";
    Given(L"下記Gherkin文がある", docString0);
    When(L"Gherkin文を整形する");
    Then(L"整形後のScenarioにGUIDが追加されること");

    std::wstring docString1 = L"Feature: feature title\n"
                              L"\n"
                              L"Scenario Outline: title\n"
                              L"\n"
                              L"  Given precondition\n"
                              L"\n"
                              L"  Examples: example1\n"
                              L"    |col1|col2|\n"
                              L"    |v11 |v12 |\n"
                              L"    |v21 |v22 |\n"
                              L"\n"
                              L"  Examples: example2\n"
                              L"    |col1|col2|\n"
                              L"    |b11 |b12 |\n"
                              L"    |b21 |b22 |";
    And(L"整形後のGherkin文は下記である", docString1);
    ExecuteTest();
}


