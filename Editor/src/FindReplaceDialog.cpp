/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#include <QPlainTextEdit>
#include "FindReplaceDialog.h"
#include "ui_findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QPlainTextEdit *pTextEdit) :
    QDialog(pTextEdit),
    ui(new Ui::FindReplaceDialog)
{
    ui->setupUi(this);
    ui->findReplaceForm->setTextEdit(pTextEdit);
    setModal(false);
}

FindReplaceDialog::~FindReplaceDialog()
{
    delete ui;
}

void FindReplaceDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FindReplaceDialog::writeSettings(QSettings &settings, const QString &prefix) {
    ui->findReplaceForm->writeSettings(settings, prefix);
}

void FindReplaceDialog::readSettings(QSettings &settings, const QString &prefix) {
    ui->findReplaceForm->readSettings(settings, prefix);
}

void FindReplaceDialog::findNext() {
    ui->findReplaceForm->findNext();
}

void FindReplaceDialog::findPrev() {
    ui->findReplaceForm->findPrev();
}

void FindReplaceDialog::showByUsingSelectedText()
{
    ui->findReplaceForm->resetInitialText();
    show();
}
