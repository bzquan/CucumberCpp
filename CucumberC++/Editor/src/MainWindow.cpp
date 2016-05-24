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

#include <QtWidgets>
#include <QMessageBox>
#include <QRect>
#include <QDebug>
#include "ui_MainWindow.h"
#include "PlainTextEditWithLineNum.h"
#include "GherkinHighlighter.h"
#include "FindDialog.h"
#include "FindReplaceDialog.h"
#include "UserSetting.h"
#include "BDDUtil.h"
#include "StrUtility.h"
#include "Utility.h"

#include <sstream>
#include "GherkinIF.h"
#include "MainWindow.h"

using namespace std;

namespace
{
    const char* file_diag_filter = "Gherkin(*.feature);;Text(*.txt);;Other(*.*)";
    const int MAX_RECENT_FILE_NR = 6;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 90);
    ui->splitter->setStretchFactor(1, 10);

    setAcceptDrops(true);

    m_pEditor = ui->gherkinTextEdit;
    m_pCompileInfo = ui->compileInfoTextEdit;

    m_pCompileInfo->setVisible(false);
    m_pCompileInfo->setReadOnly(true);

    m_pFindDialog = new FindDialog(m_pEditor);
    m_pFindReplaceDialog = new FindReplaceDialog(m_pEditor);

    m_supportUnicode = UserSetting::supportUnicode();
    CucumberCpp::BDDUtil::supportUnicode(m_supportUnicode);

    setupMenues();
    createToolBars();

    setWindowTitle("");
    setupEditor();
    statusBar()->showMessage("Hello Cucumber C++!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QStringList arguments = QCoreApplication::arguments();
    QString filePath = (arguments.size() > 1) ? arguments[1] : UserSetting::lastUsedFile();

    openFile(filePath);
    QMainWindow::show();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Cucumber/C++ v1.0"),
                tr("<p>By using <b>Cucumber/C++</b> you can make pretty Gherkin and " \
                   "generate executable specification.</p>"));
}

void MainWindow::newFile()
{
    if (canExit())
    {
        m_pEditor->clear();
        setFilePathOnTitle("");
    }
}

void MainWindow::openFile(const QString &path)
{
    if (!canExit()) return;

    QString filePath = path;
    if (filePath.isNull())
        filePath = QFileDialog::getOpenFileName(this, tr("Open File"), UserSetting::lastDir(), file_diag_filter);

    if (Utility::fileExist(filePath))
    {
        QFile file(filePath);
        if (file.open( QFile::ReadWrite | QFile::Text))
        {
            m_pEditor->setPlainText(file.readAll());
            fileOpenedOrSaved(filePath);
        }
    }
    else
    {
        // delete filePath from recent files
        adjustForCurrentFile(filePath);
    }
}

void MainWindow::openContainingFolder()
{
    QUrl url(QString("file:///") + Utility::getDirFromFilepath(m_currentFilePath));
    QDesktopServices::openUrl(url);
}

void MainWindow::openRecentFile()
{
    QAction *action = dynamic_cast<QAction*>(sender());
    if (action != nullptr)
    {
        openFile(action->data().toString());
    }
}

void MainWindow::setupEditor()
{
    m_pEditor->setFont(UserSetting::font());
    m_pEditor->setWordWrapMode(QTextOption::NoWrap);

    QSyntaxHighlighter* highlighter = new GherkinHighlighter(m_pEditor->document());
    Q_UNUSED(highlighter);
    connect(m_pEditor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void MainWindow::saveFile()
{
    if (!m_currentFilePath.isEmpty())
        saveToFile(m_currentFilePath);
    else
        saveAsFile();
}

void MainWindow::saveAsFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save as..."), "", file_diag_filter);
    saveToFile(filePath);
}

void MainWindow::saveToFile(QString filePath)
{
    QTextDocumentWriter writer;
    writer.setFormat("plaintext");
    writer.setFileName(filePath);
    bool success = writer.write(m_pEditor->document());

    if (success)
    {
        fileOpenedOrSaved(filePath);
    }
}

void MainWindow::fileOpenedOrSaved(QString filePath)
{
    saveAction->setEnabled(false);
    m_pEditor->document()->setModified(false);

    setFilePathOnTitle(filePath);
    UserSetting::setLastUsedFile(filePath);
    adjustForCurrentFile(filePath);
}

void MainWindow::setFilePathOnTitle(QString filePath)
{
    QString title = tr("Cucumber C++");
    if (!filePath.isEmpty())
        title.append(" -- " + filePath);
    m_currentFilePath = filePath;
    setWindowTitle(title);
}

void MainWindow::onTextChanged()
{
    const bool is_modified = m_pEditor->document()->isModified();
    saveAction->setEnabled(is_modified);

    const bool enable = canCompile();
    prettyGherkinAction->setEnabled(enable);
    genTestCodeAction->setEnabled(enable);
}

bool MainWindow::canCompile()
{
    return m_pEditor->document()->lineCount() > 2;
}

void MainWindow::prettyGherkin()
{
    QString msg("------------------\nStart formatting Gherkin...\n");
    std::wstring gherkin = preparingPrettyGherkin(msg);

    GherkinIF parser;
    std::wstring formattedGherkin;
    bool success = parser.prettyGherkin(gherkin, formattedGherkin);

    m_pEditor->setErrorLines(parser.errorLines());
    if (success)
    {
        displayPrettyFormattedGherkin(formattedGherkin);
    }
    else
    {
        std::vector<GherkinErrorMsg> errors = parser.errorMsgs();
        displayErrorMessages(errors);
    }
    m_pCompileInfo->moveCursor(QTextCursor::End);
}

std::wstring MainWindow::preparingPrettyGherkin(QString msg)
{
    showCompileInfo();
    m_pCompileInfo->appendPlainText(msg);

    QString text = m_pEditor->toPlainText();
    std::wstring gherkin = text.toStdWString();

    return gherkin;
}

void MainWindow::displayPrettyFormattedGherkin(std::wstring& formattedGherkin)
{
    bool feature_text_changed = formattedGherkin.length() > 0;
    if (feature_text_changed)
    {
        // contents :
        size_t cursorPos = m_pEditor->textCursor().blockNumber() + 1;
        m_pEditor->selectAll();
        QString text = QString::fromStdWString(formattedGherkin);
        m_pEditor->textCursor().insertText(text);
        moveCursor(cursorPos);
    }

    // messges
    QString success("Gherkin has been formatted successfully!");
    m_pCompileInfo->appendPlainText(success);
}

void MainWindow::displayErrorMessages(std::vector<GherkinErrorMsg>& errors)
{
    if (errors.size() > 0)
    {
        std::wstringstream ss;
        for (GherkinErrorMsg& error : errors)
        {
            ss << L"Line(" << error.lineNo() << L") " << error.errorMsg() << std::endl;
        }
        QString error_msg = QString::fromStdWString(ss.str());
        m_pCompileInfo->appendPlainText(error_msg);
        moveCursor(errors[0].lineNo());
    }
}

void MainWindow::genExecutableSpec()
{
    if (Utility::fileExist(m_currentFilePath))
    {
        genExecutableSpec4SavedFeature();
    }
    else
    {
        QMessageBox::warning(this, tr("Executable specification"),
                                   tr("Current Gherkin document has not been saved."),
                                   QMessageBox::Ok);
    }
}

void MainWindow::genExecutableSpec4SavedFeature()
{
    showCompileInfo();
    QString msg("------------------\nStart generating executable specification...\n");
    std::wstring gherkin = preparingPrettyGherkin(msg);

    GherkinIF parser;
    std::wstring formattedGherkin;
    std::wstring dir = Utility::getDirFromFilepathWS(m_currentFilePath);
    ExecutableSpecFileNames output;

    bool success = parser.GenExecSpec(gherkin, formattedGherkin, dir, output);
    m_pEditor->setErrorLines(parser.errorLines());
    if (success)
    {
        displayPrettyFormattedGherkin(formattedGherkin);
        displayExecutableSpecFileNames(output);
    }
    else
    {
        std::vector<GherkinErrorMsg> errors = parser.errorMsgs();
        displayErrorMessages(errors);
    }
    m_pCompileInfo->moveCursor(QTextCursor::End);
}

void MainWindow::displayExecutableSpecFileNames(ExecutableSpecFileNames& output)
{
    m_pCompileInfo->appendPlainText(QString::fromStdWString(output.StepHeaderFileName));
    m_pCompileInfo->appendPlainText(QString::fromStdWString(output.StepImplFileName));
    m_pCompileInfo->appendPlainText(QString::fromStdWString(output.StepModelTemplateHeaderFileName));
    m_pCompileInfo->appendPlainText(QString::fromStdWString(output.StepModelTemplateImplFileName));
    m_pCompileInfo->appendPlainText(QString::fromStdWString(output.FeatureFileName));
}

void MainWindow::clearCompileInfo()
{
    m_pCompileInfo->clear();
}

void MainWindow::showCompileInfo()
{
    m_pCompileInfo->setVisible(true);

    showCompileInfoAction->setEnabled(false);
    hideCompileInfoAction->setEnabled(true);
}

void MainWindow::hideCompileInfo()
{
    m_pCompileInfo->setVisible(false);

    showCompileInfoAction->setEnabled(true);
    hideCompileInfoAction->setEnabled(false);
}

void MainWindow::moveCursor(size_t lineNo)
{
    if (lineNo == 0)
        m_pEditor->moveCursor(QTextCursor::Start);
    else
    {
        QTextCursor cursor(m_pEditor->document()->findBlockByLineNumber(lineNo - 1)); // lineNo - 1 because line number starts from 0
        m_pEditor->setTextCursor(cursor);
    }
}

void MainWindow::setupMenues()
{
    setupFileMenu();
    setupEditMenu();
    setupCompileMenu();
    setupViewMenu();
    setupHelpMenu();
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    ui->menuBar->addMenu(fileMenu);

    newAction = fileMenu->addAction(QIcon(":/file_new.png"), tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    openAction = fileMenu->addAction(QIcon(":/file_open.png"), tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    saveAction = fileMenu->addAction(QIcon(":/file_save.png"), tr("&Save"), this, SLOT(saveFile()), QKeySequence::Save);
    saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    saveAction->setEnabled(false);

    fileMenu->addAction(tr("Save As..."), this, SLOT(saveAsFile()), QKeySequence::SaveAs);
    fileMenu->addAction(tr("Open Containing folder"), this, SLOT(openContainingFolder()));
    setupRecentFilesMenu(fileMenu);
    fileMenu->addAction(tr("E&xit"), this, SLOT(close()), QKeySequence::Quit);
}

void MainWindow::setupCompileMenu()
{
    QMenu *compileMenu = new QMenu(tr("Compile"), this);
    ui->menuBar->addMenu(compileMenu);

    prettyGherkinAction = compileMenu->addAction(QIcon(":/compile_format.png"), tr("Pretty Gherkin"), this, SLOT(prettyGherkin()));
    prettyGherkinAction->setShortcut(Qt::Key_F5);
    prettyGherkinAction->setEnabled(false);

    genTestCodeAction = compileMenu->addAction(QIcon(":/compile_gencode.png"), tr("Generate executable specification"), this, SLOT(genExecutableSpec()));
    genTestCodeAction->setShortcut(Qt::Key_F6);
    genTestCodeAction->setEnabled(false);
}

void MainWindow::setupEditMenu()
{
    QMenu *editMenu = new QMenu(tr("&Edit"), this);
    ui->menuBar->addMenu(editMenu);

    undoAction = editMenu->addAction(QIcon(":/edit_undo.png"), tr("Undo"), this, SLOT(undo()), QKeySequence::Undo);
    undoAction->setEnabled(false);
    connect(m_pEditor, SIGNAL(undoAvailable(bool)), this, SLOT(onUndoAvailable(bool)));

    redoAction = editMenu->addAction(QIcon(":/edit_redo.png"), tr("Redo"), this, SLOT(redo()), QKeySequence::Redo);
    redoAction->setEnabled(false);
    connect(m_pEditor, SIGNAL(redoAvailable(bool)), this, SLOT(onRedoAvailable(bool)));

    findAction = editMenu->addAction(QIcon(":/edit_find.png"), tr("Find"), this, SLOT(find()), QKeySequence::Find);
    editMenu->addAction(tr("Find Next"), m_pFindDialog, SLOT(findNext()), QKeySequence::FindNext);
    editMenu->addAction(tr("Find Previous"), m_pFindDialog, SLOT(findPrev()), QKeySequence::FindPrevious);
    findReplaceAction = editMenu->addAction(QIcon(":/edit_find_replace.png"), tr("Find/Replace"), this, SLOT(findReplace()), QKeySequence::Replace);

    setFontAction = editMenu->addAction(QIcon(":/edit_font.png"), tr("Change font"), this, SLOT(setFont()));
}

void MainWindow::setupRecentFilesMenu(QMenu *fileMenu)
{
    for(int i = 0; i < MAX_RECENT_FILE_NR; i++)
    {
        QAction* recentFileAction = new QAction(this);
        QObject::connect(recentFileAction, SIGNAL(triggered()), this, SLOT(openRecentFile()));
        recentFileActionList.append(recentFileAction);
    }
    hideAllRecentFileActions();

    QMenu* recentFilesMenu = fileMenu->addMenu(tr("Open Recent"));
    for(int i = 0; i < MAX_RECENT_FILE_NR; i++)
    {
        recentFilesMenu->addAction(recentFileActionList.at(i));
    }

    updateRecentActionList();
}

void MainWindow::hideAllRecentFileActions()
{
    for (int i = 0; i < MAX_RECENT_FILE_NR; i++)
    {
        recentFileActionList.at(i)->setVisible(false);
    }
}

void MainWindow::updateRecentActionList()
{
    hideAllRecentFileActions(); // hide all recent file actions as default

    QStringList recentFilePaths = UserSetting::recentFiles();
    const int recentFileNr = (recentFilePaths.size() <= MAX_RECENT_FILE_NR) ?
                                recentFilePaths.size() : MAX_RECENT_FILE_NR;
    for (int i = 0; i < recentFileNr; i++)
    {
        QString strippedName = QFileInfo(recentFilePaths.at(i)).fileName();
        recentFileActionList.at(i)->setText(strippedName);
        recentFileActionList.at(i)->setData(recentFilePaths.at(i));
        recentFileActionList.at(i)->setVisible(true);
    }
}

void MainWindow::adjustForCurrentFile(const QString &filePath)
{
    if (filePath.isEmpty()) return;

    QStringList recentFilePaths = UserSetting::recentFiles();
    recentFilePaths.removeAll(filePath);
    if (Utility::fileExist(filePath))
    {
        recentFilePaths.prepend(filePath);
        while (recentFilePaths.size() > MAX_RECENT_FILE_NR)
        {
            recentFilePaths.removeLast();
        }
    }

    UserSetting::recentFiles(recentFilePaths);
    updateRecentActionList();
}

void MainWindow::onUndoAvailable(bool available)
{
    undoAction->setEnabled(available);
}

void MainWindow::onRedoAvailable(bool available)
{
    redoAction->setEnabled(available);
}

void MainWindow::setFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, UserSetting::font(), this);
    if (ok)
    {
        UserSetting::font(font);
        m_pEditor->setFont(font);
    }
}

void MainWindow::setupViewMenu()
{
    QMenu *viewMenu = new QMenu(tr("&View"), this);
    ui->menuBar->addMenu(viewMenu);
    clearCompileInfoAction = viewMenu->addAction(QIcon(":/compile_clear.png"), tr("Clear compiling messages"), this, SLOT(clearCompileInfo()));
    showCompileInfoAction = viewMenu->addAction(QIcon(":/arrow_up.png"), tr("Show compiling message widget"), this, SLOT(showCompileInfo()));
    hideCompileInfoAction = viewMenu->addAction(QIcon(":/arrow_down.png"), tr("Hide compiling message widget"), this, SLOT(hideCompileInfo()));
    hideCompileInfoAction->setEnabled(false);
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    ui->menuBar->addMenu(helpMenu);
    helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void MainWindow::createToolBars()
{
    createFileToolBar();
    createEditToolBar();
    createCompileToolBar();
    createViewToolBar();
}

void MainWindow::createFileToolBar()
{
    ui->fileToolBar->addAction(newAction);
    ui->fileToolBar->addAction(openAction);
    ui->fileToolBar->addAction(saveAction);
}

void MainWindow::createEditToolBar()
{
    QToolBar* editToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, editToolBar);
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addAction(findAction);
    editToolBar->addAction(findReplaceAction);
    editToolBar->addAction(setFontAction);
}

void MainWindow::createCompileToolBar()
{
    QToolBar* compileToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, compileToolBar);
    compileToolBar->addAction(prettyGherkinAction);
    compileToolBar->addAction(genTestCodeAction);

    supportUnicodeAction = compileToolBar->addAction(QIcon(":/w.ico"), tr("Support unicode"), this, SLOT(supportUnicode()));
    supportUnicodeAction->setCheckable(true);
    supportUnicodeAction->setChecked(m_supportUnicode);
}

void MainWindow::createViewToolBar()
{
    QToolBar* viewToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, viewToolBar);
    viewToolBar->addAction(clearCompileInfoAction);
    viewToolBar->addAction(showCompileInfoAction);
    viewToolBar->addAction(hideCompileInfoAction);
}

void MainWindow::supportUnicode()
{
    m_supportUnicode = supportUnicodeAction->isChecked();
    UserSetting::supportUnicode(m_supportUnicode);
    CucumberCpp::BDDUtil::supportUnicode(m_supportUnicode);
}

void MainWindow::undo()
{
    m_pEditor->undo();
}

void MainWindow::redo()
{
    m_pEditor->redo();
}

void MainWindow::find()
{
    m_pFindDialog->showByUsingSelectedText();
}

void MainWindow::findReplace()
{
    m_pFindReplaceDialog->showByUsingSelectedText();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText())
    {
        QString path_mime = event->mimeData()->text();
        if (isValidFilePath(path_mime))
        {
            event->acceptProposedAction();
        }
    }
}

// drag&drop support
bool MainWindow::isValidFilePath(QString path_mime)
{
    QString filePath = Utility::fileMine2FilePath(path_mime);
    if (filePath != m_currentFilePath)
        return Utility::fileExist(filePath);
    else
        return false;
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasText())
    {
        QString filepath = Utility::fileMine2FilePath(mimeData->text());
        openFile(filepath);
    }
}

// processing application closing
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (canExit())
    {
        QRect rect{x(), y(), width(), height()};
        UserSetting::mainWindowRect(rect);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

bool MainWindow::canExit()
{
    if (!m_pEditor->document()->isModified()) return true;

    QMessageBox msgBox;
    msgBox.setText(tr("The document has been modified."));
    msgBox.setInformativeText(tr("Do you want to save your changes?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
          saveFile();
        return true;
      case QMessageBox::Discard:
        return true;
      case QMessageBox::Cancel:
        return false;
      default:
        return true;
    }
}

