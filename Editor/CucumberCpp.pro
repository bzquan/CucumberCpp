#-------------------------------------------------
#
# Project created by QtCreator 2016-01-17T14:48:25
#
#-------------------------------------------------

QT += core gui
//QT += qml quick
CONFIG += c++11

win32:RC_ICONS += ui/CucumberCpp.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QTPLUGIN += qico@

TARGET = CucumberCpp
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/PlainTextEditWithLineNum.cpp \
    src/MainWindow.cpp \
    src/GherkinHighlighter.cpp \
    src/FindDialog.cpp \
    src/FindReplaceDialog.cpp \
    src/FindReplaceForm.cpp \
    src/FindForm.cpp \
    src/UserSetting.cpp \
    src/Utility.cpp

HEADERS  += \
    src/PlainTextEditWithLineNum.h \
    src/MainWindow.h \
    src/GherkinHighlighter.h \
    src/FindDialog.h \
    src/FindReplaceDialog.h \
    src/FindReplaceForm.h \
    src/FindForm.h \
    src/UserSetting.h \
    src/Utility.h

FORMS    += \
    ui/MainWindow.ui \
    ui/findreplacedialog.ui \
    ui/findreplaceform.ui

DISTFILES += \
    ui/CucumberCpp.ico

RESOURCES += \
    ui/resources.qrc


//win32: LIBS += -lole32

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/../GherkinParser/src
INCLUDEPATH += $$PWD/../GherkinParser/src/Ast
INCLUDEPATH += $$PWD/../GherkinParser/src/BDD
INCLUDEPATH += $$PWD/../GherkinParser/src/PrettyGherkin
INCLUDEPATH += $$PWD/../GherkinParser/src/util

INCLUDEPATH += "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include"
INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"

RC_INCLUDEPATH += "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include"
RC_INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"

LIBS += -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\um\x86"
LIBS += -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\ucrt\x86"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../GherkinParser/output/release/ -lGherkinParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../GherkinParser/output/debug/ -lGherkinParser

INCLUDEPATH += $$PWD/../GherkinParser/output/debug
DEPENDPATH += $$PWD/../GherkinParser/output/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/release/libGherkinParser.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/debug/libGherkinParser.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/release/GherkinParser.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../GherkinParser/output/debug/GherkinParser.lib
