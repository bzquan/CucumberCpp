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


