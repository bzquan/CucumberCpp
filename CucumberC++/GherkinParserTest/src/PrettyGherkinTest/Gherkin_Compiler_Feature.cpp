#ifdef WIN32
// Disable warning C4800: 'int' : forcing value to bool 'true' or 'false'(performance warning)
#pragma warning(disable : 4800)
#endif

#include "FeatureTestModel.h"
#include "Gherkin_Compiler_Steps.h"


// Gherkin_Compiler_Feature

class Gherkin_Compiler_Feature : public FeatureTestModel
{
public:
    void SetUp() override
    {
        steps.SetUp();
        FeatureBackground();
    }
    void TearDown() override
    {
        steps.TearDown();
    }

protected:
    AbstractStepModel* GetStepModel() override
    {
        return &steps;
    }

    void FeatureBackground()
    {
        Given(L"Step定義headerは\"Gherkinコンパイル_Steps.h\"である");
        Given(L"Step定義Cppは\"Gherkinコンパイル_Steps.cpp\"である");
    }

    void ExecuteTest()
    {
        steps.ExecuteTest();
    }

private:
    // Gherkin_Compiler_Steps steps;
    Gherkin_Compiler_Steps steps;
};

// TEST_F(Gherkin_Compiler_Feature, テーブル引数のStep)
TEST_F(Gherkin_Compiler_Feature, u12486uuu12540uuu12502uuu12523uuu24341uuu25968uuu12398uuStep)
{
    Spec("@guid-e3aed304-c496-46d2-ae6b-e85c01414359");


    GherkinTable table0;
    table0
    //            |Col1|Col2 |Col3|
        .AddRow(L"|IBM |25   |USD |")
        .AddRow(L"|Sony|1,500|JPY |");
    Given(L"本Stepは下記テーブルを引数とする", table0);
    When(L"Featureをコンパイルする");
    Then(L"Stepの正規表現は\"本Stepは下記テーブルを引数とする\"である");
    And(L"Stepは\"void 本Stepは下記テーブルを引数とする(GherkinTable&)\"である");
    ExecuteTest();
}

// TEST_F(Gherkin_Compiler_Feature, doc_string文字列引数)
TEST_F(Gherkin_Compiler_Feature, doc_stringu25991uuu23383uuu21015uuu24341uuu25968uu)
{
    Spec("@guid-e7960b64-23ab-40c9-aea5-0d41f61ca06e");


    std::wstring docString0 = L"文字列-Doc String1"
                              L"\n"
                              L"文字列-Doc String2";
    Given(L"下記はdoc string文字列である。", docString0);
    When(L"Featureをコンパイルする");
    Then(L"Stepの正規表現は\"下記はdoc string文字列である。\"である");
    And(L"Stepは\"void 下記はdoc_string文字列である(wstring)\"である");
    ExecuteTest();
}

// TEST_F(Gherkin_Compiler_Feature, 数字引数のStep)
TEST_F(Gherkin_Compiler_Feature, u25968uuu23383uuu24341uuu25968uuu12398uuStep)
{
    Spec("@guid-dd114170-e9df-40a2-b68b-8d6cc7270a92");

    Given(L"5,000と5,000,000.66を引数とする");
    When(L"Featureをコンパイルする");
    Then(L"Stepの正規表現は\"([-+]?\\d[\\d,]*\\.?\\d*)と([-+]?\\d[\\d,]*\\.?\\d*)を引数とする\"である");
    And(L"Stepは\"void _D_と_D_を引数とする(double, double)\"である");
    ExecuteTest();
}

// Gherkin_Compiler_Feature_テーブル行引数のStep : Gherkin_Compiler_Feature
class Gherkin_Compiler_Feature_u12486uuu12540uuu12502uuu12523uuu34892uuu24341uuu25968uuu12398uuStep :
    public Gherkin_Compiler_Feature,
    public WithParamInterface<GherkinRow>
{
public:
    void SetUp() override
    {
//         Gherkin_Compiler_Feature::SetUp();
        Gherkin_Compiler_Feature::SetUp();
        Spec("@guid-ee132945-0ba8-457c-bf60-68070edcba95");
    }
};

// TEST_P(Gherkin_Compiler_Feature_テーブル行引数のStep, ScenarioOutline)
TEST_P(Gherkin_Compiler_Feature_u12486uuu12540uuu12502uuu12523uuu34892uuu24341uuu25968uuu12398uuStep, ScenarioOutline)
{
    GherkinRow param = GetParam();

    Given(L"<param1>と<param2>はテーブル列を示す", param);
    When(L"Featureをコンパイルする");
    Then(L"Stepの正規表現は\"<param1>と<param2>はテーブル列を示す\"である");
    And(L"Stepは\"void param1とparam2はテーブル列を示す(GherkinRow&)\"である");
    ExecuteTest();
}

// Gherkin_Compiler_Feature_0
INSTANTIATE_TEST_CASE_P(
        Gherkin_Compiler_Feature_0,
// Gherkin_Compiler_Feature_u12486uuu12540uuu12502uuu12523uuu34892uuu24341uuu25968uuu12398uuStep
        Gherkin_Compiler_Feature_u12486uuu12540uuu12502uuu12523uuu34892uuu24341uuu25968uuu12398uuStep,
        Values(//      |param1|param2|Sum|
// GherkinRow
          GherkinRow(L"|3     |3     |6  |"),
// GherkinRow
          GherkinRow(L"|3     |5     |8  |")
        ));


// TEST_F(Gherkin_Compiler_Feature, 数字と文字列混在の引数)
TEST_F(Gherkin_Compiler_Feature, u25968uuu23383uuu12392uuu25991uuu23383uuu21015uuu28151uuu22312uuu12398uuu24341uuu25968uu)
{
    Spec("@guid-9684f4e1-1004-4316-b4a1-b4e1d697ba89");

    Given(L"数字+123、数字-456と\"文字列引数\"の三つの引数がある");
    When(L"Featureをコンパイルする");
    Then(L"Stepは\"void 数字_D_数字_D_と_S_の三つの引数がある(double, double, wstring)\"である");
    ExecuteTest();
}

// TEST_F(Gherkin_Compiler_Feature, Step文に括弧がある)
TEST_F(Gherkin_Compiler_Feature, Stepu25991uuu12395uuu25324uuu24359uuu12364uuu12354uuu12427uu)
{
    Spec("@guid-bf35f843-bcfb-4f01-83a4-56c8dda9cea5");

    Given(L"括弧を含む文{内容①}(内容②)[内容③]");
    When(L"Featureをコンパイルする");
    Then(L"Stepの正規表現は\"括弧を含む文\\{内容①\\}\\(内容②\\)\\[内容③\\]\"である");
    And(L"Stepは\"void 括弧を含む文内容内容内容()\"である");
    ExecuteTest();
}


