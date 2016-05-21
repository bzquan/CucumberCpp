#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <regex>
#include <sstream>
#include "Comment.h"
#include "Feature.h"
#include "GherkinParser.h"
#include "GherkinLexer.h"

using namespace std;
using namespace testing;
using namespace GherkinAst;

int yylex(void);

class yylexTest : public testing::Test {
public:
    virtual void SetUp(){}
    virtual void TearDown(){}

protected:
    yytokentype skipToken()
    {
        yytokentype token = (yytokentype)yylex();    // skip a token
        delete yylval.pwstr;
        return token;
    }

protected:
    GherkinParser parser;
};

TEST_F(yylexTest, LanguageToken)
{
    // Given
    wistringstream is(L"# language: en");
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(LANGUAGE, token);
    ASSERT_EQ(wstring(L"en"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, TagLine)
{
    // Given
    wstring str{ L"@tag" };
    wistringstream is(str);
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(TAG_LINE, token);
    ASSERT_EQ(str, *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, MultiTagsLine)
{
    // Given
    wistringstream is(L"  @tag1 @tag2  ");
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(TAG_LINE, token);
    ASSERT_EQ(wstring(L"@tag1 @tag2"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, MultiTagLines)
{
    // Given
    wistringstream is(
        L"@tag1\n"
        L"@tag2");
    GherkinLexer lexer(is, parser);

    // When
    skipToken();    // skip first tag
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(TAG_LINE, token);
    ASSERT_EQ(wstring(L"@tag2"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, FeatureLine)
{
    // Given
    wistringstream is{ L"  Feature: title  " };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(FEATURE_LINE, token);
    ASSERT_EQ(wstring(L"title"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, FeatureLine_JP)
{
    // Given
    wistringstream is{ L"  Feature: 機能概要  " };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(FEATURE_LINE, token);
    ASSERT_EQ(wstring(L"機能概要"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, Description)
{
    // Given
    wistringstream is{
        L"Feature: title\n"
        L" 説明文一行目 \n"
        L"\n"
        L" 説明文二行目 \n"
    };
    GherkinLexer lexer(is, parser);

    // When
    skipToken();    // skip Feature
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(DECRIPTION, token);
    ASSERT_EQ(wstring(L" 説明文一行目\n\n 説明文二行目"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, Background_no_title)
{
    // Given
    wistringstream is{
        L"Feature: title\n"
        L"説明文一行目\n"
        L"  Background:"
    };
    GherkinLexer lexer(is, parser);

    // When
    skipToken();    // skip Feature
    skipToken();    // skip Feature description

    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(BACKGROUND_LINE, token);
    ASSERT_EQ(wstring(), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, Background_has_title)
{
    // Given
    wistringstream is{
        L"Feature: title\n"
        L"説明文一行目\n"
        L"  Background  : 前提条件 "
    };
    GherkinLexer lexer(is, parser);

    // When
    skipToken();                // skip Feature
    yytokentype desc_token = skipToken();   // description
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(DECRIPTION, desc_token);
    ASSERT_EQ(BACKGROUND_LINE, token);
    ASSERT_EQ(wstring(L"前提条件"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, ScenarioLine)
{
    // Given
    wistringstream is{ L"Scenario: シナリオタイトル" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(SCENARIO_LINE, token);
    ASSERT_EQ(wstring(L"シナリオタイトル"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, ScenarioOutLine)
{
    // Given
    wistringstream is{ L"Scenario Outline: シナリオタイトル" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(SCENARIO_OUTLINE_LINE, token);
    ASSERT_EQ(wstring(L"シナリオタイトル"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, GivenStep)
{
    // Given
    wistringstream is{ L"Given 前提条件" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(GIVEN_STEP, token);
    ASSERT_EQ(wstring(L"前提条件"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, WhenStep)
{
    // Given
    wistringstream is{ L"When 動作" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(WHEN_STEP, token);
    ASSERT_EQ(wstring(L"動作"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, ThenStep)
{
    // Given
    wistringstream is{ L"Then 期待結果" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(THEN_STEP, token);
    ASSERT_EQ(wstring(L"期待結果"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, AndStep)
{
    // Given
    wistringstream is{ L"And 続き" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(AND_STEP, token);
    ASSERT_EQ(wstring(L"続き"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, ButStep)
{
    // Given
    wistringstream is{ L"But 続き" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(BUT_STEP, token);
    ASSERT_EQ(wstring(L"続き"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, DocString)
{
    // Given
    wistringstream is{
        L"\"\"\"\n"
        L"Doc string1\n"
        L" Doc string2 \n"
        L"\"\"\"\n"
    };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(DOC_STRING, token);
    wstring expected{
        L"Doc string1\n"
        L" Doc string2"
    };
    ASSERT_EQ(expected, yylval.pDocStringParam->content);
    delete yylval.pDocStringParam;
}

TEST_F(yylexTest, DocString_with_quotation)
{
    // Given
    wistringstream is{
        L"\"\"\"\n"
        L"Doc \"string1\"\n"
        L" Doc \"string2\" \n"
        L"\"\"\"\n"
    };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(DOC_STRING, token);
    wstring expected{
        L"Doc \"string1\"\n"
        L" Doc \"string2\""
    };
    ASSERT_EQ(expected, yylval.pDocStringParam->content);
    delete yylval.pDocStringParam;
}

TEST_F(yylexTest, DocString_with_type)
{
    // Given
    wistringstream is{
        L"\"\"\"jason\n"
        L"Doc string1\n"
        L" Doc string2 \n"
        L"\"\"\"\n"
    };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(DOC_STRING, token);
    wstring expected{
        L"Doc string1\n"
        L" Doc string2"
    };
    ASSERT_EQ(expected, yylval.pDocStringParam->content);
    ASSERT_EQ(wstring(L"jason"), yylval.pDocStringParam->contentType);
    delete yylval.pDocStringParam;
}

TEST_F(yylexTest, KeywordAfterDocString)
{
    // Given
    wistringstream is{
        L"\"\"\"\n"
        L"Doc string1\n"
        L" Doc string2 \n"
        L"\"\"\"\n"
        L"Given 前提条件"
    };
    GherkinLexer lexer(is, parser);

    // When
    skipToken();    // skip DocString
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(GIVEN_STEP, token);
    ASSERT_EQ(wstring(L"前提条件"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, TableRow)
{
    // Given
    wistringstream is{ L"|Col1|Col2 |Col3|" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(TABLE_ROW, token);
    ASSERT_EQ(wstring(L"|Col1|Col2 |Col3|"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, TableRow_empty)
{
    // Given
    wistringstream is{ L"|||" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(TABLE_ROW, token);
    ASSERT_EQ(wstring(L"|||"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, TableRow_Bad_without_ending_delimiter)
{
    // Given
    wistringstream is{ L"  |Col1|Col2 |Col3" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(DECRIPTION, token);
    ASSERT_EQ(wstring(L"  |Col1|Col2 |Col3"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, ExampleLine_no_title)
{
    // Given
    wistringstream is{ L" Examples: " };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(EXAMPLE_LINE, token);
    ASSERT_EQ(wstring(), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, ExampleLine_have_title)
{
    // Given
    wistringstream is{ L" Examples : タイトル" };
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(EXAMPLE_LINE, token);
    ASSERT_EQ(wstring(L"タイトル"), *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, GherkinComment)
{
    // Given
    wistringstream is{ L" # This is Gherkin comment line" };
    GherkinLexer lexer(is, parser);

    // When
    yylex();
    delete yylval.pwstr;

    // Then
    vector<Comment>& comments = parser.astBuilder().Comments();
    ASSERT_EQ((size_t)1, comments.size());
    ASSERT_EQ(1, comments[0].Location().Line());
    ASSERT_EQ(wstring(L" # This is Gherkin comment line"), comments[0].Text());
}

TEST_F(yylexTest, CppComment)
{
    // Given
    wistringstream is{ L"// This is C++ comment line" };
    GherkinLexer lexer(is, parser);

    // When
    yylex();
    delete yylval.pwstr;

    // Then
    vector<Comment>& comments = parser.astBuilder().Comments();
    ASSERT_EQ((size_t)1, comments.size());
    ASSERT_EQ(1, comments[0].Location().Line());
    ASSERT_EQ(wstring(L"// This is C++ comment line"), comments[0].Text());
}

TEST_F(yylexTest, CppMultiComments)
{
    // Given
    wistringstream is{
        L"// This is C++ comment line1\r\n"
        L"// This is C++ comment line2\r\n"
        L"// This is C++ comment line3"
    };
    GherkinLexer lexer(is, parser);

    // When
    skipToken();    // skip 1st comment
    skipToken();    // skip 2nd comment
    yylex();
    delete yylval.pwstr;

    // Then
    vector<Comment>& comments = parser.astBuilder().Comments();
    ASSERT_EQ((size_t)3, comments.size());
    ASSERT_EQ(3, comments[2].Location().Line());
    ASSERT_EQ(wstring(L"// This is C++ comment line3"), comments[2].Text());
}

TEST_F(yylexTest, Comment_within_description_iss_comment)
{
    // Given
    wstring str{
        L"説明文一行目\n"
        L"// This is C++ comment line\n"
        L"説明文二行目"
    };
    wistringstream is(str);
    GherkinLexer lexer(is, parser);

    // When
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(DECRIPTION, token);
    ASSERT_EQ(str, *yylval.pwstr);
    delete yylval.pwstr;
}

TEST_F(yylexTest, Location_with_comment_lines)
{
    // Given
    wstring str{
        L"Feature : feature title\n"
        L"# comment1\n"
        L"Scenario : title\n"
        L"// comment2\n"
        L"Given precondition"
    };
    wistringstream is(str);
    GherkinLexer lexer(is, parser);

    // When
    skipToken();
    skipToken();
    yytokentype token = (yytokentype)yylex();

    // Then
    ASSERT_EQ(GIVEN_STEP, token);
    ASSERT_EQ(5, yylloc.first_line);
    delete yylval.pwstr;
}

TEST_F(yylexTest, wchar_space)
{
    std::wregex r;
    r.imbue(std::locale(""));
    r.assign(LR"(\s)");

    std::wstring s = L"　"; // 全角空白
    ASSERT_TRUE(regex_match(s, r));
}

TEST_F(yylexTest, Kanji)
{
#ifdef WIN32
    std::wregex r;
    r.imbue(std::locale(""));
    r.assign(LR"(\S)");

    std::wstring s = L"漢";
    ASSERT_FALSE(regex_match(s, r));
#endif
}
