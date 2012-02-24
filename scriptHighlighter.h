#ifndef SCRIPTHEIGHLIGHTER_H
#define SCRIPTHEIGHLIGHTER_H

#include <QSyntaxHighlighter>

class ScriptHighlighter : public QSyntaxHighlighter
 {
     Q_OBJECT

 public:
     ScriptHighlighter(QTextDocument *parent = 0);

 protected:
     void highlightBlock(const QString &text);

 private:
     //struct HighlightingRule
     //{
     //    QRegExp pattern;
     //    QTextCharFormat format;
     //};
     //QVector<HighlightingRule> highlightingRules;

     //QRegExp commentStartExpression;
     //QRegExp commentEndExpression;

     QTextCharFormat keywordFormat;
     QVector<QRegExp> keywordExpressions;
     //QTextCharFormat classFormat;
     //QTextCharFormat singleLineCommentFormat;
     //QTextCharFormat multiLineCommentFormat;
     //QTextCharFormat quotationFormat;
     //QTextCharFormat functionFormat;
 };
 
 #endif //SCRIPTHEIGHLIGHTER_H