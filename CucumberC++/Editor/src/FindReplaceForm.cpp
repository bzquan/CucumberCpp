/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#include <QtGui>
#include <QTextEdit>
#include <QRegExp>
#include <QSettings>
#include <QPlainTextEdit>

#include "FindReplaceForm.h"
#include "ui_findreplaceform.h"

#define TEXT_TO_FIND "textToFind"
#define TEXT_TO_REPLACE "textToReplace"
#define DOWN_RADIO "downRadio"
#define UP_RADIO "upRadio"
#define CASE_CHECK "caseCheck"
#define WHOLE_CHECK "wholeCheck"
#define REGEXP_CHECK "regexpCheck"

FindReplaceForm::FindReplaceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceForm),
    m_pTextEdit(NULL)
{
    ui->setupUi(this);

    ui->errorLabel->setText("");

    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(textToFindChanged()));
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(validateRegExp(QString)));

    connect(ui->regexCheckBox, SIGNAL(toggled(bool)), this, SLOT(regexpSelected(bool)));

    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find()));

    connect(ui->replaceButton, SIGNAL(clicked()), this, SLOT(replace()));
    connect(ui->replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAll()));
}

FindReplaceForm::~FindReplaceForm()
{
    delete ui;
}

void FindReplaceForm::hideReplaceWidgets() {
    ui->replaceLabel->setVisible(false);
    ui->textToReplace->setVisible(false);
    ui->replaceButton->setVisible(false);
    ui->replaceAllButton->setVisible(false);
}

void FindReplaceForm::setTextEdit(QPlainTextEdit *pTextEdit) {
    m_pTextEdit = pTextEdit;
}

void FindReplaceForm::resetInitialText()
{
    if (m_pTextEdit == NULL) return;

    QString text = m_pTextEdit->textCursor().selectedText();
    if (text.length() > 0)
    {
        ui->textToFind->setText(text);
    }
}

void FindReplaceForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FindReplaceForm::textToFindChanged() {
    bool hasFindableText = ui->textToFind->text().size() > 0;
    ui->findButton->setEnabled(hasFindableText);

    bool editable = !m_pTextEdit->isReadOnly();
    ui->replaceButton->setEnabled(hasFindableText && editable);
    ui->replaceAllButton->setEnabled(hasFindableText && editable);
}

void FindReplaceForm::regexpSelected(bool sel) {
    if (sel)
        validateRegExp(ui->textToFind->text());
    else
        validateRegExp("");
}

void FindReplaceForm::validateRegExp(const QString &text) {
    if (!ui->regexCheckBox->isChecked() || text.size() == 0) {
        ui->errorLabel->setText("");
        return; // nothing to validate
    }

    QRegExp reg(text,
                (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

    if (reg.isValid()) {
        showError("");
    } else {
        showError(reg.errorString());
    }
}

void FindReplaceForm::showError(const QString &error) {
    if (error == "") {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:#ff0000;\">" +
                                error +
                                "</spam>");
    }
}

void FindReplaceForm::showMessage(const QString &message) {
    if (message == "") {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:green;\">" +
                                message +
                                "</spam>");
    }
}

void FindReplaceForm::find() {
    find(ui->downRadioButton->isChecked());
}

void FindReplaceForm::find(bool next) {
    if (m_pTextEdit == NULL)
        return; // TODO: show some warning?

    // backward search
    bool back = !next;

    QTextDocument::FindFlags flags;

    if (back)
        flags |= QTextDocument::FindBackward;
    if (ui->caseCheckBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (ui->wholeCheckBox->isChecked())
        flags |= QTextDocument::FindWholeWords;

    const QString &toSearch = ui->textToFind->text();
    if (ui->regexCheckBox->isChecked()) {
        QRegExp regex(toSearch,
                    (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
        m_pTextEdit->find(regex, flags);
    } else {
        m_pTextEdit->find(toSearch, flags);
    }
}

void FindReplaceForm::replace() {
    if (!m_pTextEdit->textCursor().hasSelection()) {
        find();
    } else {
        m_pTextEdit->textCursor().insertText(ui->textToReplace->text());
        find();
    }
}

void FindReplaceForm::replaceAll() {
    m_pTextEdit->moveCursor(QTextCursor::Start);
    find();
    int i=0;
    while (m_pTextEdit->textCursor().hasSelection()){
        m_pTextEdit->textCursor().insertText(ui->textToReplace->text());
        find();
        i++;
    }
    showMessage(tr("Replaced %1 occurrence(s)").arg(i));
}

void FindReplaceForm::writeSettings(QSettings &settings, const QString &prefix) {
    settings.beginGroup(prefix);
    settings.setValue(TEXT_TO_FIND, ui->textToFind->text());
    settings.setValue(TEXT_TO_REPLACE, ui->textToReplace->text());
    settings.setValue(DOWN_RADIO, ui->downRadioButton->isChecked());
    settings.setValue(UP_RADIO, ui->upRadioButton->isChecked());
    settings.setValue(CASE_CHECK, ui->caseCheckBox->isChecked());
    settings.setValue(WHOLE_CHECK, ui->wholeCheckBox->isChecked());
    settings.setValue(REGEXP_CHECK, ui->regexCheckBox->isChecked());
    settings.endGroup();
}

void FindReplaceForm::readSettings(QSettings &settings, const QString &prefix) {
    settings.beginGroup(prefix);
    ui->textToFind->setText(settings.value(TEXT_TO_FIND, "").toString());
    ui->textToReplace->setText(settings.value(TEXT_TO_REPLACE, "").toString());
    ui->downRadioButton->setChecked(settings.value(DOWN_RADIO, true).toBool());
    ui->upRadioButton->setChecked(settings.value(UP_RADIO, false).toBool());
    ui->caseCheckBox->setChecked(settings.value(CASE_CHECK, false).toBool());
    ui->wholeCheckBox->setChecked(settings.value(WHOLE_CHECK, false).toBool());
    ui->regexCheckBox->setChecked(settings.value(REGEXP_CHECK, false).toBool());
    settings.endGroup();
}
