QT += core
QT -= gui

CONFIG += c++11

TARGET = GherkinParserTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    src/BDDTest.cpp \
    src/BDDUtilTest.cpp \
    src/main.cpp \
    src/parseErrorTest.cpp \
    src/StrUtilityTest.cpp \
    src/yylexTest.cpp \
    src/yyparseTest.cpp \
    src/PrettyGherkinTest/Gherkin_Compiler_Feature.cpp \
    src/PrettyGherkinTest/Gherkin_Compiler_Steps.cpp \
    src/PrettyGherkinTest/Gherkin_Compiler_TestModel.cpp \
    TestCaseModel/AbstractTestModel.cpp \
    TestCaseModel/GherkinTable.cpp \
    TestCaseModel/IndirectFunctionCaller.cpp \
    TestCaseModel/NotificationTrace.cpp \
    TestCaseModel/StringUtility.cpp \
    src/PrettyGherkinTest/Pretty_Gherkin_Feature.cpp \
    src/PrettyGherkinTest/Pretty_Gherkin_Steps.cpp \
    src/PrettyGherkinTest/Pretty_Gherkin_TestModel.cpp

HEADERS += \
    src/MinimalistPrinter.h \
    src/PrettyGherkinTest/Gherkin_Compiler_Steps.h \
    src/PrettyGherkinTest/Gherkin_Compiler_TestModel.h \
    TestCaseModel/AbstractNotificationTrace.h \
    TestCaseModel/AbstractTestModel.h \
    TestCaseModel/FeatureStepArg.h \
    TestCaseModel/FeatureStepFunction.h \
    TestCaseModel/FeatureStepModel.h \
    TestCaseModel/FeatureTestModel.h \
    TestCaseModel/GeneralMacro.h \
    TestCaseModel/GherkinTable.h \
    TestCaseModel/IndirectFunctionCaller.h \
    TestCaseModel/IndirectFunctionCallRequest.h \
    TestCaseModel/NotificationTrace.h \
    TestCaseModel/StringUtility.h \
    src/PrettyGherkinTest/Pretty_Gherkin_Steps.h \
    src/PrettyGherkinTest/Pretty_Gherkin_TestModel.h

INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"
INCLUDEPATH += "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include"

LIBS += -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\um\x86"
LIBS += -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\ucrt\x86"

INCLUDEPATH += $$PWD/gmock-1.7.0-lib/include
win32: LIBS += -L$$PWD/gmock-1.7.0-lib/lib/ -lgmock

INCLUDEPATH += $$PWD/TestCaseModel

INCLUDEPATH += $$PWD/../GherkinParser/src
INCLUDEPATH += $$PWD/../GherkinParser/src/Ast
INCLUDEPATH += $$PWD/../GherkinParser/src/BDD
INCLUDEPATH += $$PWD/../GherkinParser/src/PrettyGherkin
INCLUDEPATH += $$PWD/../GherkinParser/src/util

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../GherkinParser/output/release/ -lGherkinParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../GherkinParser/output/debug/ -lGherkinParser

INCLUDEPATH += $$PWD/../GherkinParser/output/debug
DEPENDPATH += $$PWD/../GherkinParser/output/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/release/libGherkinParser.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/debug/libGherkinParser.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/release/GherkinParser.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/debug/GherkinParser.lib
