#pragma once

#include "FeatureStepModel.h"
#include "String_calculator_using_mock_object_TestModel.h"

using namespace bdd;
#ifdef WIN32
#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
using namespace boost;
#endif
#endif

class String_calculator_using_mock_object_Steps : public AbstractStepModel
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
    void Input_Numbers(GherkinRow&);
    void The_result_Sum_shall_be_informedmock(GherkinRow&);

public:
    void RegisterSteps() override
    {
        Step(
            L"Input <Numbers>",
            function < void(GherkinRow&) >
            (bind(&String_calculator_using_mock_object_Steps::Input_Numbers, this, _1)));
        Step(
            L"The result <Sum> shall be informed\\[\\[mock\\]\\]",
            function < void(GherkinRow&) >
            (bind(&String_calculator_using_mock_object_Steps::The_result_Sum_shall_be_informedmock, this, _1)));
    }

private:
    String_calculator_using_mock_object_TestModel model;
};

