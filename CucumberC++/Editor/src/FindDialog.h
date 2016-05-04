/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

#include "FindReplaceDialog.h"

class QPlainTextEdit;

/**
  * A find dialog (it is basically the same
  * as FindReplaceDialog without the replace related widgets).
  */
class FindDialog : public FindReplaceDialog {
    Q_OBJECT
public:
    FindDialog(QPlainTextEdit *pTextEdit);
    ~FindDialog();

    /**
      * Writes the state of the form to the passed settings.
      * @param settings
      * @param prefix the prefix to insert in the settings
      */
    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindDialog");

    /**
      * Reads the state of the form from the passed settings.
      * @param settings
      * @param prefix the prefix to look for in the settings
      */
    virtual void readSettings(QSettings &settings, const QString &prefix = "FindDialog");
};

#endif // FINDDIALOG_H
