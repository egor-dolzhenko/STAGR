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

#ifndef SCRITPEDITDIALOG_H
#define SCRIPTEDITDIALOG_H

#include <QDialog>

class QTextEdit;

class ScriptEditDialog : public QDialog
{
	Q_OBJECT
	
public:
	ScriptEditDialog(QWidget *parent);
	QString getScript();
	
private:
	QTextEdit *editor;
	
};

#endif //SCRIPTEDITDIALOG_H