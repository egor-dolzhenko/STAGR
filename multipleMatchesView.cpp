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
#include "MultipleMatchesView.h"
#include <algorithm>
#include <vector>
#include <QtCore>
//#include <QtSvg>

using namespace std;

MultipleMatchesView::MultipleMatchesView(QWidget* parent, int *array1, int *array2, 
				int *primaryArray, int *matchesSubjectEnd, int queryLength, int subjectLength, 
				int numberOfRelevantRecords, QString *matchesSubjectNames)
	:QGraphicsView(parent)
{
	myQueryStart = array1;
	myQueryEnd = array2;
	mySubjectStart = primaryArray;
	mySubjectEnd = matchesSubjectEnd;
	mySubjectLength = subjectLength;
	myQueryLength = queryLength;
	
	scene = new QGraphicsScene(this);
	setAlignment(Qt::AlignCenter);
	setRenderHints(QPainter::Antialiasing|
				   QPainter::TextAntialiasing);
	setScene(scene);
	
	QSet<QString> setSubjectNames;
	
	for(int i = 0; i < numberOfRelevantRecords; i++)
	{
		setSubjectNames << matchesSubjectNames[i];
	}
		 
	 numberSubjects = setSubjectNames.size();
	 qStartsArray = new vector<int>[numberSubjects];
	 sStartsArray = new vector<int>[numberSubjects];
	 qEndsArray = new vector<int>[numberSubjects];
	 sEndsArray = new vector<int>[numberSubjects];
	 
	 int index = 0;
	 
	 QSetIterator<QString> i(setSubjectNames);
	 while (i.hasNext())
	 {
    	 QString current_subject_name = i.next();
    	 for(int j = 0; j < numberOfRelevantRecords; j++)
    	 {
    	 	if(matchesSubjectNames[j] == current_subject_name)
    	 	{
    	 		qStartsArray[index].push_back(myQueryStart[j]);
    	 		sStartsArray[index].push_back(mySubjectStart[j]);
    	 		qEndsArray[index].push_back(myQueryEnd[j]);
    	 		sEndsArray[index].push_back(mySubjectEnd[j]);
    	 	}
    	 }
    	 
    	 index++;
     }

     
     scale = 3;
	 
}

void MultipleMatchesView::createScene(int width, int height)
{
	//need to add contig names to the parameter list
	for(int i = 0; i < numberSubjects; i++)
	{
    	if(canLinearlyOrder(qStartsArray[i], qEndsArray[i]) && canLinearlyOrder(sStartsArray[i], sEndsArray[i]))
    	{
    		createContigReferenceMap(width, height, qStartsArray[i], sStartsArray[i], qEndsArray[i], sEndsArray[i], (i)*5500, (1 - i % 2)*(-400)); 
    	}
		
	}
	
	/*
	 QSvgGenerator generator;
     generator.setFileName("map.svg");
     generator.setSize(QSize(1500, 500));
     generator.setViewBox(QRect(0, 0, 1500, 500));
     generator.setTitle(tr("STAGR output"));
     generator.setDescription(tr("STAGR output"));
     QPainter painter;
     painter.scale(5,5);
     painter.begin(&generator);
     this->render(&painter);
     painter.end();
     */
}

void MultipleMatchesView::createContigReferenceMap(int width, int height, vector<int> qStarts, vector<int> sStarts, vector<int> qEnds, vector<int> sEnds, int startX, int startY)
{	
	map<int, int> qNext, sNext, qPrev, sPrev; 
	
	vector<int>::iterator it;

	int numberOfRecords = qStarts.size();
	
 	int sep = 240 + startY;
  	
   	int qstart = 0;
	int qend = 0;
	int sstart = 0;
	int send = 0;
	
	//draw the lines between segments
	for(int i = 0; i < numberOfRecords; i++)
	{
   		qstart = qStarts[i]/scale;
		qend = qEnds[i]/scale;
		sstart = sStarts[i]/scale;
		send = sEnds[i]/scale;
		QPainterPath line;
		line.moveTo((qend + qstart)/2, 20);
		line.lineTo(startX + (send + sstart)/2, sep); 
		QGraphicsPathItem *lineItem = new QGraphicsPathItem(line);
		lineItem->setPen(QPen(Qt::DashLine));
		scene->addItem(lineItem);
	}
   	
   	//Assumption: all matches are consequtive
   	sort (qStarts.begin(), qStarts.end());
   	sort (sStarts.begin(), sStarts.end());
   	sort (qEnds.begin(), qEnds.end());
   	sort (sEnds.begin(), sEnds.end());
   	  	
  	//draw the outline
	sstart = sStarts[0]/scale;
	send = sEnds[numberOfRecords - 1]/scale;
	
	QPolygonF spolygon;
	spolygon << QPointF(startX + sstart, 0 + sep);
	spolygon << QPointF(startX + send, 0 + sep);
	spolygon << QPointF(startX + send, 20 + sep);
	spolygon << QPointF(startX + sstart, 20 + sep);
	
	//draw the outline
	qstart = qStarts[0]/scale;
	qend = qEnds[numberOfRecords - 1]/scale;
	
	QPolygonF spolygon2;
	spolygon2 << QPointF(qstart, 0);
	spolygon2 << QPointF(qend, 0);
	spolygon2 << QPointF(qend, 20);
	spolygon2 << QPointF(qstart, 20);
	
	
	QGraphicsPolygonItem *smatch = new QGraphicsPolygonItem(spolygon);
	QGraphicsPolygonItem *smatch2 = new QGraphicsPolygonItem(spolygon2);
	smatch->setBrush(colorForMatchIndex(startX/500));
	smatch2->setBrush(colorForMatchIndex(4));
	
	smatch->setOpacity(0.3);
	smatch2->setOpacity(0.3);
	
	scene->addItem(smatch);
	scene->addItem(smatch2);
		
	//draw the segments
	for(int i = 0; i < numberOfRecords; i++)
	{
		qstart = qStarts[i]/scale;
		qend = qEnds[i]/scale;
		int qforwardOverlapLength = 0;
		int qbackwardOverlapLength = 0;

		sstart = sStarts[i]/scale;
		send = sEnds[i]/scale;
		int sforwardOverlapLength = 0;
		int sbackwardOverlapLength = 0;
	
		if(i != numberOfRecords - 1)
		{
			int qnextstart = qStarts[i+1]/scale;
			int snextstart = sStarts[i+1]/scale;
			qforwardOverlapLength = qend - qnextstart;
			sforwardOverlapLength = send - snextstart;
			if(qforwardOverlapLength < 0) qforwardOverlapLength = 0;
			if(sforwardOverlapLength < 0) sforwardOverlapLength = 0;
		}
		if( i != 0)
		{
			int qprevend = qEnds[i-1]/scale;
			int sprevend = sEnds[i-1]/scale;
			qbackwardOverlapLength = qprevend - qstart;
			sbackwardOverlapLength = sprevend - sstart;
			if(qbackwardOverlapLength < 0) qbackwardOverlapLength = 0;
			if(sbackwardOverlapLength < 0) sbackwardOverlapLength = 0;
		}
		
		QPolygonF qpolygon;
		qpolygon << QPointF(qstart, 0);
		qpolygon << QPointF(qend - qforwardOverlapLength, 0);
		qpolygon << QPointF(qend - qforwardOverlapLength, 10);
		qpolygon << QPointF(qend, 10);
		qpolygon << QPointF(qend, 20);
		qpolygon << QPointF(qstart + qbackwardOverlapLength, 20);
		qpolygon << QPointF(qstart + qbackwardOverlapLength, 10);
		qpolygon << QPointF(qstart, 10);
		
		QGraphicsPolygonItem *qmatch = new QGraphicsPolygonItem(qpolygon);
		qmatch->setPen(Qt::NoPen);
		qmatch->setBrush(colorForMatchIndex(i));
		scene->addItem(qmatch);		

		QPolygonF spolygon;
		spolygon << QPointF(startX + sstart, 0 + sep);
		spolygon << QPointF(startX + send - sforwardOverlapLength, 0 + sep);
		spolygon << QPointF(startX + send - sforwardOverlapLength, 10 + sep);
		spolygon << QPointF(startX + send, 10 + sep);
		spolygon << QPointF(startX + send, 20 + sep);
		spolygon << QPointF(startX + sstart + sbackwardOverlapLength, 20 + sep);
		spolygon << QPointF(startX + sstart + sbackwardOverlapLength, 10 + sep);
		spolygon << QPointF(startX + sstart, 10 + sep);

		QGraphicsPolygonItem *smatch = new QGraphicsPolygonItem(spolygon);
		smatch->setPen(Qt::NoPen);
		smatch->setBrush(colorForMatchIndex(i));
		scene->addItem(smatch);
		
		if(qforwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(qend,0);
			path.lineTo(qend,20);
			QGraphicsPathItem *endLine = new QGraphicsPathItem(path);
			scene->addItem(endLine);
		}
		
		if(qbackwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(qstart,0);
			path.lineTo(qstart,20);
			QGraphicsPathItem *beginLine = new QGraphicsPathItem(path);
			scene->addItem(beginLine);
		}

		if(sforwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(startX + send,0 + sep);
			path.lineTo(startX + send,20 + sep);
			QGraphicsPathItem *endLine = new QGraphicsPathItem(path);
			scene->addItem(endLine);
		}
		
		if(sbackwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(startX + sstart,0 + sep);
			path.lineTo(startX + sstart,20 + sep);
			QGraphicsPathItem *beginLine = new QGraphicsPathItem(path);
			scene->addItem(beginLine);
		}

		
		QPainterPath qTopLine;
		qTopLine.moveTo(qstart,0);
		qTopLine.lineTo(qend - qforwardOverlapLength,0);
		QGraphicsPathItem *qTopLineItem = new QGraphicsPathItem(qTopLine);
		scene->addItem(qTopLineItem);
		
		QPainterPath qBottomLine;
		qBottomLine.moveTo(qstart + qbackwardOverlapLength,20);
		qBottomLine.lineTo(qend,20);
		QGraphicsPathItem *qBottomLineItem = new QGraphicsPathItem(qBottomLine);
		scene->addItem(qBottomLineItem);

		QPainterPath sTopLine;
		sTopLine.moveTo(startX + sstart,0 + sep);
		sTopLine.lineTo(startX + send - sforwardOverlapLength,0 + sep);
		QGraphicsPathItem *sTopLineItem = new QGraphicsPathItem(sTopLine);
		scene->addItem(sTopLineItem);
		
		QPainterPath sBottomLine;
		sBottomLine.moveTo(startX + sstart + sbackwardOverlapLength,20 + sep);
		sBottomLine.lineTo(startX + send, 20 + sep);
		QGraphicsPathItem *sBottomLineItem = new QGraphicsPathItem(sBottomLine);
		scene->addItem(sBottomLineItem);		
	}

}

void MultipleMatchesView::clearScene()
{
	QList<QGraphicsItem *> list = scene->items();
	QList<QGraphicsItem *>::Iterator iterator = list.begin();
	for ( ; iterator != list.end(); ++iterator)
	{
		if( *iterator )
		{
			scene->removeItem(*iterator);
			delete *iterator;
		}
	}
}

void MultipleMatchesView::resizeEvent(QResizeEvent* event)
{
	clearScene();
	createScene(event->size().width()-70, event->size().height() - 150);
	
	QGraphicsView::resizeEvent(event);
}

QColor MultipleMatchesView::colorForMatchIndex(int index)
{
	QColor colors[5];
	colors[0] = QColor(255, 77, 65);
	colors[1] = QColor(242, 147, 31);
	colors[2] = QColor(229, 202, 33);
	colors[3] = QColor(145, 178, 33);
	colors[4] = QColor(30, 140, 101);
	
	return colors[index % 5];
}

void MultipleMatchesView::keyPressEvent(QKeyEvent *event)
{
	
	if( (event->key() == Qt::Key_Equal) && (event->modifiers() == Qt::ControlModifier) ) 
	{ 
	  if( scale > 5) 
	  {
	    scale -= 5; 
	    resizeEvent(&QResizeEvent(size(), size()));
	  }
	}
	if( (event->key() == Qt::Key_Minus) && (event->modifiers() == Qt::ControlModifier) )  
	{
	  if( scale <= 500)
	  {
	    scale += 5; resizeEvent(&QResizeEvent(size(), size())); //qDebug() << nucleotideWidth;
	  }
	}	
}

bool MultipleMatchesView::canLinearlyOrder(vector<int> origPrimaryArray, vector<int> origArray1)
{
	vector<int> primaryArray(origPrimaryArray);
	vector<int> array1(origArray1);
	
	bool change = true;
	unsigned numberSwap;
	QString stringSwap;
	while(change == true)
	{
		change = false;
		for(int i = 0; i < primaryArray.size() - 1; i++)
		{
			if(primaryArray[i] > primaryArray[i+1])
			{
				numberSwap = array1[i];
				array1[i] = array1[i+1];
				array1[i+1] = numberSwap;
				
				numberSwap = primaryArray[i];
				primaryArray[i] = primaryArray[i+1];
				primaryArray[i+1] = numberSwap;
				
				change = true;
			}
		}
	}
	
    for(int j = 0; j < primaryArray.size() - 1; j++)
    {
    	if((primaryArray[j] >= primaryArray[j+1])||(array1[j] >= array1[j+1]))
    	{
    		return false;
    	}
    }

	return true;
}

