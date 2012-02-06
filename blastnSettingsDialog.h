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

#ifndef BLASTNSETTINGSDIALOG_H
#define BLASTNSETTINGSDIALOG_H

#include <QDialog>

class QPushButton;
class QComboBox;
class QCheckBox;
class QLineEdit;

class BlastnSettingsDialog : public QDialog
{
	Q_OBJECT
	
public:
	BlastnSettingsDialog(QWidget *parent);
	QStringList blastSettingsPatrameterString(QString queryFilename, QString referenceFilename);
	
private:
	QPushButton *okButton;
	QComboBox *wordsizeComboBox;
	QComboBox *matchscoreComboBox;
	QComboBox *mismatchscoreComboBox;
	QComboBox *openComboBox;
	QComboBox *extensionComboBox;
	QCheckBox *dustCheckBox;
	QLineEdit *identityLineEdit;
	QLineEdit *expectedvalueLineEdit;
	
private slots:
	void okPushed();
	void cancelPushed();
	void updateExtensionComboBox(int index);
	void updateMismatchComboBox(int index);
};
#endif //BLASTNSETTINGSDIALOG_H