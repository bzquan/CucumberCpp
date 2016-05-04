/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

namespace Ui {
    class FindReplaceDialog;
}

class QTextEdit;
class QSettings;
class QPlainTextEdit;

/**
  * A find/replace dialog.
  *
  * It relies on a FindReplaceForm object (see that class for the functionalities provided).
  */
class FindReplaceDialog : public QDialog {
    Q_OBJECT
public:
    FindReplaceDialog(QPlainTextEdit *pTextEdit);
    virtual ~FindReplaceDialog();

    /**
      * Writes the state of the form to the passed settings.
      * @param settings
      * @param prefix the prefix to insert in the settings
      */
    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

    /**
      * Reads the state of the form from the passed settings.
      * @param settings
      * @param prefix the prefix to look for in the settings
      */
    virtual void readSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

    void showByUsingSelectedText();

public slots:
    /**
     * Finds the next occurrence
     */
    void findNext();

    /**
     * Finds the previous occurrence
     */
    void findPrev();

protected:
    void changeEvent(QEvent *e);

    Ui::FindReplaceDialog *ui;
};

#endif // FINDREPLACEDIALOG_H
