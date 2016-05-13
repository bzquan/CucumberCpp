#pragma once

#include "FeatureStepModel.h"
#include "文字列電卓_TestModel.h"

using namespace bdd;
#ifdef WIN32
#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
using namespace boost;
#endif
#endif

class 文字列電卓_Steps : public AbstractStepModel
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
    void 数字文字列がある(GherkinRow&);
    void 数字を合計する();
    void 期待結果は合計であること(GherkinRow&);

public:
    void RegisterSteps() override
    {
        Step(
            L"<数字文字列>がある",
            function < void(GherkinRow&) >
            (bind(&文字列電卓_Steps::数字文字列がある, this, _1)));
        Step(
            L"数字を合計する",
            function < void() >
            (bind(&文字列電卓_Steps::数字を合計する, this)));
        Step(
            L"期待結果は<合計>であること",
            function < void(GherkinRow&) >
            (bind(&文字列電卓_Steps::期待結果は合計であること, this, _1)));
    }

private:
    文字列電卓_TestModel model;
};

