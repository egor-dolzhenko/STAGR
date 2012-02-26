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
 
	QTextCharFormat keywordFormat;
	QTextCharFormat commentFormat;
	QVector<QRegExp> keywordExpressions;
	QRegExp commentExpression;

};
 
 #endif //SCRIPTHEIGHLIGHTER_H