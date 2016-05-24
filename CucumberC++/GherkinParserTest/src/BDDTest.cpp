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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <fstream>
#include <locale>
#ifdef WIN32
#include <codecvt>
#endif
#include <direct.h>
#include "StrUtility.h"
#include "Feature.h"
#include "GherkinParser.h"
#include "BDDExecSpecGenerator.h"
#include "GherkinIF.h"

using namespace std;
using namespace testing;
using namespace GherkinAst;
using namespace CucumberCpp;

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

char cCurrentPath[512];

class BDDTest : public testing::Test {
public:
    virtual void SetUp(){}
    virtual void TearDown(){}

protected:
    wstring outputDir()
    {
        if (GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        {
            string path(cCurrentPath);
           return StrUtility::string2wstring(path) + L"\\TestOutput\\";
        }
        else
        {
            return wstring();
        }
    }

protected:
    GherkinParser parser;
};

TEST_F(BDDTest, StepHeader)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When action
          )"
    };

    parser.parse(is);
    Feature* pFeature = parser.astBuilder().Feature();
    BDDExecSpecGenerator execSpecGenerator;
    execSpecGenerator.GenExecSpec(pFeature);

    // When
    wstring stepHeader = execSpecGenerator.StepDefsHeader();

    // Then
    ASSERT_TRUE(stepHeader.length() > 0);

    wstring path = outputDir() + execSpecGenerator.StepHeaderFileName();
    wofstream file(StrUtility::wstring2string(path));
    file << stepHeader;
}

TEST_F(BDDTest, StepImpl)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When action
          )"
    };

    parser.parse(is);
    Feature* pFeature = parser.astBuilder().Feature();
    BDDExecSpecGenerator execSpecGenerator;
    execSpecGenerator.GenExecSpec(pFeature);

    // When
    wstring stepImpl = execSpecGenerator.StepDefsImpl();

    // Then
    ASSERT_TRUE(stepImpl.length() > 0);

    wstring path = outputDir() + execSpecGenerator.StepImplFileName();
    wofstream file(StrUtility::wstring2string(path));
    file << stepImpl;
}

TEST_F(BDDTest, TestModelHeader)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When action
          )"
    };

    parser.parse(is);
    Feature* pFeature = parser.astBuilder().Feature();
    BDDExecSpecGenerator execSpecGenerator;
    execSpecGenerator.GenExecSpec(pFeature);

    // When
    wstring testModelHeader = execSpecGenerator.StepModelTemplateHeader();

    // Then
    ASSERT_TRUE(testModelHeader.length() > 0);

    wstring path = outputDir() + execSpecGenerator.StepModelTemplateHeaderFileName();
    wofstream file(StrUtility::wstring2string(path));
    file << testModelHeader;
}

TEST_F(BDDTest, TestModelImpl)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When action
          )"
    };

    parser.parse(is);
    Feature* pFeature = parser.astBuilder().Feature();
    BDDExecSpecGenerator execSpecGenerator;
    execSpecGenerator.GenExecSpec(pFeature);

    // When
    wstring testModelImpl = execSpecGenerator.StepModelTemplateImpl();

    // Then
    ASSERT_TRUE(testModelImpl.length() > 0);

    wstring path = outputDir() + execSpecGenerator.StepModelTemplateImplFileName();
    wofstream file(StrUtility::wstring2string(path));
    file << testModelImpl;
}

TEST_F(BDDTest, FeatureImpl)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When action
          )"
    };

    parser.parse(is);
    Feature* pFeature = parser.astBuilder().Feature();
    BDDExecSpecGenerator execSpecGenerator;
    execSpecGenerator.GenExecSpec(pFeature);

    // When
    wstring featureImpl = execSpecGenerator.FeatureImpl();

    // Then
    ASSERT_TRUE(featureImpl.length() > 0);

    wstring path = outputDir() + execSpecGenerator.FeatureFileName();
    wofstream file(StrUtility::wstring2string(path));
    file << featureImpl;
}

TEST_F(BDDTest, ColumnParam)
{
    // Given
    wstring text{
        LR"(Feature : feature with column param
            Scenario Outline: title
             Description of scenario
              Given 下記はdoc string文字列である。
                """
                文字列-Doc String1
                文字列-Doc String2
                """          
              Given 本Stepは下記テーブルを引数とする
                 |Col1|Col2 |Col3|
                 |IBM |25   |USD |
                 |Sony|1,500|JPY |
              Given <col1> and <col2>
              Given Step定義headerは"Gherkinコンパイル_Steps.h"である
              When 5,000と5,000,000.66を引数とする
              Examples: "Scenario Outline"のテーブル
                |col1|param2|Sum|
                |3     |3     |6  |
                |3     |5     |8  |
          )"
    };

    std::wstring formattedGherkin;
    ExecutableSpecFileNames output;

    // When
    GherkinIF gherkin;
    bool res = gherkin.GenExecSpec(text, formattedGherkin, outputDir(), output);

    // Then
    ASSERT_TRUE(res);
}

TEST_F(BDDTest, UseGherkinIF)
{
    // Given
    wistringstream is{
        LR"(Feature : feature title
            Scenario : title
             Description of scenario
              Given precondition
              When action
          )"
    };

    ExecutableSpec output;
    GherkinIF gherkin;

    // When
    bool res = gherkin.GenExecSpec(is, output);

    // Then
    ASSERT_TRUE(res);
    ASSERT_TRUE(output.FeatureImpl.length() > 0);
    ASSERT_TRUE(output.StepDefsHeader.length() > 0);
    ASSERT_TRUE(output.StepDefsImpl.length() > 0);
    ASSERT_TRUE(output.StepModelTemplateHeader.length() > 0);
    ASSERT_TRUE(output.StepModelTemplateImpl.length() > 0);
}
