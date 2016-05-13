#include "文字列電卓Mock_Steps.h"

// <数字文字列>を入力する
void 文字列電卓Mock_Steps::数字文字列を入力する(GherkinRow& row)
{
    model.Input(row[L"数字文字列"].strValue());
}

// <合計>が通知されること[[mock]]
void 文字列電卓Mock_Steps::合計が通知されることmock(GherkinRow& row)
{
    model.ExpectedSum(row[L"合計"].intValue());
}


