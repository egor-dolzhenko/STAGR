#ifndef MULTIPLEMATCHESDIALOG_H
#define MULTIPLEMATCHESDIALOG_H
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

#include <QDialog>
#include "Table.h"
#include "sequenceView.h"
#include "multipleMatchesView.h"
#include "hsp.h"
#include "plotLayer.h"

enum recordType {qseqid, sseqid, pident, length, MISMATCH, gapopen, 
				 qstart, qend, sstart, send, evalue, bitscore};
				 
class QTabWidget;

class MultipleMatchesDialog : public QDialog
{
	Q_OBJECT

public:
	MultipleMatchesDialog(QWidget *parent, HSPs *hsps, QSet<QString> precursorIds, 
						  QSet<QString> productIds, QString precursorSequence, 
						  QString productSequence
						  );
	~MultipleMatchesDialog();
private:
	QTabWidget *mainTab;
	Table *summaryTable;
	SequenceView *sequenceView;
	SequenceView *subjectView;
	MultipleMatchesView *multipleMatchesView;
	HSPs *newHsps;
	HspLoci *precursorLoci;
	HspLoci *productLoci;
};

#endif //MULTIPLEMATCHESDIALOG_H