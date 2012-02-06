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

#ifndef MATCHESVIEW_H
#define MATCHESVIEW_H

#include <QGraphicsView>

class QGraphicsScene;

class MatchesView : public QGraphicsView
{
	Q_OBJECT
	
public: 
	MatchesView(QWidget* parent, int *matchesStart, int *matchesEnd, 
				int *matchesSubjectStart, int *matchesSubjectEnd, 
				int queryLength, int subjectLength, int numberOfRelevantRecords);
	
protected:
	virtual void resizeEvent(QResizeEvent* event);

private:
	QGraphicsScene *scene;
	void createScene(int width, int height);
	void clearScene();
	int numberOfRecords;
	int *myQueryStart;
	int *myQueryEnd;
	int *mySubjectStart;
	int *mySubjectEnd;
	int mySubjectLength;
	int myQueryLength;
	QColor colorForMatchIndex(int index);
};
	


#endif //MATCHESVIEW_H