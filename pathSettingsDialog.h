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

#ifndef PATHSETTINGSDIALOG_H
#define PATHSETTINGSDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class PathSettingsDialog : public QDialog
{
	Q_OBJECT;
	
public:
	PathSettingsDialog(QWidget *parent);
	QString blastnPath();
	QString blatPath();
	
private:
	QLineEdit *blastnPathLineEdit;
	QLineEdit *blatPathLineEdit;
	QPushButton *okButton;
	
private slots:
	void okPushed();
};

#endif //PATHSETTINGSDIALOG_H
