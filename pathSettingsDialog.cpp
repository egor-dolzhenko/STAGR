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
#include "pathSettingsDialog.h"
#include <QWidget>
#include <QSettings>

PathSettingsDialog::PathSettingsDialog(QWidget *parent)
	:QDialog(parent)
{

	QLabel *blastnLabel = new QLabel("Blastn path:");
	QLabel *blatLabel = new QLabel("Blat path:");
	
	blastnPathLineEdit = new QLineEdit("/usr/local/ncbi/blast/bin/blastn");
	blatPathLineEdit = new QLineEdit("/Users/egor/blat/blat");
	
	okButton = new QPushButton("OK");
	
	QGridLayout *layout = new QGridLayout;
	
	layout->addWidget(blastnLabel, 0, 0);
	layout->addWidget(blastnPathLineEdit, 0, 1);
	layout->addWidget(blatLabel, 1, 0);
	layout->addWidget(blatPathLineEdit, 1, 1);
	layout->addWidget(okButton, 2, 1);
	
	setLayout(layout);
	connect(okButton, SIGNAL(clicked()), this, SLOT(okPushed()));
}

void PathSettingsDialog::okPushed()
{
	accept();
}

QString PathSettingsDialog::blastnPath()
{
	return blastnPathLineEdit->text();
}

QString PathSettingsDialog::blatPath()
{
	return blatPathLineEdit->text();
}