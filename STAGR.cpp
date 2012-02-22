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
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "STAGR.h"

//Constructor
StagrMainWindow::StagrMainWindow(QWidget *parent)
	   :QMainWindow(parent)
{

	hsps = NULL;
	hspsStats = NULL;

	multipleMatchesDialog = NULL;

	//Creates main toolbar and initializes it with actions
	createToolBar();
	createMenus();
	
	mainTabWidget = new QTabWidget;
	numAlignments = 0;
	
	//The default filenames
	precursorFilename = "MIC.fasta";
	productFilename = "MAC.fasta";

	querySequenceInformationLayout = new QHBoxLayout;
	querySequenceLabel = new QLabel("File with query sequences:");
	querySequenceFilenameLabel = new QLabel(precursorFilename); 
	querySequenceInformationLayout->addWidget(querySequenceLabel);
	querySequenceInformationLayout->addWidget(querySequenceFilenameLabel);
	
	
	referenceSequenceInformationLayout = new QHBoxLayout;
	referenceSequenceLabel = new QLabel("File with reference sequences:");
	referenceSequenceFilenameLabel = new QLabel(productFilename);
	referenceSequenceInformationLayout = new QHBoxLayout;
	referenceSequenceInformationLayout->addWidget(referenceSequenceLabel);
	referenceSequenceInformationLayout->addWidget(referenceSequenceFilenameLabel);
	
	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(querySequenceInformationLayout);
	mainLayout->addLayout(referenceSequenceInformationLayout);
	mainLayout->addWidget(mainTabWidget);
	setCentralWidget(new QWidget);
	centralWidget()->setLayout(mainLayout);
	
	//create blastn settings dialog (modal)
	blastnSettingsDialog = new BlastnSettingsDialog(this);
	blatSettingsDialog = new BlatSettingsDialog(this);
	scriptEditDialog = new ScriptEditDialog(this);

	runBlastnAction = new QAction(this);
	runBlatAction = new QAction(this);

	//blast is used by default
	currentAligner = BLASTN;
	
	//table for storing the alignment summary
	table = NULL;
	
	connect(settingsAction, SIGNAL(triggered()), this, 
			SLOT(openSettingsDialog()));
				
	//blastn is the default local alignment algorithm
	connect(startAction, SIGNAL(triggered()), this,
			SLOT(runStagr()));
	
	connect(stagrSettingsAction, SIGNAL(triggered()), this,
			SLOT(openMDialogMultipleMatches()));
				
	connect(startEditorAction, SIGNAL(triggered()), this,
			SLOT(openScriptEditor()));
}

//Creates main toolbar and initializes it with actions
void StagrMainWindow::createToolBar()
{
	startAction = new QAction("Start", this);
	settingsAction = new QAction("Blastn settings", this);
	//loadSequencesAction = new QAction("Load sequences", this);
	stagrSettingsAction = new QAction("STAGR settings", this);
	filteringAction = new QAction("Filtering Script",this);
	startEditorAction = new QAction("Script Editor", this);
	startAction->setIcon(QIcon("icons/startIcon.png"));
	settingsAction->setIcon(QIcon("icons/settingsIcon.png"));
	//loadSequencesAction->setIcon(QIcon("icons/loadSequencesIcon.png"));
	startEditorAction->setIcon(QIcon("icons/pythonIcon.png"));
	stagrSettingsAction->setIcon(QIcon("icons/stagrSettingsIcon.png"));
	toolBar = addToolBar("mainToolBar");
	//toolBar->addAction(loadSequencesAction);
	toolBar->addAction(startAction);
	toolBar->addAction(settingsAction);
	toolBar->addAction(startEditorAction);
	toolBar->addAction(stagrSettingsAction);
}

//Run blastn and initialize alignments and numAlignments
//with alignments discovered by blastn
QString StagrMainWindow::runBlastn(QString queryFilename, QString referenceFilename)
{
	QProcess *blastn = new QProcess(this);
	//QStringList arguments;
	
	blastnArguments = blastnSettingsDialog->blastSettingsPatrameterString(queryFilename, referenceFilename);
	
	QString result = "";
	blastn->start("blastn", blastnArguments);
	blastn->waitForFinished(-1);
	result = blastn->readAll();
	return result;
}

QString StagrMainWindow::runBlat(QString queryFilename, QString referenceFilename)
{
	QProcess *blat = new QProcess(this);
	blatArguments = blatSettingsDialog->blatSettingsPatrameterString(queryFilename, referenceFilename);
	QString result = "";
	blat->start("blat", blatArguments);
	blat->waitForFinished(-1);
	
	QFile file("out");
	
	if(!file.exists())
	{
		alert("error: the file with blat output is missing");
		return "";
	}
	
	if(!file.open( QIODevice::ReadOnly | QIODevice::Text ))
	{
		alert("error: couldn't open the file with blat output");
		return "";
	}
	
	QTextStream blatOutputStream( &file );
	result = blatOutputStream.readAll();
	QFile::remove("out");
	return result;
}

void StagrMainWindow::alert(QString text)
{
	QMessageBox msgBox;
 	msgBox.setText(text);
 	msgBox.exec();
}

bool StagrMainWindow::runFilteringAlgorithm(QString input, QString algorithmFilename)
{
	//initialize Python interpreter
	Py_Initialize();
		
	PyObject *argument = PyString_FromString( input.toStdString().c_str() );
	PyObject *list;
	PyObject *output;
	
	list = NULL;
	
	QString aligner;
	switch(currentAligner)
	{
		case BLASTN:
			aligner = "blastn";
			break;
		case BLAT:
			aligner = "blat";
			break;
	}
	list = runPythonFunction(QString("output2dict.py"), aligner, argument);
	
	if(list == NULL)
	{
		alert("Couldn't convert local-alignment results to a list");
		return false;
	}
	
	output = runPythonFunction(QString("script.py"), QString("annotate"), list); // algorithmFilename
	
	if( hsps == NULL ) delete hsps;
	
	hsps = new HSPs;
	QString loadStatus = hsps->loadData(output);
	if( loadStatus != "" )
	{
		alert(loadStatus);
		return false;
	}
	
	if(output == NULL)
	{
		alert("Couldn't run the annotation script");
		return false;
	}
	
	PyObject *key, *value;
	filteredAlignments = new QVector< QMap<QString,QString> >(0);
	if( PyList_Size(output) < 1 )
	{
		alert("The annotation script did not return any relevant data");
		return false;
	}
	for( unsigned i = 0; i < PyList_Size(output); ++i)
	{
		PyObject *dictionary = PyList_GetItem(output, i);
		
		Py_ssize_t pos = 0;
		QMap<QString, QString> filteredAlignment;
		
		
		while (PyDict_Next(dictionary, &pos, &key, &value))
		{
			if(!PyString_Check(key))
			{
				alert("error: key is not a string");
				return false;
			}
			
			if(PyInt_Check(value))
			{
				filteredAlignment[PyString_AsString(key)] = QString::number(PyInt_AsLong(value));
			}
			else if(PyFloat_Check(value))
			{
				filteredAlignment[QString(PyString_AsString(key))] = QString::number(PyFloat_AsDouble(value));
			}
			else if(PyString_Check(value))
			{
				filteredAlignment[PyString_AsString(key)] = QString(PyString_AsString(value));
			}
			else
			{
				alert("conversion error: expected int, float, or string");
				return false;
			}
		
		}
		filteredAlignments->append(filteredAlignment);
	}
	numAlignments = PyList_Size(output);
	
	PyErr_Clear();
 	Py_Finalize();
 	return true;
}

bool StagrMainWindow::runStagr()
{
	QString result("");
	
	switch(currentAligner)
	{
		case BLASTN:
			result = runBlastn(precursorFilename, productFilename);
			break;
		case BLAT:
			result = runBlat(precursorFilename, productFilename);
			break;
	}
	
	QFile file("script.py");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << scriptEditDialog->getScript();
    file.close();
    
	if(runFilteringAlgorithm(result, "annotate.py") == NULL) return false;

	createTable();
	return true;
}

PyObject *StagrMainWindow::runPythonFunction(QString filename, QString functionname, PyObject *argument)
{

	PyObject *pValue;
 	
	//redirect output to file (simplify)
 	
 	PyRun_SimpleString("import sys");
 	//PyRun_SimpleString("sys.stdout = open('python_out.log','w')");
 



	//Get a reference to the main module.
 	PyObject* mainModule = PyImport_AddModule("__main__");
 	char const* redirectErrorOutput = "class StdoutCatcher:\n  def __init__(self):\n    self.data = ''\n  def write(self, stuff):\n   self.data = self.data + stuff\ncatcher = StdoutCatcher()\nsys.stderr = catcher";
 	PyRun_SimpleString(redirectErrorOutput);
 	
	//Get the main module's dictionary and make a copy of it.
 	PyObject* mainDict = PyModule_GetDict(mainModule);
 	PyObject* mainDictCopy = PyDict_Copy(mainDict);
 	
	//Execute two different files of
  	//Python code in separate environments
 	FILE* file_1 = fopen(filename.toStdString().c_str(), "r");
 	PyRun_File(file_1, filename.toStdString().c_str(), Py_file_input, mainDict, mainDict);
 	
 	PyObject *pFunc = PyDict_GetItemString(mainDict, functionname.toStdString().c_str());
 	
 	if (PyCallable_Check(pFunc)) 
     {
     	PyObject *pArgs = PyTuple_New(1);
     	PyTuple_SetItem(pArgs, 0, argument);
       	pValue = PyObject_CallObject(pFunc, pArgs);//argument
     }
     else 
     {
        PyErr_Print();
		PyObject* catcher = PyObject_GetAttrString(mainModule, "catcher");
		PyObject* output = PyObject_GetAttrString(catcher, "data");
    	alert(PyString_AsString(output));
 
        return NULL;
     }
 	
        
 	return pValue;
}

void StagrMainWindow::openSettingsDialog()
{
	switch(currentAligner)
	{
		case BLASTN:
			openBlastnSettingsDialog();
			break;
		case BLAT:
			openBlatSettingsDialog();
			break;
	}
}

void StagrMainWindow::openMDialogMultipleMatches()
{
	//table
	const QModelIndexList list = table->selectionModel()->selectedRows();
	if( list.count() == 0 )
		return;
		
	QString precursorId = "";
	QString productId = "";
	
	QSet<QString> precursorIds;
	QSet<QString> productIds;
	
	for (unsigned i = 0; i < list.count(); i++)
	{
		QModelIndex index = list.at(i);
		unsigned row = index.row();
		precursorIds.insert(hspsStats->at(row)[qseqid]);
		productIds.insert(hspsStats->at(row)[sseqid]);
	}
	
	if( precursorIds.size() == 1 ) precursorId = precursorIds.toList()[0];
	if( productIds.size() == 1 ) productId = productIds.toList()[0]; 
	
	if(multipleMatchesDialog != NULL)
		delete multipleMatchesDialog;
	multipleMatchesDialog = new MultipleMatchesDialog(this, hsps, precursorIds, productIds,
													  pullOutFastaSequence(precursorFilename, precursorId), 
													  pullOutFastaSequence(productFilename, productId),  
													  filteredAlignments);
													  
	multipleMatchesDialog->show();
	multipleMatchesDialog->raise();
	multipleMatchesDialog->activateWindow();
}

void StagrMainWindow::openBlastnSettingsDialog()
{
	blastnSettingsDialog->exec();
}

void StagrMainWindow::openBlatSettingsDialog()
{
	blatSettingsDialog->exec();
}

void StagrMainWindow::openScriptEditor()
{
	scriptEditDialog->exec();
}

void StagrMainWindow::getAlignmentsSummary()
{

	if( hspsStats != NULL) delete hspsStats;
	hspsStats = new QVector<QStringList>;

	QString precursorId;
	QString productId;
	
	QSet<QString> *precursorIds = hsps->getAllValues("qseqid");
	QSet<QString> *productIds = hsps->getAllValues("sseqid");
	
	QSetIterator<QString> precursorIdIterator(*precursorIds);
	
	while(precursorIdIterator.hasNext())
	{
		precursorId = precursorIdIterator.next();
		
		QSetIterator<QString> productIdIterator(*productIds);
		
		while(productIdIterator.hasNext())
		{
			productId = productIdIterator.next();
			
			unsigned numHSPs = hsps->numHSPs(precursorId, productId);
						
			if( numHSPs != 0 )
			{
				float aveLength = hsps->getAverage(precursorId, productId, "length");
				float aveGaps = hsps->getAverage(precursorId, productId, "gapopen");
				float aveMismatch = hsps->getAverage(precursorId, productId, "mismatch");
				
				QStringList stats;
				stats << precursorId << productId << QString::number(numHSPs) << QString::number(aveLength, 'f', 1) 
					  << QString::number(aveMismatch, 'f', 1) << QString::number(aveGaps, 'f', 1);
				hspsStats->append(stats);
			}
			
		}
		
	}
}

void StagrMainWindow::getPrecursorFilename()
{
	precursorFilename = QFileDialog::getOpenFileName(this, "Specify file with precursor contigs", QDir::currentPath(), "FASTA files (*.fa *.fasta);;All files (*.*)");
    if( !precursorFilename.isNull() ) querySequenceFilenameLabel->setText(precursorFilename.toAscii()); 
}

void StagrMainWindow::getProductFilename()
{
 	productFilename = QFileDialog::getOpenFileName(this, "Specify file with product contigs", QDir::currentPath(), "FASTA files (*.fa *.fasta);;All files (*.*)" );
    if( !productFilename.isNull() ) referenceSequenceFilenameLabel->setText(productFilename.toAscii());
}

void StagrMainWindow::createTable()
{
	
	getAlignmentsSummary();
	
	if(mainTabWidget != NULL)
	{
		mainLayout->removeWidget(mainTabWidget);
		delete mainTabWidget;
		mainTabWidget = NULL;
	}
	else
	{
		mainLayout->removeWidget(table);
		delete table;
		table = NULL;
	}
	
	QStringList header;
	header << "Precursor" << "Product" << "Number of HSPs" << "Ave. Length" << "Ave. Mismatch" << "Ave. Gap";
	table = new Table(NULL, header, hspsStats);
		
	table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	mainLayout->addWidget(table);
	
	connect(table, SIGNAL(doubleClicked(QModelIndex)), this,
			SLOT(openMDialogMultipleMatches())); 

}

void StagrMainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu("File");
	alignmentMenu = menuBar()->addMenu("Alignment");
	
	getPrecursorFilenameAction = new QAction("Load Precursor Contigs", this);
	getProductFilenameAction = new QAction("Load Product Contigs", this);
	selectBlastnAction = new QAction("Blastn", this);
	selectBlastnAction->setCheckable(true);
	selectBlatAction = new QAction("Blat", this);
	selectBlatAction->setCheckable(true);
	
	connect(getPrecursorFilenameAction, SIGNAL(triggered()), this,
			SLOT(getPrecursorFilename()));

	connect(getProductFilenameAction, SIGNAL(triggered()), this,
			SLOT(getProductFilename()));
	
	connect(selectBlastnAction, SIGNAL(triggered()), this,
			SLOT(selectBlastn()));

	connect(selectBlatAction, SIGNAL(triggered()), this,
			SLOT(selectBlat()));

	fileMenu->addAction(getPrecursorFilenameAction);
	fileMenu->addAction(getProductFilenameAction);	
	
	alignmentGroup = new QActionGroup(this);
	
	alignmentGroup->addAction(selectBlastnAction);
	alignmentGroup->addAction(selectBlatAction);
	
	selectBlastnAction->setChecked(true);
	
	alignmentMenu->addAction(selectBlastnAction);
	alignmentMenu->addAction(selectBlatAction);
}

void StagrMainWindow::selectBlastn()
{
	currentAligner = BLASTN;
}

void StagrMainWindow::selectBlat()
{
	currentAligner = BLAT;
}

QString StagrMainWindow::pullOutFastaSequence(QString filename, QString id)
{
	QFile fastaFile(filename);
	QTextStream stream(&fastaFile);
	
	if(!fastaFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		 alert("error opening file");
		 return "";
	}
	
	QString line("");
	QString sequence("");
	bool foundId = false;
	while( !stream.atEnd() )
	{
		line = stream.readLine();
		if( (foundId == true) && (line[0] == '>'))
		{
			return sequence;
		}
		if(foundId == true) 
		{
			sequence = sequence + line;
		}
		if(line == ">" + id) foundId = true;
	}
	fastaFile.close();
	return sequence;
}