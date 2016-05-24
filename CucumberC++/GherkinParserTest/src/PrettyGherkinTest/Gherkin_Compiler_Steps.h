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

#pragma once

#include "FeatureStepModel.h"
#include "Gherkin_Compiler_TestModel.h"

using namespace bdd;
#ifdef WIN32
#if (_MSC_VER < 1900)   // _MSC_VER == 1900 (Visual Studio 2015, MSVC++ 14.0)
using namespace boost;
#endif
#endif

class Gherkin_Compiler_Steps : public AbstractStepModel
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
        // Step定義headerは_S_である
    void Stepu23450uuu32681uuheaderu12399uu_S_u12391uuu12354uuu12427uu(std::wstring);
        // Step定義Cppは_S_である
    void Stepu23450uuu32681uuCppu12399uu_S_u12391uuu12354uuu12427uu(std::wstring);
        // 本Stepは下記テーブルを引数とする
    void u26412uuStepu12399uuu19979uuu35352uuu12486uuu12540uuu12502uuu12523uuu12434uuu24341uuu25968uuu12392uuu12377uuu12427uu(GherkinTable&);
        // Featureをコンパイルする
    void Featureu12434uuu12467uuu12531uuu12497uuu12452uuu12523uuu12377uuu12427uu();
        // Stepの正規表現は_S_である
    void Stepu12398uuu27491uuu35215uuu34920uuu29694uuu12399uu_S_u12391uuu12354uuu12427uu(std::wstring);
        // Stepは_S_である
    void Stepu12399uu_S_u12391uuu12354uuu12427uu(std::wstring);
        // 下記はdoc_string文字列である
    void u19979uuu35352uuu12399uudoc_stringu25991uuu23383uuu21015uuu12391uuu12354uuu12427uu(std::wstring);
        // _D_と_D_を引数とする
    void _D_u12392uu_D_u12434uuu24341uuu25968uuu12392uuu12377uuu12427uu(double, double);
        // param1とparam2はテーブル列を示す
    void param1u12392uuparam2u12399uuu12486uuu12540uuu12502uuu12523uuu21015uuu12434uuu31034uuu12377uu(GherkinRow&);
        // 数字_D_数字_D_と_S_の三つの引数がある
    void u25968uuu23383uu_D_u25968uuu23383uu_D_u12392uu_S_u12398uuu19977uuu12388uuu12398uuu24341uuu25968uuu12364uuu12354uuu12427uu(double, double, std::wstring);
        // 括弧を含む文内容内容内容
    void u25324uuu24359uuu12434uuu21547uuu12416uuu25991uuu20869uuu23481uuu20869uuu23481uuu20869uuu23481uu();

public:
    void RegisterSteps() override
    {
        Step<std::wstring>(
            L"Step定義headerは(\"[^\"]*\")である",
            function < void(std::wstring) >
            (bind(&Gherkin_Compiler_Steps::Stepu23450uuu32681uuheaderu12399uu_S_u12391uuu12354uuu12427uu, this, _1)));
        Step<std::wstring>(
            L"Step定義Cppは(\"[^\"]*\")である",
            function < void(std::wstring) >
            (bind(&Gherkin_Compiler_Steps::Stepu23450uuu32681uuCppu12399uu_S_u12391uuu12354uuu12427uu, this, _1)));
        Step(
            L"本Stepは下記テーブルを引数とする",
            function < void(GherkinTable&) >
            (bind(&Gherkin_Compiler_Steps::u26412uuStepu12399uuu19979uuu35352uuu12486uuu12540uuu12502uuu12523uuu12434uuu24341uuu25968uuu12392uuu12377uuu12427uu, this, _1)));
        Step(
            L"Featureをコンパイルする",
            function < void() >
            (bind(&Gherkin_Compiler_Steps::Featureu12434uuu12467uuu12531uuu12497uuu12452uuu12523uuu12377uuu12427uu, this)));
        Step<std::wstring>(
            L"Stepの正規表現は(\"[^\"]*\")である",
            function < void(std::wstring) >
            (bind(&Gherkin_Compiler_Steps::Stepu12398uuu27491uuu35215uuu34920uuu29694uuu12399uu_S_u12391uuu12354uuu12427uu, this, _1)));
        Step<std::wstring>(
            L"Stepは(\"[^\"]*\")である",
            function < void(std::wstring) >
            (bind(&Gherkin_Compiler_Steps::Stepu12399uu_S_u12391uuu12354uuu12427uu, this, _1)));
        StepDocString(
            L"下記はdoc string文字列である。",
            function < void(std::wstring) >
            (bind(&Gherkin_Compiler_Steps::u19979uuu35352uuu12399uudoc_stringu25991uuu23383uuu21015uuu12391uuu12354uuu12427uu, this, _1)));
        Step<double, double>(
            L"([-+]?\\d[\\d,]*\\.?\\d*)と([-+]?\\d[\\d,]*\\.?\\d*)を引数とする",
            function < void(double, double) >
            (bind(&Gherkin_Compiler_Steps::_D_u12392uu_D_u12434uuu24341uuu25968uuu12392uuu12377uuu12427uu, this, _1, _2)));
        Step(
            L"<param1>と<param2>はテーブル列を示す",
            function < void(GherkinRow&) >
            (bind(&Gherkin_Compiler_Steps::param1u12392uuparam2u12399uuu12486uuu12540uuu12502uuu12523uuu21015uuu12434uuu31034uuu12377uu, this, _1)));
        Step<double, double, std::wstring>(
            L"数字([-+]?\\d[\\d,]*\\.?\\d*)、数字([-+]?\\d[\\d,]*\\.?\\d*)と(\"[^\"]*\")の三つの引数がある",
            function < void(double, double, std::wstring) >
            (bind(&Gherkin_Compiler_Steps::u25968uuu23383uu_D_u25968uuu23383uu_D_u12392uu_S_u12398uuu19977uuu12388uuu12398uuu24341uuu25968uuu12364uuu12354uuu12427uu, this, _1, _2, _3)));
        Step(
            L"括弧を含む文\\{内容①\\}\\(内容②\\)\\[内容③\\]",
            function < void() >
            (bind(&Gherkin_Compiler_Steps::u25324uuu24359uuu12434uuu21547uuu12416uuu25991uuu20869uuu23481uuu20869uuu23481uuu20869uuu23481uu, this)));
    }

private:
    Gherkin_Compiler_TestModel model;
};

