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

#ifndef SEQUENCEVIEW_H
#define SEQUENCEVIEW_H

#include <QGraphicsView>
#include "block.h"

class QWidget;
class QGraphicsScene;
class QString;
class QFont;

enum Direction {LEFT, RIGHT};

class SequenceView : public QGraphicsView
{
	Q_OBJECT
	
	
public:
	SequenceView(QWidget* parent, QString newSequence, int newSequenceLength, int newnumberAlignments, 
				 int* newMatchesStart, int* newMatchesEnd, QString *annotation, QVector<Direction> *newAlignmentDirection);
	
protected:
	virtual void resizeEvent(QResizeEvent* event);
	void keyPressEvent(QKeyEvent *event);

private slots:
	void timerSlot();

private:
	QGraphicsScene *scene;
	void createScene(int width, int height);
	void clearScene();
	int sequenceLength;
	int numberAlignments;
	int* matchesStart;
	int* matchesEnd;
	QColor colorForMatchIndex(int index);
	QString *matchNames;
	void Annotate(int x, int y, int width, int height, int matchIndex);
	QFont setFontSize(int pixelsPerNucleotide, int nucleotidesPerRow, QString firstRow, QFont font);
	QString sequence;
	QTimer *timer;
	int windowHeight;
	int windowWidth;
	bool showNucleotides;
	int timerIterations;
	int nucleotideWidth;
	bool alwaysShowNucleotides;
	QVector<Direction> *alignmentsDirection;
};

#endif //of SEQUENCEVIEW_H