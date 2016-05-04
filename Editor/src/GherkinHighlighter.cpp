#include "GherkinHighlighter.h"

GherkinHighlighter::GherkinHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    setupFeatureRule();
    setupTagRule();
    setupScenarioRule();
    setupStepRule();
    setupTableRule();
    setupDocStringRule();
    setupCommentRule();
    setupAttributeRule();
}

void GherkinHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(NOT_IN_MULTI_LINE_PATTERN);
    processMultiLineComment(text);
    processDocString(text);
}

void GherkinHighlighter::processMultiLineComment(const QString &text)
{
    if (previousBlockState() == IN_DOC_STRING) return;

    int startIndex = 0;
    if (previousBlockState() != IN_COMMENT)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0)
    {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(IN_COMMENT);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}

void GherkinHighlighter::processDocString(const QString &text)
{
    if (previousBlockState() == IN_COMMENT) return;

    if (previousBlockState() != IN_DOC_STRING)
    {
        precessNewDocString(text);
    }
    else
    {
        precessContinuedDocString(text);
    }
}

void GherkinHighlighter::precessNewDocString(const QString &text)
{
    int startIndex = docStringExpression.indexIn(text);
    if (startIndex >= 0)
    {
        setCurrentBlockState(IN_DOC_STRING);
        int docStringLength = text.length() - startIndex
                             + docStringExpression.matchedLength();
        setFormat(startIndex, docStringLength, docStringFormat);
    }
}

void GherkinHighlighter::precessContinuedDocString(const QString &text)
{
    int startIndex = 0;
    while (startIndex >= 0)
    {
        int endIndex = docStringExpression.indexIn(text, startIndex);
        int docStringLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(IN_DOC_STRING);
            docStringLength = text.length() - startIndex;
        } else {
            docStringLength = endIndex - startIndex
                            + docStringExpression.matchedLength();
        }
        setFormat(startIndex, docStringLength, docStringFormat);
        startIndex = docStringExpression.indexIn(text, startIndex + docStringLength);
    }
}

void GherkinHighlighter::setupFeatureRule()
{
    HighlightingRule rule;
    rule.pattern = QRegExp("^\\s*Feature\\s*:");
    rule.format = createFormat(Qt::red, true);
    highlightingRules.append(rule);
}

void GherkinHighlighter::setupTagRule()
{
    HighlightingRule rule;
    rule.pattern = QRegExp("^\\s*@.*");
    rule.format = createFormat(QColor(138, 43, 226), true); // blueviolet
    highlightingRules.append(rule);
}

void GherkinHighlighter::setupScenarioRule()
{
    QTextCharFormat format = createFormat(Qt::blue, true);
    QStringList keywordPatterns {"^\\s*Background\\s*:",
                                 "^\\s*Scenario\\s*:",
                                 "^\\s*Scenario\\s*Outline:",
                                 "^\\s*Examples\\s*:"
                                };
    setupRules(format, keywordPatterns);
}

void GherkinHighlighter::setupRules(QTextCharFormat& format, QStringList& patterns)
{
    HighlightingRule rule;
    for (const QString &pattern : patterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = format;
        highlightingRules.append(rule);
    }
}

void GherkinHighlighter::setupStepRule()
{
    QTextCharFormat format = createFormat(QColor(0x40, 0x80, 0x80), true); // deepskyblue
    QStringList stepPatterns {"^\\s*Given\\s",
                              "^\\s*When\\s",
                              "^\\s*Then\\s",
                              "^\\s*And\\s",
                              "^\\s*But\\s"
                             };

    setupRules(format, stepPatterns);
}

void GherkinHighlighter::setupTableRule()
{
    HighlightingRule rule;
    rule.pattern = QRegExp("^\\s*\\|.*\\|\\s*$"); // 空白|<文字列>|
    rule.format = createFormat(QColor(139, 69, 19), false);
    highlightingRules.append(rule);
}

void GherkinHighlighter::setupDocStringRule()
{
    docStringFormat.setForeground(QColor(139, 69, 19));  // saddlebrown
    docStringExpression = QRegExp("^\\s*\"\"\"\\s*$");   // 空白"""空白
}

void GherkinHighlighter::setupCommentRule()
{
    QColor limegreen(50, 205, 50);
    QColor comment_color = limegreen.darker(160);

    // single line comment
    HighlightingRule rule;
    rule.pattern = QRegExp("^\\s*(#|//).*");
    rule.format = createFormat(comment_color, false);
    highlightingRules.append(rule);

    // multi line comment
    multiLineCommentFormat.setForeground(comment_color);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void GherkinHighlighter::setupAttributeRule()
{
    HighlightingRule rule;
    rule.pattern = QRegExp("(\\b|\\s)\\[\\[.+\\]\\]");  // [[文字列]]
    rule.format = createFormat(Qt::darkGreen, false);
    highlightingRules.append(rule);
}

QTextCharFormat GherkinHighlighter::createFormat(QColor color, bool bold)
{
    QTextCharFormat format;
    format.setForeground(color);
    if (bold) format.setFontWeight(QFont::Bold);

    return format;
}
