Feature: Gherkin Compiler
GherkinからC++の実行可能な仕様書を生成する。

Background:

  Given Step定義headerは"Gherkinコンパイル_Steps.h"である
  Given Step定義Cppは"Gherkinコンパイル_Steps.cpp"である

@guid-e3aed304-c496-46d2-ae6b-e85c01414359
Scenario: テーブル引数のStep
  テーブルを使用したStep関数にはテーブルの引数がある

  Given 本Stepは下記テーブルを引数とする
    |Col1|Col2 |三列目|
    |IBM |25   |USD   |
    |Sony|1,500|JPY   |
  When Featureをコンパイルする
  Then Stepの正規表現は"本Stepは下記テーブルを引数とする"である
  And Stepは"void 本Stepは下記テーブルを引数とする(GherkinTable&)"である

@guid-e7960b64-23ab-40c9-aea5-0d41f61ca06e
Scenario: doc string文字列引数
 Doc stringを使用したStep関数には文字列の引数がある
 Doc stringの行と行の間には「"\n"」が追加される。

  Given 下記はdoc string文字列である。
    """
    文字列-Doc String1
    文字列-Doc String2
    """
  When Featureをコンパイルする
  Then Stepの正規表現は"下記はdoc string文字列である。"である
  And Stepは"void 下記はdoc_string文字列である(wstring)"である

@guid-dd114170-e9df-40a2-b68b-8d6cc7270a92
Scenario: 数字引数のStep
 数字を使用した関数にはdouble型の引数がある。
 なお、数字では","が使用できる。

  Given 5,000と5,000,000.66を引数とする
  When Featureをコンパイルする
  Then Stepの正規表現は"([-+]?\\d[\\d,]*\\.?\\d*)と([-+]?\\d[\\d,]*\\.?\\d*)を引数とする"である
  And Stepは"void _D_と_D_を引数とする(double, double)"である

@guid-ee132945-0ba8-457c-bf60-68070edcba95
# comment
Scenario Outline: テーブル行引数のStep
 exampleテーブル列を使用した関数にはGherkinRow型の引数がある。
 Stepに複数のテーブル列が参照されても、Step関数にはGherkinRowが一個のみである。

  Given <param1>と<param2>はテーブル列を示す
  When Featureをコンパイルする
   # comment
  Then Stepの正規表現は"<param1>と<param2>はテーブル列を示す"である
  And Stepは"void param1とparam2はテーブル列を示す(GherkinRow&)"である

  Examples: "Scenario Outline"のテーブル
# comment
    |param1|param2|Sum|
    |3     |3     |6  |
# comment
    |3     |5     |8  |

@guid-9684f4e1-1004-4316-b4a1-b4e1d697ba89
Scenario: 数字と文字列混在の引数
 Stepでは数字と文字列が混在した引数が使用できる。
 備考：文字列の正規表現には「"」が含まれるため、Stepの正規表現は確認せず
 正規表現："数字([-+]?\\d[\\d,]*\\.?\\d*)、数字([-+]?\\d[\\d,]*\\.?\\d*)と(\"[^\"]*\")の三つの引数がある"

  Given 数字+123、数字-456と"文字列引数"の三つの引数がある
  When Featureをコンパイルする
#  Then Stepの正規表現は"数字([-+]?\\d[\\d,]*\\.?\\d*)、数字([-+]?\\d[\\d,]*\\.?\\d*)と(\"[^\"]*\")の三つの引数がある"である
  Then Stepは"void 数字_D_数字_D_と_S_の三つの引数がある(double, double, wstring)"である

@guid-bf35f843-bcfb-4f01-83a4-56c8dda9cea5
Scenario: Step文に括弧がある
Step文内の括弧は正規表現でEscapeにて表現する。

  Given 括弧を含む文{内容①}(内容②)[内容③]
  When Featureをコンパイルする
  Then Stepの正規表現は"括弧を含む文\\{内容①\\}\\(内容②\\)\\[内容③\\]"である
  And Stepは"void 括弧を含む文内容内容内容()"である
