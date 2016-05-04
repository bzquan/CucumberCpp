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
