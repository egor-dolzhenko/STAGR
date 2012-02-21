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
#include <QGraphicsScene>
#include <QGraphicsView>
#include "MultipleMatchesDialog.h"
#include "plotLayer.h"
#include "chordDiagram.h"


MultipleMatchesDialog::MultipleMatchesDialog(QWidget *parent, HSPs *hsps, QString queryName, QSet<QString> subjectNames,
							 QString querySequence, QString subjectSequence, QVector< QMap<QString,QString> > *filteredAlignments//,
							 //int numberOfRelevantRecords, 
							 //int queryLength, int subjectLength
							 ) //, QString filenameQueryFile, QString filenameReferenceFile
	:QDialog(parent)
{

	QSet<QString> precursorNames;
	precursorNames.insert(queryName);
	//QStringList productNames;

	//qDebug() << "creating hsps";	
	newHsps = new HSPs(hsps, precursorNames, subjectNames);
	precursorLoci = new HspLoci(newHsps, "qstart", "qend", "qseqid");
	productLoci = new HspLoci(newHsps, "sstart", "send", "sseqid");
	
	//qDebug() << "printing table";
	//newHsps->printTable();
	//qDebug() << "done";
	alignmentsPairContigs = new QVector< QMap<QString,QString> >(0);
	alignmentsDirection = new QVector<Direction>(0);
	
	QString qseqidValue("");
	QString sseqidValue("");
	for(unsigned i = 0; i < filteredAlignments->size(); ++i)
	{ 
		qseqidValue = filteredAlignments->at(i)["qseqid"];
		sseqidValue = filteredAlignments->at(i)["sseqid"];
		if( (qseqidValue == queryName) && (subjectNames.contains(sseqidValue)) )
		{
			
			unsigned qstartValue = filteredAlignments->at(i)["qstart"].toInt();
			unsigned qendValue = filteredAlignments->at(i)["qend"].toInt();
			unsigned sstartValue = filteredAlignments->at(i)["sstart"].toInt();
			unsigned sendValue = filteredAlignments->at(i)["send"].toInt();
			QString qendValueString(qendValue);
			const QString qstartValueString(qstartValue);
			if(qstartValue > qendValue)
			{
				(*filteredAlignments)[i].insert("qstart", QString::number(qendValue));
				(*filteredAlignments)[i].insert("qend", QString::number(qstartValue));
				alignmentsDirection->append(LEFT);
			}
			else if(sstartValue > sendValue)
			{
				(*filteredAlignments)[i].insert("sstart", QString::number(sendValue));
				(*filteredAlignments)[i].insert("send", QString::number(sstartValue));
				alignmentsDirection->append(LEFT);
			}
			else
			{
				alignmentsDirection->append(RIGHT);
			}

			alignmentsPairContigs->append(filteredAlignments->at(i)); //QMap<QString,QString>()
		}
	}	
	
	//QStringList *header;
	//header = filteredAlignments->at(0).keys();
	
	//header = newHsps.getKeys();
	
	//header << "qseqid" << "sseqid" << "pident" << "length" << "mismatch" << "gapopen" 
	//	   << "qstart" << "qend"   << "sstart" << "send"   << "evalue"   << "bitscore";
	
	//tableWithRelevantMatches = new Table(NULL, header, alignmentsPairContigs);
	newHsps->printTable();
	tableWithRelevantMatches = new Table(NULL, newHsps);
	newHsps->printTable();
	mainTab = new QTabWidget(this);
	
	mainTab->addTab(tableWithRelevantMatches, "Summary");
	
	//====================================================
	unsigned numAlignments = alignmentsPairContigs->size();
	matchesStart = new int[numAlignments];
	matchesEnd = new int[numAlignments];
	matchesSubjectStart = new int[numAlignments];
	matchesSubjectEnd = new int[numAlignments];
	matchesSubjectNames = new QString[numAlignments];
	
	unsigned newStart = smallestValue("qstart") - 1; //
	unsigned newStartReference = smallestValue("sstart") - 1;
	
	//qDebug() << newStart << largestValue("qend"); 
	//qDebug() << newHsps->minUpstreamPrecursor << newHsps->maxDownstreamPrecursor;
	
	//qDebug() << newStartReference << largestValue("send"); 
	//qDebug() << newHsps->minUpstreamProduct << newHsps->maxDownstreamProduct;
	
	
	for(unsigned i = 0; i < alignmentsPairContigs->size(); ++i)
	{
		matchesStart[i] = alignmentsPairContigs->at(i)["qstart"].toInt() - newStart;
		matchesEnd[i] = alignmentsPairContigs->at(i)["qend"].toInt() - newStart;
		matchesSubjectStart[i] = alignmentsPairContigs->at(i)["sstart"].toInt() - newStartReference;
		matchesSubjectEnd[i] = alignmentsPairContigs->at(i)["send"].toInt() - newStartReference;
		matchesSubjectNames[i] = alignmentsPairContigs->at(i)["sseqid"];
	}
	
	//==================================================
	
	bubbleSortArraysByQuery();
	
	sequenceView = new SequenceView(NULL, precursorLoci, querySequence, largestValue("qend") - newStart//, numAlignments, //queryLength
									//matchesStart, matchesEnd, matchesSubjectNames, alignmentsDirection
									);
	mainTab->addTab(sequenceView, "Query");

	bool moreThanOne = false;
	for(unsigned i = 0; i < alignmentsPairContigs->size(); i++)
	{
		if(alignmentsPairContigs->at(i)["sseqid"] != alignmentsPairContigs->at(0)["sseqid"])
		{
			moreThanOne = true;
			break;
		}
	}
	
	if(!moreThanOne)
	{
		bubbleSortArraysByReference();
		subjectView = new SequenceView(NULL, productLoci, subjectSequence, largestValue("send") - newStartReference//, numAlignments, //subjectLength
								   		//matchesSubjectStart, matchesSubjectEnd, matchesSubjectNames, alignmentsDirection
								   		);
		mainTab->addTab(subjectView, "Subject");
		
	}
	
	ChordDiagram *chordDiagram = new ChordDiagram(NULL, precursorLoci, productLoci);
	//chordDiagram->show();
	
	//multipleMatchesView = new MultipleMatchesView(NULL, precursorLoci, productLoci, matchesStart, matchesEnd, matchesSubjectStart,
	//						 matchesSubjectEnd, //queryLength, subjectLength, 
	//						 numAlignments, matchesSubjectNames); 
	//
	//mainTab->addTab(multipleMatchesView, "Match map");
	
	mainTab->addTab(chordDiagram, "Chord Diagram");
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mainTab);
	setLayout(mainLayout);
	
	
	
}

MultipleMatchesDialog::~MultipleMatchesDialog()
{
	//delete tableWithRelevantMatches;
	//delete[] matchesStart;
	//delete[] matchesEnd;
	//delete[] matchesSubjectStart;
	//delete[] matchesSubjectEnd;
	//delete sequenceView;
	//delete multipleMatchesView;
	//delete alignmentsPairContigs;
}

// void MultipleMatchesDialog::bubbleSortQuerySubjectRecordsByQuery()
// {
// 	bool change = true;
// 	QStringList stringList;
// 	while(change == true)
// 	{
// 		change = false;
// 		for(int i = 0; i < myNumberOfRelevantRecords - 1; i++)
// 		{
// 			if(querySubjectRecords[i][qstart].toInt() > querySubjectRecords[i+1][qstart].toInt())
// 			{
// 				stringList = querySubjectRecords[i];
// 				querySubjectRecords[i] = querySubjectRecords[i+1];
// 				querySubjectRecords[i+1] = stringList;
// 				change = true;
// 			}
// 		}
// 	}
// }

// void MultipleMatchesDialog::bubbleSortQuerySubjectRecordsBySubject()
// {
// 	bool change = true;
// 	QStringList stringList;
// 	while(change == true)
// 	{
// 		change = false;
// 		for(int i = 0; i < myNumberOfRelevantRecords - 1; i++)
// 		{
// 			if(querySubjectRecords[i][sstart].toInt() > querySubjectRecords[i+1][sstart].toInt())
// 			{
// 				stringList = querySubjectRecords[i];
// 				querySubjectRecords[i] = querySubjectRecords[i+1];
// 				querySubjectRecords[i+1] = stringList;
// 				change = true;
// 			}
// 		}
// 	}
// }


// int MultipleMatchesDialog::smallestValueOfParameter(recordType param)
// {
// 	int minValue = querySubjectRecords[0][param].toInt();
// 	for(int i = 0; i < myNumberOfRelevantRecords; i++)
// 	{
// 		if(querySubjectRecords[i][param].toInt() < minValue)
// 		{
// 			minValue = querySubjectRecords[i][param].toInt();
// 		}
// 	}
// 	
// 	return minValue;
// }
// 
// int MultipleMatchesDialog::largestValueOfParameter(recordType param)
// {
// 	int maxValue = querySubjectRecords[0][param].toInt();
// 	for(int i = 0; i < myNumberOfRelevantRecords; i++)
// 	{
// 		if(querySubjectRecords[i][param].toInt() > maxValue)
// 		{
// 			maxValue = querySubjectRecords[i][param].toInt();
// 		}
// 	}
// 	
// 	return maxValue;
// }

unsigned MultipleMatchesDialog::smallestValue(QString id)
{
	unsigned minValue = alignmentsPairContigs->at(0)[id].toInt();
	for(unsigned i = 0; i < alignmentsPairContigs->size(); ++i)
	{
		unsigned currentValue = alignmentsPairContigs->at(i)[id].toInt();
		if(currentValue < minValue)
		{
			minValue = currentValue;
		}
	}
	
	return minValue;
}

unsigned MultipleMatchesDialog::largestValue(QString id)
{
	unsigned maxValue = alignmentsPairContigs->at(0)[id].toInt();
	for(unsigned i = 0; i < alignmentsPairContigs->size(); ++i)
	{
		unsigned currentValue = alignmentsPairContigs->at(i)[id].toInt();
		if(currentValue > maxValue)
		{
			maxValue = currentValue;
		}
	}
	
	return maxValue;

}

void MultipleMatchesDialog::bubbleSortArraysByQuery()
{
	bool change = true;
	unsigned numberSwap;
	QString stringSwap;
	while(change == true)
	{
		change = false;
		for(int i = 0; i < alignmentsPairContigs->size() - 1; i++)
		{
			if(matchesStart[i] > matchesStart[i+1])
			{
				numberSwap = matchesStart[i];
				matchesStart[i] = matchesStart[i+1];
				matchesStart[i+1] = numberSwap;
				
				numberSwap = matchesEnd[i];
				matchesEnd[i] = matchesEnd[i+1];
				matchesEnd[i+1] = numberSwap;
				
				numberSwap = matchesSubjectStart[i];
				matchesSubjectStart[i] = matchesSubjectStart[i+1];
				matchesSubjectStart[i+1] = numberSwap;
				
				numberSwap = matchesSubjectEnd[i];
				matchesSubjectEnd[i] = matchesSubjectEnd[i+1];
				matchesSubjectEnd[i+1] = numberSwap;
				
				
				stringSwap = matchesSubjectNames[i];
				matchesSubjectNames[i] = matchesSubjectNames[i+1];
				matchesSubjectNames[i+1] = stringSwap;
				change = true;
			}
		}
	}
}

void MultipleMatchesDialog::bubbleSortArraysByReference()
{
	bool change = true;
	unsigned numberSwap;
	QString stringSwap;
	while(change == true)
	{
		change = false;
		for(int i = 0; i < alignmentsPairContigs->size() - 1; i++)
		{
			if(matchesSubjectStart[i] > matchesSubjectStart[i+1])
			{
				numberSwap = matchesStart[i];
				matchesStart[i] = matchesStart[i+1];
				matchesStart[i+1] = numberSwap;
				
				numberSwap = matchesEnd[i];
				matchesEnd[i] = matchesEnd[i+1];
				matchesEnd[i+1] = numberSwap;
				
				numberSwap = matchesSubjectStart[i];
				matchesSubjectStart[i] = matchesSubjectStart[i+1];
				matchesSubjectStart[i+1] = numberSwap;
				
				numberSwap = matchesSubjectEnd[i];
				matchesSubjectEnd[i] = matchesSubjectEnd[i+1];
				matchesSubjectEnd[i+1] = numberSwap;
				
				stringSwap = matchesSubjectNames[i];
				matchesSubjectNames[i] = matchesSubjectNames[i+1];
				matchesSubjectNames[i+1] = stringSwap;
				change = true;
			}
		}
	}
}

QString MultipleMatchesDialog::pullOutFastaSequence(QString filename, QString id)
{
	QFile fastaFile(filename);
	QTextStream stream(&fastaFile);
	
	if(!fastaFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "error opening file";
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

