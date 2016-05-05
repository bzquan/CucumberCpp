# An Example of Cucumber/C++
Suppose we have following specification for a simple string calculaor.

    Feature: String calculator
     Client can get sum of numbers by inputting a string.

    Scenario Outline: A separator can be +, comma or semicolon.  
     A separator could be either +, comma or semicolon. But it is not allowed to combinate different separators.

    Given Enter <Numbers> with separator
    When Sum all the numbers
    Then The result should be <Sum>

    Examples:
     |Numbers  |Sum|
     |1 + 2 + 3|6  |
     |4, 5, 6  |15 |
     |7; 8; 9  |24 |
     |1, 2; 3  |-1 |

We can generating following C++ implementations by using Cucumber/C++.

    String_calculator_Feature.cpp
    String_calculator_Steps.h/cpp
    String_calculator_TestModel.h/cpp

String\_calculator\_Steps is a class of step definiton for the feature. String\_calculator\_Steps.h looks like this. We do not care about String\_calculator\_Steps class definition when implementing scenario steps. We need to implement the steps instead.

    class String_calculator_Steps : public AbstractStepModel
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
        // Enter_Numbers_with_separator
        void Enter_Numbers_with_separator(GherkinRow&);
        // Sum_all_the_numbers
        void Sum_all_the_numbers();
        // The_result_should_be_Sum
        void The_result_should_be_Sum(GherkinRow&);

    public:
        void RegisterSteps() override
        {
            Step(
                L"Enter <Numbers> with separator",
                function < void(GherkinRow&) >
                (bind(&String_calculator_Steps::Enter_Numbers_with_separator, this, _1)));
            Step(
                L"Sum all the numbers",
                function < void() >
                (bind(&String_calculator_Steps::Sum_all_the_numbers, this)));
            Step(
                L"The result should be <Sum>",
                function < void(GherkinRow&) >
                (bind(&String_calculator_Steps::The_result_should_be_Sum, this, _1)));
        }

    private:
        String_calculator_TestModel model;
    };

Following is a skeleton of step implemetation(String\_calculator\_Steps.cpp).

    #include "String_calculator_Steps.h"

    // Enter <Numbers> with separator
	void String_calculator_Steps::Enter_Numbers_with_separator(GherkinRow& row)
    {
        PendingStep(L"Enter_Numbers_with_separator");
    }

    // Sum all the numbers
    void String_calculator_Steps::Sum_all_the_numbers()
    {
        PendingStep(L"Sum_all_the_numbers");
    }

    // The result should be <Sum>
    void String_calculator_Steps::The_result_should_be_Sum(GherkinRow& row)
    {
        PendingStep(L"The_result_should_be_Sum");
    }

We recommend to use String\_calculator\_Steps as a kind of adaptor for step implementation. It shall be used to convert step parameters, e.g. table, table row, numbers. In order to separate concerns, all implementations shall be implemented in String\_calculator\_TestModel. Generated String\_calculator\_TestModel class has only SetUp, TearDown and VerifyExpectations functions. We need to add supporting functions to implement step definitions. Following is a definition of String\_calculator\_TestModel class(String\_calculator\_TestModel.h).

    #pragma once

    #include "gtest/gtest.h"
    #include "gmock/gmock.h"
    #include "AbstractTestModel.h"
    #include "StringCalculator.h"

    //String_calculator_TestModel
    class String_calculator_TestModel : public AbstractTestModel
    {
    public:
        void SetUp();
        void TearDown();
        void VerifyExpectations() override;

        void Input(string input);
        void Sum();
        void ExpectedSum(int sum);

    private:
        StringCalculator m_Calculator;
        int m_ExpectedSum;
        int m_ActualSum;
    };

Following is an implementation of String\_calculator\_TestModel class(String\_calculator\_TestModel.cpp).

    #include "String_calculator_TestModel.h"

    using namespace ::testing;

    void String_calculator_TestModel::VerifyExpectations()
    {
        ASSERT_EQ(m_ExpectedSum, m_ActualSum);
    }

    void String_calculator_TestModel::Input(string input)
    {
        m_Calculator.Input(input);
    }

    void String_calculator_TestModel::Sum()
    {
        m_ActualSum = m_Calculator.Result();
    }

    void String_calculator_TestModel::ExpectedSum(int sum)
    {
        m_ExpectedSum = sum;
    }

Now we can implement step definitions easily by using String\_calculator\_TestModel class. "GherkinRow& row" is step parameter which is a table row from the examples table of scenario outline.(String\_calculator_Steps.cpp)

    void String_calculator_Steps::Enter_Numbers_with_separator(GherkinRow& row)
    {
        model.Input(row[0].strValue());
    }

    void String_calculator_Steps::Sum_all_the_numbers()
    {
        model.Sum();
    }

    void String_calculator_Steps::The_result_should_be_Sum(GherkinRow& row)
    {
        model.ExpectedSum(row[1].intValue());
    }

That is all about implementating steps. Now we can implement our simple string calculator, StringCalculator. An example of class definition is as following(StringCalculator.h).

    #pragma once

    #include <string>

    using namespace std;

    class StringCalculator
    {
    public:
        StringCalculator() : m_Result(-1) {}
        void Input(const string input);
        int Result() { return m_Result; }

    private:
        vector<string> Split(const string &str, char delim);
        char GetSeparator(const string& input);
        bool IsSeprator(const string& input, char ch);
        bool IsAllDigit(const string& str);

    private:
        int m_Result;
    };

Following is an implementation of StringCalculator(StringCalculator.cpp).

    #include <vector>
    #include <sstream>
    #include "StringCalculator.h"

    void StringCalculator::Input(const string input)
    {
        char delim = GetSeparator(input);
        vector<string> nums = Split(input, delim);
        m_Result = 0;
        for (string& str : nums)
        {
            if (IsAllDigit(str))
                m_Result += (int)stol(str);
            else
            {
                m_Result = -1;
                return;
            }
        }
    }

    char StringCalculator::GetSeparator(const string& input)
    {
        if (IsSeprator(input, '+'))
            return '+';
        else if (IsSeprator(input, ','))
            return ',';
        else if (IsSeprator(input, ';'))
            return ';';
        else
            return '\0';
    }

    vector<string> StringCalculator::Split(const string &str, char delim)
    {
        istringstream iss(str);
        string tmp;
        vector<string> res;
        while (getline(iss, tmp, delim))
            res.push_back(tmp);
        
        return res;
    }

    bool StringCalculator::IsSeprator(const string& input, char ch)
    {
        return string::npos != input.find(ch);
    }

    bool StringCalculator::IsAllDigit(const string& str)
    {
        if (str.length() == 0) return false;
        for (char ch : str)
        {
            bool is_digit = (ch >= '0') && (ch <= '9');
            bool is_space = (ch == ' ');
            if (!is_digit && !is_space) return false;
        }
        return true;
    }

That is all.

You can find source code of this example from [here](https://github.com/bzquan/CucumberCpp/tree/master/Example/SimpleStringCalculator)

Note: Implementation of steps needs [Google test/mock](https://github.com/google/googletest)