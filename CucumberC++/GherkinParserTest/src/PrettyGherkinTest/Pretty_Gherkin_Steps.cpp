#include "Pretty_Gherkin_Steps.h"

// 下記Gherkin文がある
//-- Pretty_Gherkin_Steps::下記Gherkin文がある(std::wstring docStr)
void Pretty_Gherkin_Steps::u19979uuu35352uuGherkinu25991uuu12364uuu12354uuu12427uu(std::wstring docStr)
{
    model.GivenGherkin(docStr);
}

// Gherkin文を整形する
//-- Pretty_Gherkin_Steps::Gherkin文を整形する()
void Pretty_Gherkin_Steps::Gherkinu25991uuu12434uuu25972uuu24418uuu12377uuu12427uu()
{
    model.MakePrettyGherkin();
}

// 整形後のScenarioにGUIDが追加されること
//-- Pretty_Gherkin_Steps::整形後のScenarioにGUIDが追加されること()
void Pretty_Gherkin_Steps::u25972uuu24418uuu24460uuu12398uuScenariou12395uuGUIDu12364uuu36861uuu21152uuu12373uuu12428uuu12427uuu12371uuu12392uu()
{
    model.ExpectNewGUIDCreated();
}

// 整形後のGherkin文は下記である
//-- Pretty_Gherkin_Steps::整形後のGherkin文は下記である(std::wstring docStr)
void Pretty_Gherkin_Steps::u25972uuu24418uuu24460uuu12398uuGherkinu25991uuu12399uuu19979uuu35352uuu12391uuu12354uuu12427uu(std::wstring docStr)
{
    model.ExpectFormattedGherkin(docStr);
}


