#pragma once

#include "FeatureStepModel.h"
#include "文字列電卓Mock_TestModel.h"

using namespace bdd;
#ifdef WIN32
#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
using namespace boost;
#endif
#endif

class 文字列電卓Mock_Steps : public AbstractStepModel
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
    void 数字文字列を入力する(GherkinRow&);
    void 合計が通知されることmock(GherkinRow&);

public:
    void RegisterSteps() override
    {
        Step(
            L"<数字文字列>を入力する",
            function < void(GherkinRow&) >
            (bind(&文字列電卓Mock_Steps::数字文字列を入力する, this, _1)));
        Step(
            L"<合計>が通知されること\\[\\[mock\\]\\]",
            function < void(GherkinRow&) >
            (bind(&文字列電卓Mock_Steps::合計が通知されることmock, this, _1)));
    }

private:
    文字列電卓Mock_TestModel model;
};

