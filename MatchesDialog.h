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

#ifndef MATCHESDIALOG_H
#define MATCHESDIALOG_H

#include <QDialog>
#include "Table.h"
#include "sequenceView.h"
#include "matchesView.h"

enum recordType {qseqid, sseqid, pident, length, MISMATCH, gapopen, 
				 qstart, qend, sstart, send, evalue, bitscore};


class QTabWidget;

class MatchesDialog : public QDialog
{
	Q_OBJECT
	
public:
	MatchesDialog(QWidget *parent, QString queryName, QString subjectName,
				  QString querySequence, QString subjectSequence,
				  QStringList *records, int numberOfRecords,
				  int numberOfRelevantRecords, int queryLength, int subjectLength);
private:
	QTabWidget *mainTab;
	QStringList* querySubjectRecords;
	int numberOfQuerySubjectRecords;
	Table *tableWithRelevantMatches;
	int *matchesStart;
	int *matchesEnd;
	int *matchesSubjectStart;
	int *matchesSubjectEnd;
	int *matchesStartSubject;
	int *matchesEndSubject;
	int *matchesSubjectStartSubject;
	int *matchesSubjectEndSubject;
	SequenceView *sequenceView;
	SequenceView *subjectView;
	MatchesView *matchesView;
	int myNumberOfRelevantRecords;
	void bubbleSortQuerySubjectRecordsByQuery();
	void bubbleSortQuerySubjectRecordsBySubject();
	int smallestValueOfParameter(recordType param);
	int largestValueOfParameter(recordType param);

};

#endif //MATCHESDIALOG_H