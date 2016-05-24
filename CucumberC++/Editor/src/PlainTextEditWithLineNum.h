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

#ifndef PLAIN_TEXT_EDIT_WITH_LINE_NUM_H
#define PLAIN_TEXT_EDIT_WITH_LINE_NUM_H

#include <vector>
#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

class PlainTextEditWithLineNum : public QPlainTextEdit
{
    Q_OBJECT

public:
    PlainTextEditWithLineNum(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setErrorLines(std::vector<int> errorLines){ m_ErrorLines = errorLines; }

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    // We do not provide drag&drop here. Let MainWindow do drag&drop
    void dragEnterEvent(QDragEnterEvent *event) override { event->ignore(); }
    void dragMoveEvent(QDragMoveEvent *event) override { event->ignore(); }
    void dragLeaveEvent(QDragLeaveEvent *event) override { event->ignore(); }
    void dropEvent(QDropEvent *event) override { event->ignore(); }

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    bool isErrorLine(int lineNo);

private:
    QWidget *lineNumberArea;
    std::vector<int> m_ErrorLines;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(PlainTextEditWithLineNum *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    PlainTextEditWithLineNum *codeEditor;
};


#endif
