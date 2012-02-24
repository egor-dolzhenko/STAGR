#include <QtGui>

#include "scriptHighlighter.h"

ScriptHighlighter::ScriptHighlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
{
	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	
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
		
	
}

 void ScriptHighlighter::highlightBlock(const QString &text)
 {
  
  	foreach( const QRegExp &expression, keywordExpressions )
  	{
  		int index = expression.indexIn(text);
  		while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, keywordFormat);
             index = expression.indexIn(text, index + length);
         }
  	}
  
  	// foreach (const HighlightingRule &rule, highlightingRules) {
//          QRegExp expression(rule.pattern);
//          int index = expression.indexIn(text);
//          while (index >= 0) {
//              int length = expression.matchedLength();
//              setFormat(index, length, rule.format);
//              index = expression.indexIn(text, index + length);
//          }
//      }
//      setCurrentBlockState(0);
// 
//      int startIndex = 0;
//      if (previousBlockState() != 1)
//          startIndex = commentStartExpression.indexIn(text);
// 
//      while (startIndex >= 0) {
//          int endIndex = commentEndExpression.indexIn(text, startIndex);
//          int commentLength;
//          if (endIndex == -1) {
//              setCurrentBlockState(1);
//              commentLength = text.length() - startIndex;
//          } else {
//              commentLength = endIndex - startIndex
//                              + commentEndExpression.matchedLength();
//          }
//          setFormat(startIndex, commentLength, multiLineCommentFormat);
//          startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
//      }
 }