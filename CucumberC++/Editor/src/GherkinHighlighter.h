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

#ifndef GHERKIN_HIGHLIGHTER_H
#define GHERKIN_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class GherkinHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    GherkinHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    void processMultiLineComment(const QString &text);
    void processDocString(const QString &text);

private:
    void setupFeatureRule();
    void setupTagRule();
    void setupScenarioRule();
    void setupStepRule();
    void setupTableRule();
    void setupDocStringRule();
    void setupCommentRule();
    void setupAttributeRule();
    void precessNewDocString(const QString &text);
    void precessContinuedDocString(const QString &text);
    void setupRules(QTextCharFormat& format, QStringList& patterns);
    QTextCharFormat createFormat(QColor color, bool bold);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    enum BlockState
    {
        NOT_IN_MULTI_LINE_PATTERN,
        IN_COMMENT,
        IN_DOC_STRING
    };

    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;
    QRegExp docStringExpression;

    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat docStringFormat;
};

#endif
