#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>

#include "PlainTextEditWithLineNum.h"
//#include "SyntaxHighlighter.h"

class PlainTextEditWithLineNum;
class QPlainTextEdit;
class tileToolBar;
class QSyntaxHighlighter;
struct ExecutableSpecFileNames;

class GherkinErrorMsg;
class FindDialog;
class FindReplaceDialog;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void show();

public slots:
    void newFile();
    void openFile(const QString &path = QString());
    void openRecentFile();
    void openContainingFolder();
    void saveFile();
    void saveAsFile();

    void prettyGherkin();
    void genExecutableSpec();
    void supportUnicode();

    void undo();
    void onUndoAvailable(bool available);

    void redo();
    void onRedoAvailable(bool available);
    void find();
    void findReplace();
    void setFont();

    void clearCompileInfo();
    void showCompileInfo();
    void hideCompileInfo();

    void about();
    void onTextChanged();

protected:
    void closeEvent(QCloseEvent *event) override;

    // drag&drop
    bool isValidFilePath(QString path_mime);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void setupMenues();
    void setupFileMenu();
    void setupEditMenu();
    void setupViewMenu();
    void setupHelpMenu();
    void setupCompileMenu();
    void createToolBars();
    void setupEditor();
    void setupRecentFilesMenu(QMenu *fileMenu);

    void createFileToolBar();
    void createEditToolBar();
    void createCompileToolBar();
    void createViewToolBar();

    void genExecutableSpec4SavedFeature();
    bool canExit();
    void saveToFile(QString filePath);
    void fileOpenedOrSaved(QString filePath);
    void setFilePathOnTitle(QString filePath);
    void enableZoomButtons();
    void moveCursor(size_t lineNo);
    std::wstring preparingPrettyGherkin(QString msg);
    bool canCompile();
    void displayPrettyFormattedGherkin(std::wstring& formattedGherkin);
    void displayExecutableSpecFileNames(ExecutableSpecFileNames& output);
    void displayErrorMessages(std::vector<GherkinErrorMsg>& errors);
    void updateRecentActionList();
    void adjustForCurrentFile(const QString &filePath);
    void hideAllRecentFileActions();

private:
    PlainTextEditWithLineNum* m_pEditor;
    QPlainTextEdit* m_pCompileInfo;

    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QList<QAction*> recentFileActionList;

    QAction* undoAction;
    QAction* redoAction;
    QAction* findAction;
    QAction* findReplaceAction;
    QAction* setFontAction;

    QAction* prettyGherkinAction;
    QAction* genTestCodeAction;
    QAction* clearCompileInfoAction;
    QAction* showCompileInfoAction;
    QAction* hideCompileInfoAction;

    QAction* supportUnicodeAction;

    QString  m_currentFilePath;
    bool     m_supportUnicode;

    FindDialog* m_pFindDialog;
    FindReplaceDialog* m_pFindReplaceDialog;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
