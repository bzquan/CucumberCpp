# An Example of Cucumber/C++
Some times we need to use google mock as a test double. The differences from simple string calculaor is that the step "_Then The result should be <Sum>_" has been changed to "_Then The result <Sum> shall be informed_". The calculaor may inform the sum to a screen or GUI. 

    Feature: String calculator
     Client can get sum of numbers by inputting a string.

    Scenario Outline: A separator can be +, comma or semicolon.  
     A separator could be either +, comma or semicolon. But it is not allowed to combinate different separators.

    Given Enter <Numbers> with separator
    When Sum all the numbers
    Then The result <Sum> shall be informed

    Examples:
     |Numbers  |Sum|
     |1 + 2 + 3|6  |
     |4, 5, 6  |15 |
     |7; 8; 9  |24 |
     |1, 2; 3  |-1 |

Suppose that the calculator will inform the sum to following IDisplay interface.

    class IDisplay
    {
    public:
        ~IDisplay(){}
        virtual void Sum(int sum) = 0;
    };

In the implementation of scenario we may use following google mock object.

    #include "IDisplay.h"

    using namespace testing;

    class MockDisplay : public IDisplay
    {
    public:
        MOCK_METHOD1(Sum, void(int sum));

        void ExpectSum(int sum)
        {
            EXPECT_CALL(*this, Sum(sum));
        }
    };

The calling sequence of our executable specification is ![call sequence](https://github.com/bzquan/CucumberCpp/blob/master/Example/SimpleStringCalculatoMock/CallSequence.jpg).  
Sure, this implementation will fail. The problem is that google mock requires that the expectation of a mock object __must__ be set before a function of the mock object called. In other words, _MockDisplay::ExpectSum_ __must__ be called before _StringCalculator::CalculateSum_ called. This is an technique issue which is differnt from the normal readable specification. It will be unreadable specification if we rewrite the feature as following to pass our test program, i.e. put _Then_ step before the _When_ step. 

    Feature: String calculator
     Client can get sum of numbers by inputting a string.

    Scenario Outline: A separator can be +, comma or semicolon.  
     A separator could be either +, comma or semicolon. But it is not allowed to combinate different separators.

    Given Enter <Numbers> with separator
    Then The result <Sum> shall be informed
    When Sum all the numbers

    Examples:
     |Numbers  |Sum|
     |1 + 2 + 3|6  |
     |4, 5, 6  |15 |
     |7; 8; 9  |24 |
     |1, 2; 3  |-1 |

By using Cucumber/C++'s _[[mock]]_ attribute, we can change our feature as little as possible. Steps with __[[mock]]__ attribute will be executed when running executable specification. So that our test program will all succeed.

    Feature: String calculator
     Client can get sum of numbers by inputting a string.

    Scenario Outline: A separator can be +, comma or semicolon.  
     A separator could be either +, comma or semicolon. But it is not allowed to combinate different separators.

    Given Enter <Numbers> with separator
    When Sum all the numbers
    Then The result <Sum> shall be informed[[mock]]

    Examples:
     |Numbers  |Sum|
     |1 + 2 + 3|6  |
     |4, 5, 6  |15 |
     |7; 8; 9  |24 |
     |1, 2; 3  |-1 |

You can find source code of this example from [here](https://github.com/bzquan/CucumberCpp/tree/master/Example/SimpleStringCalculatoMock)

Note: Implementation of steps needs [Google test/mock](https://github.com/google/googletest)