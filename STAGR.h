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

//STAGR.h contains the definition of STAGR's main window class
#ifndef STAGR_H
#define STAGR_H

#include <QMainWindow>

//MultipleMatchesDialog visualizes and shows info about HSPs
//between given contigs
#include "MultipleMatchesDialog.h"

//Dialog with blastn settings
#include "blastnSettingsDialog.h"

//Dialog with blat settings
#include "blatSettingsDialog.h"

#include "scriptEditDialog.h"

#include "pathSettingsDialog.h"

#include "hsp.h"

//Location of the header file for including Python interpreter into STAGR
#include <Python.h>

//Classes used in the definition of StagrMainWindow class
class QTabWidget;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QActionGroup;

//Defines STAGR's main window
class StagrMainWindow : public QMainWindow
{
	//Enables use of signals and slots
	Q_OBJECT

	//Either blast or blat local-alignment heuristics can be used
	//to find HSPs
	enum InitialAligner {BLASTN, BLAT};

public:
	//Constructor
	StagrMainWindow(QWidget *parent = 0);

private slots:
	//Opens multiple matches dialog
	void openMDialogMultipleMatches();
	
	//Opens blastn settings dialog
	void openBlastnSettingsDialog();
	
	//Opens blat settings dialog
	void openBlatSettingsDialog();
	
	//Opens path settings dialog
	void openPathSettingsDialog();
	
	//get precursor filename from user through a file dialog
	void getPrecursorFilename();
	
	//get product filename from user through a file dialog
	void getProductFilename();
	
	void openScriptEditor();
		
	//Chooses blast aligner
	void selectBlastn();
	
	//Chooses blat aligner
	void selectBlat();
	
	//Runs main algorithm
	bool runStagr();
	
	//Opens settings dialog
	void openSettingsDialog();
	
private:
	void createToolBar();
	
	//Run blastn and populate alignments and numAlignments
	QString runBlastn(QString queryFilename, QString referenceFilename);

	//Runs blat
	QString runBlat(QString queryFilename, QString referenceFilename);

		
	void getAlignmentsSummary();
	
	void createTable();
	
	void createMenus();
	
	bool runFilteringAlgorithm(QString input, QString algorithmFilename);
	
	void alert(QString text);
	
	PyObject *runPythonFunction(QString filename, QString functionname, PyObject *argument);
		
	//main tab widget containing table
	QTabWidget *mainTabWidget;
	
	//Layout with labels listing query contigs file
	QHBoxLayout *querySequenceInformationLayout;
	
	//Layout with labels listing reference contigs file
	QHBoxLayout *referenceSequenceInformationLayout;
	
	//Main layout containing all widgets and layouts in main window
	QVBoxLayout *mainLayout;
	
	//Label that says: File with query contigs
	QLabel *querySequenceLabel;
	
	//Label that says: File with reference contigs
	QLabel *referenceSequenceLabel;
	
	//Name of the file with query contigs or <none specified>
	QLabel *querySequenceFilenameLabel;
	
	//name of the file with reference contigs or <none specified>
	QLabel *referenceSequenceFilenameLabel;
	
	//Table with names of pairs of contigs and the number of matches between them
	Table *table;
	
	//Toolbar containing essential commands and dialogs
	QToolBar *toolBar;
	
	//start STAGR algorithm
	QAction *startAction;
	
	//Open blastn settings dialog
	QAction *settingsAction;
	
	QAction *getPrecursorFilenameAction;
	
	QAction *getProductFilenameAction;
	
	//Open STAGR settings dialog
	QAction *stagrSettingsAction;
	
	QAction *runBlastnAction;
	
	QAction *runBlatAction;

	QAction *selectBlastnAction;
	
	QAction *selectBlatAction;

	QAction *filteringAction;

	QActionGroup *alignmentGroup;
	
	QAction *startEditorAction;
	
	QAction *openPathSettingsAction;
		
	//Dialog containing summary information about matches corresponding to
	//a particular query contig and multiple reference contigs
	MultipleMatchesDialog *multipleMatchesDialog;
	
	//Dialog containing blastn settings
	BlastnSettingsDialog* blastnSettingsDialog;
	
	//Dialog containing blat settings
	BlatSettingsDialog* blatSettingsDialog;
	
	ScriptEditDialog* scriptEditDialog;
	
	PathSettingsDialog* pathSettingsDialog;
	
	//Contains information about alignments found by blast
	QStringList* alignments;
	
	//Number of elements in the alignments array
	unsigned numAlignments;
	
	//Summary about alignments between pairs of contigs
	QVector<QStringList> *hspsStats;
		
	//name of the query file
	QString precursorFilename;
	
	//name of the reference file
	QString productFilename;
	
	//arguments for blastn local-alignment heuristic
	QStringList blastnArguments;
	
	//arguments for blat local-alignment heuristic
	QStringList blatArguments;
	
	QMenu *fileMenu;
	QMenu *alignmentMenu;
	QMenu *setPathsMenu;
	
	InitialAligner currentAligner;
	
	QString pullOutFastaSequence(QString filename, QString id);
	
	HSPs *hsps;
};
#endif //STAGR_H
