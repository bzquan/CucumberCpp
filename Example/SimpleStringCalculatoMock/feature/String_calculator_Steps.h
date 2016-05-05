#pragma once

#include "FeatureStepModel.h"
#include "String_calculator_TestModel.h"

using namespace bdd;
#ifdef WIN32
#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
using namespace boost;
#endif
#endif

class String_calculator_Steps : public AbstractStepModel
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
    void Enter_Numbers_with_separator(GherkinRow&);
    void Sum_all_the_numbers();
    void The_result_Sum_shall_be_informedmock(GherkinRow&);

public:
    void RegisterSteps() override
    {
        Step(
            L"Enter <Numbers> with separator",
            function < void(GherkinRow&) >
            (bind(&String_calculator_Steps::Enter_Numbers_with_separator, this, _1)));
        Step(
            L"Sum all the numbers",
            function < void() >
            (bind(&String_calculator_Steps::Sum_all_the_numbers, this)));
        Step(
            L"The result <Sum> shall be informed\\[\\[mock\\]\\]",
            function < void(GherkinRow&) >
            (bind(&String_calculator_Steps::The_result_Sum_shall_be_informedmock, this, _1)));
    }

private:
    String_calculator_TestModel model;
};

