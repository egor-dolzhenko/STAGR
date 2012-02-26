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
	
	saveButton = new QPushButton("Save Script");
	loadButton = new QPushButton("Load Script");
	
	QGridLayout *mainLayout = new QGridLayout;
	
	mainLayout->addWidget(editor, 0, 0, 2, 2);
	mainLayout->addWidget(saveButton, 3, 0);
	mainLayout->addWidget(loadButton, 3, 1);
	
	//QVBoxLayout *mainLayout = new QVBoxLayout;
	//mainLayout->addWidget(editor);
	setLayout(mainLayout);
	
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveScript()));
	connect(loadButton, SIGNAL(clicked()), this, SLOT(loadScript()));
}

QString ScriptEditDialog::getScript()
{
	return editor->toPlainText();
}

void ScriptEditDialog::saveScript()
{
	QString saveFilename = QFileDialog::getSaveFileName(this, "Save Script", QDir::currentPath(), "Python files (*.py);;All files (*.*)");
	//qDebug() << saveFilename;
	if(saveFilename != "")
	{
		QFile file(saveFilename);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
         
         QTextStream in(&file);
         in << getScript();
         file.close();
	}
}

void ScriptEditDialog::loadScript()
{
	QString loadFilename = QFileDialog::getOpenFileName(this, "Load Script", QDir::currentPath(), "Python files (*.py);;All files (*.*)");
	qDebug() << loadFilename;
	if(loadFilename != "")
	{
		QFile file(loadFilename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
        
        QTextStream out( &file );
		editor->setText(out.readAll());

         //QTextStream out(&file);
         //out << getScript();
         file.close();
	}	
}