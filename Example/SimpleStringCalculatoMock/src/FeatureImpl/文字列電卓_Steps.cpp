#include "文字列電卓_Steps.h"

// <数字文字列>がある
void 文字列電卓_Steps::数字文字列がある(GherkinRow& row)
{
    model.Input(row[L"数字文字列"].strValue());
}

// 数字を合計する
void 文字列電卓_Steps::数字を合計する()
{
    model.CalculateSum();
}

// 期待結果は<合計>であること
void 文字列電卓_Steps::期待結果は合計であること(GherkinRow& row)
{
    model.ExpectedSum(row[L"合計"].intValue());
}


