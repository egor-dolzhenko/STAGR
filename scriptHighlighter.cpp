#include <QtGui>

#include "scriptHighlighter.h"

ScriptHighlighter::ScriptHighlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
{
	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	
	commentFormat.setForeground(Qt::gray);
	
	 QStringList keywords;
	 keywords << "\\band\\b" << "\\bdel\\b" << "\\bfrom" << "\\bnot\\b" 
	 		  << "\\bwhile\\b" << "\\bas\\b"  << "\\belif\\b" << "\\bglobal\\b" 
	 		  << "\\bor\\b" << "\\bwith\\b" << "\\bassert\\b" 
	 		  << "\\belse\\b" << "\\bif\\b" << "\\bpass\\b"  
	 		  << "\\byield\\b"<< "\\bbreak\\b" << "\\bexcept\\b" 
	 		  << "\\bimport\\b" << "\\bprint\\b" << "\\bclass\\b" 
	 		  <<  "\\bexec\\b" << "\\bin\\b" << "\\braise\\b" 
	 		  << "\\bcontinue\\b" <<  "\\bfinally\\b" << "\\bis\\b" 
	 		  << "\\breturn\\b" << "\\bdef\\b" << "\\bfor\\b" 
	 		  << "\\blambda\\b" << "\\btry\\b";
	for(unsigned i = 0; i < keywords.size(); i++)
		keywordExpressions.append(QRegExp(keywords[i]));
		
	commentExpression = QRegExp("#[^\n]*");
}

 void ScriptHighlighter::highlightBlock(const QString &text)
 {
  
  	int index = 0;
  
  	foreach( const QRegExp &expression, keywordExpressions )
  	{
  		index = expression.indexIn(text);
  		while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, keywordFormat);
             index = expression.indexIn(text, index + length);
         }
  	}
  	
  	index = commentExpression.indexIn(text);
  	if( index != -1 )
  	{
  		int length = commentExpression.matchedLength();
  		setFormat(index, length, commentFormat);
  	}

}