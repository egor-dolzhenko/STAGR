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
#include "BlastnSettingsDialog.h"
#include <QWidget>
#include <QSettings>

BlastnSettingsDialog::BlastnSettingsDialog(QWidget *parent) //, QString parameters
	:QDialog(parent)
{
	
	//QSettings settings;
    //restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
	
	//group boxes containing widgets for adjusting *blastn* parameters
	QGroupBox *alignmentGroup = new QGroupBox("Alignment");
	QGroupBox *filteringGroup = new QGroupBox("Filtering");
	QGroupBox *cutoffsGroup = new QGroupBox("Cutoffs");
	
	//widgets corresponding to *word_dsize* parameter
	QLabel *wordsizeLabel = new QLabel("word size: ");
	wordsizeComboBox = new QComboBox;
	wordsizeComboBox->addItem("7");
	wordsizeComboBox->addItem("11");
	wordsizeComboBox->addItem("15");
	wordsizeComboBox->addItem("16");
	wordsizeComboBox->addItem("20");
	wordsizeComboBox->addItem("24");
	wordsizeComboBox->addItem("28");
	wordsizeComboBox->addItem("32");
	wordsizeComboBox->addItem("48");
	wordsizeComboBox->addItem("64");
	wordsizeComboBox->addItem("128");
	wordsizeComboBox->addItem("256");
	
	//widgets corresponding to *reward* parameter
	QLabel *matchscoreLabel = new QLabel("match score: ");
	matchscoreComboBox = new QComboBox;
	matchscoreComboBox->addItem("1");
	matchscoreComboBox->addItem("2");
	
	//widgets corresponding to *penalty* parameter
	QLabel *mismatchscoreLabel = new QLabel("mismatch score: ");
	mismatchscoreComboBox = new QComboBox;
	mismatchscoreComboBox->addItem("-1");
	mismatchscoreComboBox->addItem("-2");
	mismatchscoreComboBox->addItem("-3");
	mismatchscoreComboBox->addItem("-4");

	//checkbox to enable/disable search for gapped alignments
	gappedAlignment = new QCheckBox("gapped alignment", this);
	
	//widgets corresponding to *gapopen* and *gapextend* parameters
	QLabel *openLabel = new QLabel("open: ");
	QLabel *extensionLabel = new QLabel("extension: ");
	openComboBox = new QComboBox;
	extensionComboBox = new QComboBox;
	openComboBox->addItem("0");
	openComboBox->addItem("1");
	openComboBox->addItem("2");
	openComboBox->addItem("3");
	openComboBox->addItem("4");
	extensionComboBox->addItem("2");
	extensionComboBox->addItem("3");
	extensionComboBox->addItem("4");
	
	//setup layout for alignment combobox
	QGridLayout *alignmentLayout = new QGridLayout;
    alignmentLayout->addWidget(wordsizeLabel, 			0, 0);
    alignmentLayout->addWidget(wordsizeComboBox,		0, 1);
    alignmentLayout->addWidget(matchscoreLabel,			1, 0);
    alignmentLayout->addWidget(matchscoreComboBox,		1, 1);
    alignmentLayout->addWidget(mismatchscoreLabel,		2, 0);
    alignmentLayout->addWidget(mismatchscoreComboBox,	2, 1);
    alignmentLayout->addWidget(gappedAlignment, 		3, 0, 1, 2);
    alignmentLayout->addWidget(openLabel,				4, 0);
    alignmentLayout->addWidget(openComboBox,			4, 1);
    alignmentLayout->addWidget(extensionLabel,			5, 0);
    alignmentLayout->addWidget(extensionComboBox,		5, 1);

	alignmentGroup->setLayout(alignmentLayout);
	
	//widgets corresponding to enable/disable *dust* filtering algorithm
	dustCheckBox = new QCheckBox("enable dust filtering algorithm",this);
	
	
	//setup layout for filtering combobox
	QGridLayout *dustLayout = new QGridLayout;
	dustLayout->addWidget(dustCheckBox,	0,	0);
	
	filteringGroup->setLayout(dustLayout);
	
	//widgets corresponding to *evalue* parameter
	QLabel *expectedvalueLabel = new QLabel("expected value: ");
	expectedvalueLineEdit = new QLineEdit;

	//widgets corresponding to *perc_identity* parameter
	QLabel *identityLabel = new QLabel("percent identity: ");
	identityLineEdit = new QLineEdit;
	
	//setup layout for cutoffs combobox
	QGridLayout *cutoffsLayout = new QGridLayout;
	cutoffsLayout->addWidget(expectedvalueLabel, 0, 0);
	cutoffsLayout->addWidget(expectedvalueLineEdit, 0, 1);
	cutoffsLayout->addWidget(identityLabel, 1, 0);
	cutoffsLayout->addWidget(identityLineEdit, 1, 1);
	
	
	cutoffsGroup->setLayout(cutoffsLayout);
	
	QGridLayout *mainLayout = new QGridLayout;
	
	QHBoxLayout *okCancelLayout = new QHBoxLayout;
	okButton = new QPushButton("OK");
	okCancelLayout->addStretch(1);
	okCancelLayout->addWidget(okButton);
	
	mainLayout->addWidget(alignmentGroup, 0, 0, 3, 1);
	mainLayout->addWidget(filteringGroup, 0, 1);
	mainLayout->addWidget(cutoffsGroup, 1, 1);
	mainLayout->addLayout(okCancelLayout, 2, 1);
	setLayout(mainLayout);
	
	connect(okButton, SIGNAL(clicked()), this, SLOT(okPushed()));
	connect(openComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateExtensionComboBox(int)));
	connect(matchscoreComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateMismatchComboBox(int)));
	
	setDefaults();
}

void BlastnSettingsDialog::setDefaults()
{
	wordsizeComboBox->setCurrentIndex(6);
	matchscoreComboBox->setCurrentIndex(0);
	mismatchscoreComboBox->setCurrentIndex(0);
	openComboBox->setCurrentIndex(1);
	extensionComboBox->setCurrentIndex(0);
	gappedAlignment->setChecked(true);
}

void BlastnSettingsDialog::okPushed()
{
	accept();
}

void BlastnSettingsDialog::cancelPushed()
{
	reject();
}

QStringList BlastnSettingsDialog::blastSettingsPatrameterString(QString queryFilename, QString referenceFilename)
{
	QStringList arguments;
	if(!dustCheckBox->isChecked()) arguments << "-dust" << "no";
	arguments << "-query" << queryFilename;
	arguments << "-subject" << referenceFilename;
	arguments << "-outfmt" << "6";
	arguments << "-word_size" << wordsizeComboBox->itemText( wordsizeComboBox->currentIndex() );
	arguments << "-reward" << matchscoreComboBox->itemText( matchscoreComboBox->currentIndex() );
	arguments << "-penalty" << mismatchscoreComboBox->itemText( mismatchscoreComboBox->currentIndex() );
	arguments << "-gapopen" << openComboBox->itemText( openComboBox->currentIndex() );
	arguments << "-gapextend" << extensionComboBox->itemText( extensionComboBox->currentIndex() );
	if(!gappedAlignment->isChecked()) arguments << "-ungapped";
	if(identityLineEdit->text() != "") 
		arguments << "-perc_identity" + identityLineEdit->text();
	if(expectedvalueLineEdit->text() != "") 
		arguments << "-evalue" + expectedvalueLineEdit->text();
	
	return arguments;
}

void BlastnSettingsDialog::updateExtensionComboBox(int index)
{
	while(extensionComboBox->count() != 0) extensionComboBox->removeItem(0);
	QStringList newItems;
	if(openComboBox->currentText().toInt() >= 2) newItems << "1";
	newItems << "2" << "3" << "4";
	extensionComboBox->addItems(newItems);
}

void BlastnSettingsDialog::updateMismatchComboBox(int index)
{
	while(mismatchscoreComboBox->count() != 0) mismatchscoreComboBox->removeItem(0);
	QStringList newItems;
	int curMatchScore = matchscoreComboBox->currentText().toInt();
	if(curMatchScore == 1)
	{
		newItems << "-1" << "-2" << "-3" << "-4";
	}
	else if(curMatchScore == 2)
	{
		newItems << "-3";
	}
	else
	{
		newItems << "-5";
	}
	mismatchscoreComboBox->addItems(newItems);
}
