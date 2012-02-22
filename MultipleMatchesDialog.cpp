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


MultipleMatchesDialog::MultipleMatchesDialog(QWidget *parent, HSPs *hsps, QSet<QString> precursorIds, QSet<QString> productIds,
							 QString precursorSequence, QString productSequence, QVector< QMap<QString,QString> > *filteredAlignments)
	:QDialog(parent)
{

	newHsps = new HSPs(hsps, precursorIds, productIds);
	precursorLoci = new HspLoci(newHsps, "qstart", "qend", "sseqid");
	productLoci = new HspLoci(newHsps, "sstart", "send", "qseqid");
	
	alignmentsPairContigs = new QVector< QMap<QString,QString> >(0);
	alignmentsDirection = new QVector<Direction>(0);
	
	newHsps->printTable();
	tableWithRelevantMatches = new Table(NULL, newHsps);
	newHsps->printTable();
	mainTab = new QTabWidget(this);
	
	mainTab->addTab(tableWithRelevantMatches, "Summary");
	
	if(precursorSequence != "")
	{
		sequenceView = new SequenceView(NULL, precursorLoci, precursorSequence);
		mainTab->addTab(sequenceView, "Query");
	}
	
	if(productSequence != "")
	{
		subjectView = new SequenceView(NULL, productLoci, productSequence);
		mainTab->addTab(subjectView, "Subject");
	}
	
	ChordDiagram *chordDiagram = new ChordDiagram(NULL, precursorLoci, productLoci);
	
	mainTab->addTab(chordDiagram, "Chord Diagram");
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mainTab);
	setLayout(mainLayout);	
}

MultipleMatchesDialog::~MultipleMatchesDialog()
{

}