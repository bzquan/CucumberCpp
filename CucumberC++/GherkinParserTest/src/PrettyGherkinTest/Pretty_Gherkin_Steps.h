#pragma once

#include "FeatureStepModel.h"
#include "Pretty_Gherkin_TestModel.h"

using namespace bdd;
#ifdef WIN32
#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
using namespace boost;
#endif
#endif

class Pretty_Gherkin_Steps : public AbstractStepModel
{
public:
    void SetUp()
    {
        RegisterSteps();
        model.SetUp();
    }

    void TearDown()
    {
        model.TearDown();
    }

    void ExecuteTest()
    {
        model.Execute();
    }

public:
        // 下記Gherkin文がある
    void u19979uuu35352uuGherkinu25991uuu12364uuu12354uuu12427uu(std::wstring);
        // Gherkin文を整形する
    void Gherkinu25991uuu12434uuu25972uuu24418uuu12377uuu12427uu();
        // 整形後のScenarioにGUIDが追加されること
    void u25972uuu24418uuu24460uuu12398uuScenariou12395uuGUIDu12364uuu36861uuu21152uuu12373uuu12428uuu12427uuu12371uuu12392uu();
        // 整形後のGherkin文は下記である
    void u25972uuu24418uuu24460uuu12398uuGherkinu25991uuu12399uuu19979uuu35352uuu12391uuu12354uuu12427uu(std::wstring);

public:
    void RegisterSteps() override
    {
        StepDocString(
            L"下記Gherkin文がある",
            function < void(std::wstring) >
            (bind(&Pretty_Gherkin_Steps::u19979uuu35352uuGherkinu25991uuu12364uuu12354uuu12427uu, this, _1)));
        Step(
            L"Gherkin文を整形する",
            function < void() >
            (bind(&Pretty_Gherkin_Steps::Gherkinu25991uuu12434uuu25972uuu24418uuu12377uuu12427uu, this)));
        Step(
            L"整形後のScenarioにGUIDが追加されること",
            function < void() >
            (bind(&Pretty_Gherkin_Steps::u25972uuu24418uuu24460uuu12398uuScenariou12395uuGUIDu12364uuu36861uuu21152uuu12373uuu12428uuu12427uuu12371uuu12392uu, this)));
        StepDocString(
            L"整形後のGherkin文は下記である",
            function < void(std::wstring) >
            (bind(&Pretty_Gherkin_Steps::u25972uuu24418uuu24460uuu12398uuGherkinu25991uuu12399uuu19979uuu35352uuu12391uuu12354uuu12427uu, this, _1)));
    }

private:
    Pretty_Gherkin_TestModel model;
};

