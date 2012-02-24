//	Copyright 2012 Egor Dolzhenko
//
//	This file is a part of STAGR.
//
//	STAGR is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
// 
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
// 
//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QtGui>
#include "scriptHighlighter.h"
#include "scriptEditDialog.h"

ScriptEditDialog::ScriptEditDialog(QWidget *parent)
	:QDialog(parent)
{
	editor = new QTextEdit;
	QFont font1("Monospace");
	font1.setStyleHint(QFont::TypeWriter);
	editor->setFont(font1);
	editor->setLineWrapMode(QTextEdit::NoWrap);
	scriptHighlighter = new ScriptHighlighter(editor->document());
	
	editor->setText("import operator\n\ndef annotate(initialAlignment):\n  return initialAlignment");
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(editor);
	setLayout(mainLayout);
}

QString ScriptEditDialog::getScript()
{
	return editor->toPlainText();
}