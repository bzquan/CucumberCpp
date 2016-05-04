# Cucumber/C++
Cucumber/C++ is an editor of Cucumber/Gherkin, a language of specification by example in the world of BDD.
It could generate C++ skeleton implementation from Gherkin.

# Features
1. Keywords highlight
2. Pretty formatting
3. Generation of C++ Gherkin implementation skeleton.

# Using precompiled package(Only for Windows)  
The package includes Qt5.6 supporting DLLs.  
1. Uncompress CucumberC++.Windows.7z.You can download CucumberCpp.ex_ and change extension to exe if you have ready installed CucumberC++.Windows package.  
2. Install Visual Studio 2015 run time. It can be downloaded from Microsoft site.  
3. Start CucumberCpp.exe  
4. Using non-English specifications in Gherkin when generating executable specification  
    - Check "Support unicode" button if you use Visual Studio 2015. Non-English names, e.g. Japanese, Chinese, are used in feature class name, scenario class names and function names.
    - Uncheck "Support unicode" button if you use gcc. Unicode identifiers are used in feature class name, scenario class names and function names. Because g++ does not support UTF-8 characters in identifiers yet.

# Building Cucumber/C++
1. Install Qt5.6
2. Setup C++14 compiler, eg. Visual Studio 2015, gcc5.2.
3. Optional: Bison is needed if you want to change Gherkin parser grammer, gherkin.y.
3. Configure Qt projects, CucumberCpp.pro and GherkinParser.pro.
4. CucumberCpp is GUI projects which depends on GherkinParser.
 
# Limitations
It only supports English Keywords of Gherkin. However you can use any languages to write specification by example in Gherkin.



