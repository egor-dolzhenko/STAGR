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
#include "BlatSettingsDialog.h"
#include <QWidget>
#include <QSettings>

BlatSettingsDialog::BlatSettingsDialog(QWidget *parent)
	:QDialog(parent)
{
		
	//group boxes containing widgets for adjusting *blat* parameters
	QGroupBox *leftGroup = new QGroupBox("Blat Settings");
	QGroupBox *rightGroup = new QGroupBox(" ");
	
	//widgets corresponding to *-tileSize* parameter
	QLabel *tilesizeLabel = new QLabel("tile size: ");
	tilesizeComboBox = new QComboBox;
	tilesizeComboBox->addItem("8");
	tilesizeComboBox->addItem("9");
	tilesizeComboBox->addItem("10");
	tilesizeComboBox->addItem("11");
	tilesizeComboBox->addItem("12");
	
	//widgets corresponding to *-stepSize* parameter
	QLabel *stepsizeLabel = new QLabel("step size: ");
	stepsizeComboBox = new QComboBox;
	stepsizeComboBox->addItem("6");
	stepsizeComboBox->addItem("7");
	stepsizeComboBox->addItem("8");
	stepsizeComboBox->addItem("9");
	stepsizeComboBox->addItem("10");
	stepsizeComboBox->addItem("11");
	stepsizeComboBox->addItem("12");
	stepsizeComboBox->addItem("13");
	stepsizeComboBox->addItem("14");
	
	//widgets corresponding to *-oneOff* parameter
	oneoffCheckBox = new QCheckBox("allow one mismatch in the template",this);	
	
	//widgets corresponding to *-minMatch* parameter
	QLabel *minmatchLabel = new QLabel("min match: ");
	minmatchComboBox = new QComboBox;
	minmatchComboBox->addItem("2");
	minmatchComboBox->addItem("3");
	minmatchComboBox->addItem("4");
	
	//setup layout for left groupbox
	QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addWidget(tilesizeLabel, 	0, 0);
    leftLayout->addWidget(tilesizeComboBox,	0, 1);
    
    leftLayout->addWidget(stepsizeLabel,	1, 0);
    leftLayout->addWidget(stepsizeComboBox,	1, 1);
    
    leftLayout->addWidget(oneoffCheckBox,	2, 0, 1, 2);
    
    leftLayout->addWidget(minmatchLabel,	3, 0);
    leftLayout->addWidget(minmatchComboBox,	3, 1);
    
 	leftGroup->setLayout(leftLayout);

	//widgets corresponding to *-minScore* parameter
	QLabel *minscoreLabel = new QLabel("min score: ");
	minscoreLineEdit = new QLineEdit;

	//widgets corresponding to *-minIdentity* parameter
	QLabel *minidentityLabel = new QLabel("min identity: ");
	minidentityLineEdit = new QLineEdit;
	
	//widgets corresponding to *-maxGap* parameter
	QLabel *maxgapLabel = new QLabel("max gap: ");
	maxgapComboBox = new QComboBox;
	maxgapComboBox->addItem("0");
	maxgapComboBox->addItem("1");
	maxgapComboBox->addItem("2");
	maxgapComboBox->addItem("3");
		
	//setup layout for right groupbox
	QGridLayout *rightLayout = new QGridLayout;
	
	rightLayout->addWidget(minscoreLabel, 0, 0);
	rightLayout->addWidget(minscoreLineEdit, 0, 1);
	
	rightLayout->addWidget(minidentityLabel, 1, 0);
	rightLayout->addWidget(minidentityLineEdit, 1, 1);

	rightLayout->addWidget(maxgapLabel, 2, 0);
	rightLayout->addWidget(maxgapComboBox, 2, 1);
	
	rightGroup->setLayout(rightLayout);
	
	QGridLayout *mainLayout = new QGridLayout;
	
	QHBoxLayout *okCancelLayout = new QHBoxLayout;
	okButton = new QPushButton("OK");
	okCancelLayout->addStretch(1);
	okCancelLayout->addWidget(okButton);
	
	mainLayout->addWidget(leftGroup, 0, 0, 2, 1);
	mainLayout->addWidget(rightGroup, 0, 1);
	mainLayout->addLayout(okCancelLayout, 1, 1);
	setLayout(mainLayout);
	
	connect(okButton, SIGNAL(clicked()), this, SLOT(okPushed()));
}

void BlatSettingsDialog::okPushed()
{
	accept();
}


QStringList BlatSettingsDialog::blatSettingsPatrameterString(QString queryFilename, QString referenceFilename)
{
	QStringList arguments;
	
	arguments << referenceFilename;
	arguments << queryFilename;
	arguments << "out";
	arguments << "-out=blast8";
	arguments << "-tileSize=" + tilesizeComboBox->itemText( tilesizeComboBox->currentIndex() );
	arguments << "-stepSize=" + stepsizeComboBox->itemText( stepsizeComboBox->currentIndex() );
	if(!oneoffCheckBox->isChecked()) arguments << "-oneOff=1";
	arguments << "-minMatch=" + minmatchComboBox->itemText( minmatchComboBox->currentIndex() );
	arguments << "-maxGap=" + maxgapComboBox->itemText( maxgapComboBox->currentIndex() );
	
	if(minscoreLineEdit->text() != "")
		arguments << "-minScore=" + minscoreLineEdit->text();
	
	if(minidentityLineEdit->text() != "")
		arguments << "-minIdentity=" + minidentityLineEdit->text();

	return arguments;
}