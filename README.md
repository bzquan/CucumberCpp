# Cucumber/C++
Cucumber/C++ is an editor of Cucumber/Gherkin, a language of specification by example in the BDD world.
C++ step implementation is simple and straight forward.

# Screen shot
![sceen shot](https://github.com/bzquan/CucumberCpp/blob/master/CucumberC%2B%2B.jpg)

# Features
1. Keywords highlight
2. Pretty formatting
3. Generation of C++ Gherkin implementation skeleton.

# Building Cucumber/C++
1. Install Qt5.6
2. Setup C++14 compiler, eg. Visual Studio 2015, gcc5.2.
3. Optional: Bison is needed if you want to change Gherkin parser grammer, gherkin.y.
3. Configure Qt projects, CucumberCpp.pro and GherkinParser.pro.
4. CucumberCpp is GUI projects which depends on GherkinParser.

# Examples
[Simple string calculator](https://github.com/bzquan/CucumberCpp/blob/master/Example/SimpleStringCalculator.md)  
[How to use mock object](https://github.com/bzquan/CucumberCpp/blob/master/Example/SimpleStringCalculatorMock.md)
 
# Limitations
It only supports English Keywords of Gherkin. However you can use any languages to write specification by example in Gherkin.


# Memo
[Markdown help from stackoverflow](http://stackoverflow.com/editing-help)

