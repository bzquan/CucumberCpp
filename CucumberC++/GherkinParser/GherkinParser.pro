#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T21:51:44
#
#-------------------------------------------------

QT       -= core gui
QT      += core
TARGET = GherkinParser
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14

CXXFLAGS += -Wno-write-strings

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/Ast
INCLUDEPATH += $$PWD/src/BDD
INCLUDEPATH += $$PWD/src/PrettyGherkin
INCLUDEPATH += $$PWD/src/util

SOURCES += \
    src/AstBuilder.cpp \
    src/gherkin.tab.cpp \
    src/GherkinIF.cpp \
    src/GherkinLexer.cpp \
    src/GherkinParser.cpp \
    src/ParsingState.cpp \
    src/Ast/Background.cpp \
    src/Ast/Example.cpp \
    src/Ast/Feature.cpp \
    src/Ast/ScenarioDefinition.cpp \
    src/Ast/ScenarioOutline.cpp \
    src/Ast/Step.cpp \
    src/Ast/Tag.cpp \
    src/BDD/BDDAbstractBuilder.cpp \
    src/BDD/BDDAbstrctScenarioBuilder.cpp \
    src/BDD/BDDASTVisitor.cpp \
    src/BDD/BDDExecSpecGenerator.cpp \
    src/BDD/BDDFeatureBuilder.cpp \
    src/BDD/BDDGherkinTableBuilder.cpp \
    src/BDD/BDDInstantiatedTestClassBuilder.cpp \
    src/BDD/BDDScenarioBuilder.cpp \
    src/BDD/BDDScenarioOutlineBuilder.cpp \
    src/BDD/BDDStepArg.cpp \
    src/BDD/BDDStepBuilder.cpp \
    src/BDD/BDDStepImplBuilderContext.cpp \
    src/BDD/BDDStepImplBuilderManager.cpp \
    src/BDD/BDDStepImplCppBuilder.cpp \
    src/BDD/BDDStepImplHeaderBuilder.cpp \
    src/BDD/BDDTestModelBuilder.cpp \
    src/BDD/BDDUtil.cpp \
    src/PrettyGherkin/PrettyDataTable.cpp \
    src/PrettyGherkin/PrettyDataTableFormatter.cpp \
    src/PrettyGherkin/PrettyGherkin.cpp \
    src/PrettyGherkin/PrettyGherkinASTVisitor.cpp \
    src/PrettyGherkin/PrettyTableCell.cpp \
    src/PrettyGherkin/PrettyTableRow.cpp \
    src/PrettyGherkin/PrettyTableRowFormatter.cpp \
    src/util/guid.cpp \
    src/util/StrUtility.cpp \
    src/Ast/IHasSteps.cpp \
    src/BDD/BDDFeatureBuilderContext.cpp \
    src/BDD/BDDUnicodeNameDefinitions.cpp

HEADERS += \
    src/AstBuilder.h \
    src/Definitions.h \
    src/gherkin.tab.hpp \
    src/GherkinErrorMsg.h \
    src/GherkinIF.h \
    src/GherkinLexer.h \
    src/GherkinParser.h \
    src/ParsingState.h \
    src/YYTableParam.h \
    src/Ast/Background.h \
    src/Ast/Comment.h \
    src/Ast/DataTable.h \
    src/Ast/DocString.h \
    src/Ast/Example.h \
    src/Ast/Feature.h \
    src/Ast/IHasDescription.h \
    src/Ast/IHasLocation.h \
    src/Ast/IHasRows.h \
    src/Ast/IHasSteps.h \
    src/Ast/IHasTags.h \
    src/Ast/IVisit.h \
    src/Ast/IVisitable.h \
    src/Ast/Language.h \
    src/Ast/Location.h \
    src/Ast/Scenario.h \
    src/Ast/ScenarioDefinition.h \
    src/Ast/ScenarioOutline.h \
    src/Ast/Step.h \
    src/Ast/StepArgument.h \
    src/Ast/TableCell.h \
    src/Ast/TableRow.h \
    src/Ast/Tag.h \
    src/BDD/BDDAbstractBuilder.h \
    src/BDD/BDDAbstrctScenarioBuilder.h \
    src/BDD/BDDASTVisitor.h \
    src/BDD/BDDBackgroundBuilder.h \
    src/BDD/BDDExecSpecGenerator.h \
    src/BDD/BDDFeatureBuilder.h \
    src/BDD/BDDGherkinTableBuilder.h \
    src/BDD/BDDInstantiatedTestClassBuilder.h \
    src/BDD/BDDScenarioBuilder.h \
    src/BDD/BDDScenarioOutlineBuilder.h \
    src/BDD/BDDStepArg.h \
    src/BDD/BDDStepBuilder.h \
    src/BDD/BDDStepImplBuilderContext.h \
    src/BDD/BDDStepImplBuilderManager.h \
    src/BDD/BDDStepImplCppBuilder.h \
    src/BDD/BDDStepImplHeaderBuilder.h \
    src/BDD/BDDTestModelBuilder.h \
    src/BDD/BDDUtil.h \
    src/PrettyGherkin/PrettyDataTable.h \
    src/PrettyGherkin/PrettyDataTableFormatter.h \
    src/PrettyGherkin/PrettyGherkin.h \
    src/PrettyGherkin/PrettyGherkinASTVisitor.h \
    src/PrettyGherkin/PrettyGherkinDef.h \
    src/PrettyGherkin/PrettyTableCell.h \
    src/PrettyGherkin/PrettyTableRow.h \
    src/PrettyGherkin/PrettyTableRowFormatter.h \
    src/util/guid.h \
    src/util/StrUtility.h \
    src/BDD/BDDFeatureBuilderContext.h \
    src/BDD/BDDUnicodeNameDefinitions.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"
INCLUDEPATH += "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include"

LIBS += -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\um\x86"
LIBS += -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\ucrt\x86"
