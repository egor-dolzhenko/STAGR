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

//Location of the header file for including Python interpreter into STAGR
#include <Python/Python.h>

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
	
	//Opens query file dialog
	void openQueryFileDialog();
	
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
	
	//Open load sequences dialog
	QAction *loadSequencesAction;
	
	//Open STAGR settings dialog
	QAction *stagrSettingsAction;
	
	QAction *runBlastnAction;
	
	QAction *runBlatAction;

	QAction *selectBlastnAction;
	
	QAction *selectBlatAction;

	QAction *filteringAction;

	QActionGroup *alignmentGroup;
	
	QAction *startEditorAction;
		
	//Dialog containing match information for a particular pair of contigs
	//MatchesDialog *matchesDialog;
	
	//Dialog containing summary information about matches corresponding to
	//a particular query contig and multiple reference contigs
	MultipleMatchesDialog *multipleMatchesDialog;
	
	//Dialog containing blastn settings
	BlastnSettingsDialog* blastnSettingsDialog;
	
	//Dialog containing blat settings
	BlatSettingsDialog* blatSettingsDialog;
	
	ScriptEditDialog* scriptEditDialog;
	
	//Contains information about alignments found by blast
	QStringList* alignments;
	
	//Number of elements in the alignments array
	unsigned numAlignments;
	
	//Summary about alignments between pairs of contigs
	QStringList* alignmentsSummary;
	
	//Number of elements in alignmentsSummary array
	unsigned numAlignmentsSummary;
	
	//Lengths of query contigs
	QMap <QString, unsigned> queryLengths;
	
	//Lengths of matches contigs
	QMap <QString, unsigned> referenceLengths;
	
	//name of the query file
	QString filenameQueryFile;
	
	//name of the reference file
	QString filenameReferenceFile;
	
	//arguments for blastn local-alignment heuristic
	QStringList blastnArguments;
	
	//arguments for blat local-alignment heuristic
	QStringList blatArguments;
	
	QMenu *fileMenu;
	QMenu *alignmentMenu;
	
	InitialAligner currentAligner;
	
	QVector< QMap<QString,QString> > *filteredAlignments;
	
	QString pullOutFastaSequence(QString filename, QString id);
};
#endif //STAGR_H