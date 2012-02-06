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
#include "matchesView.h"
#include <algorithm>
#include <vector>

using namespace std;

MatchesView::MatchesView(QWidget* parent, int *matchesStart, int *matchesEnd, 
				int *matchesSubjectStart, int *matchesSubjectEnd, 
				int queryLength, int subjectLength, int numberOfRelevantRecords)
	:QGraphicsView(parent)
{
	numberOfRecords = numberOfRelevantRecords;
	myQueryStart = matchesStart;
	myQueryEnd = matchesEnd;
	mySubjectStart = matchesSubjectStart;
	mySubjectEnd = matchesSubjectEnd;
	mySubjectLength = subjectLength;
	myQueryLength = queryLength;
	scene = new QGraphicsScene(this);
	setAlignment(Qt::AlignCenter);
	setRenderHints(QPainter::Antialiasing|
				   QPainter::TextAntialiasing);
	setScene(scene);

}

void MatchesView::createScene(int width, int height)
{
	vector<int>	qStarts (myQueryStart, myQueryStart + numberOfRecords);
	vector<int> sStarts (mySubjectStart, mySubjectStart + numberOfRecords);
	vector<int>	qEnds (myQueryEnd, myQueryEnd + numberOfRecords);
	vector<int> sEnds (mySubjectEnd, mySubjectEnd + numberOfRecords);
	
	
	map<int, int> qNext, sNext, qPrev, sPrev; //, ltstr
	
	vector<int>::iterator it;
   	
   	//Assumption: all matches are consequtive
   	sort (qStarts.begin(), qStarts.end());
   	sort (sStarts.begin(), sStarts.end());
   	sort (qEnds.begin(), qEnds.end());
   	sort (sEnds.begin(), sEnds.end());
   	
   	int scale = 3;
 	int sep = 240;
  	
   	int qstart = 0;
	int qend = 0;
	int sstart = 0;
	int send = 0;
	
	//int height = 20;
   	
	for(int i = 0; i < numberOfRecords; i++)
	{
   		qstart = myQueryStart[i]/scale;
		qend = myQueryEnd[i]/scale;
		sstart = mySubjectStart[i]/scale;
		send = mySubjectEnd[i]/scale;
		QPainterPath line;
		line.moveTo( (qend + qstart)/2, 20);
		line.lineTo( (send + sstart)/2, sep); //10 + 
		QGraphicsPathItem *lineItem = new QGraphicsPathItem(line);
		//QGraphicsItem.Pen pen();
		//pen.setStyle(Qt::DashDotLine);
		lineItem->setPen(QPen(Qt::DashLine));
 		//pen.setWidth(3);
		//pen.setBrush(Qt::green);
		//pen.setCapStyle(Qt::RoundCap);
		//pen.setJoinStyle(Qt::RoundJoin);

		//painter.setPen(pen);
		scene->addItem(lineItem);
	}   	
   
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
		
		//qDebug() << forwardOverlapLength;
		QPolygonF qpolygon;
		qpolygon << QPointF(qstart, 0);
		qpolygon << QPointF(qend - qforwardOverlapLength, 0);
		qpolygon << QPointF(qend - qforwardOverlapLength, 10);
		qpolygon << QPointF(qend, 10);
		qpolygon << QPointF(qend, 20);
		qpolygon << QPointF(qstart + qbackwardOverlapLength, 20);
		qpolygon << QPointF(qstart + qbackwardOverlapLength, 10);
		qpolygon << QPointF(qstart, 10);
		
		//QLinearGradient linearGradient((qend-qstart)/2,0,(qend-qstart)/2,20);
    	//linearGradient.setColorAt(0.0,Qt::black);
    	//linearGradient.setColorAt(0.2,colorForMatchIndex);
    	//linearGradient.setColorAt(0.8,colorForMatchIndex);
    	//linearGradient.setColorAt(1.0,Qt::black); //QColor(181, 172, 174)
    	//painter->setBrush(linearGradient);
		//painter->drawPolygon(points, numPoints);
		QGraphicsPolygonItem *qmatch = new QGraphicsPolygonItem(qpolygon);
		qmatch->setPen(Qt::NoPen);
		qmatch->setBrush(colorForMatchIndex(i));
		scene->addItem(qmatch);		

		QPolygonF spolygon;
		spolygon << QPointF(sstart, 0 + sep);
		spolygon << QPointF(send - sforwardOverlapLength, 0 + sep);
		spolygon << QPointF(send - sforwardOverlapLength, 10 + sep);
		spolygon << QPointF(send, 10 + sep);
		spolygon << QPointF(send, 20 + sep);
		spolygon << QPointF(sstart + sbackwardOverlapLength, 20 + sep);
		spolygon << QPointF(sstart + sbackwardOverlapLength, 10 + sep);
		spolygon << QPointF(sstart, 10 + sep);



		//polygon << QPointF(,);
		
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
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
		}
		
		if(qbackwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(qstart,0);
			path.lineTo(qstart,20);
			QGraphicsPathItem *beginLine = new QGraphicsPathItem(path);
			scene->addItem(beginLine);
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
		}

		if(sforwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(send,0 + sep);
			path.lineTo(send,20 + sep);
			QGraphicsPathItem *endLine = new QGraphicsPathItem(path);
			scene->addItem(endLine);
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
		}
		
		if(sbackwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(sstart,0 + sep);
			path.lineTo(sstart,20 + sep);
			QGraphicsPathItem *beginLine = new QGraphicsPathItem(path);
			scene->addItem(beginLine);
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
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
		sTopLine.moveTo(sstart,0 + sep);
		sTopLine.lineTo(send - sforwardOverlapLength,0 + sep);
		QGraphicsPathItem *sTopLineItem = new QGraphicsPathItem(sTopLine);
		scene->addItem(sTopLineItem);
		
		QPainterPath sBottomLine;
		sBottomLine.moveTo(sstart + sbackwardOverlapLength,20 + sep);
		sBottomLine.lineTo(send, 20 + sep);
		QGraphicsPathItem *sBottomLineItem = new QGraphicsPathItem(sBottomLine);
		scene->addItem(sBottomLineItem);
		
		//QGraphicsRectItem *rectangle = new QGraphicsRectItem(myQueryStart[i],0,myQueryEnd[i],20);
		//scene->addItem(rectangle);
		
	}
   	
	/*
	for (int i = 0; i < qStarts.length(); i++)
   	{	
		if(it < qStarts.length() - 1)
   			qNext[qStarts[i]] = qStarts[i+1];
   		if(it != 1)
   			qPrev[q[i]] = *(it+1);
   		
   	}
	for (it=sStarts.begin(); it!=sStarts.end(); ++it)
   	{	
		if(it < qStarts.end() - 1)
   			sStarts[*it] = *(it+1);
   		if(it > 1)
   			sPrev[*it] = *(it+1);
   		
   	}
   	
   	//int startIndex[numberOfRecords];
   	//int endIndex[numberOfRecords];
	
	int scale = 2;
   	
   	for(int i = 0; i < numberOfRecords; i++)
   	{
   		int qstart = myQueryStart[i]/scale;
		int sstart = mySubjectStart[i]/scale;
   		qStartIndex[qstart] = i;
		sStartIndex[sstart] = i;
   	}
	
	for(int i = 0; i < numberOfRecords; i++)
	{
		int qstart = myQueryStart[i]/scale;
		int qend = myQueryEnd[i]/scale;
		int qforwardOverlapLength = 0;
		int qbackwardOverlapLength = 0;

		int sstart = mySubjectStart[i]/scale;
		int send = mySubjectEnd[i]/scale;
		int sforwardOverlapLength = 0;
		int sbackwardOverlapLength = 0;
	
		int sep = 140;
		
		//qDebug() << "qstart = " << qstart;
		//qDebug() << "qend = " << qend;

		QPainterPath line;
		line.moveTo( (qend + qstart)/2, 10);
		line.lineTo( (send + sstart)/2, 10 + sep);
		QGraphicsPathItem *lineItem = new QGraphicsPathItem(line);
		//QGraphicsItem.Pen pen();
		//pen.setStyle(Qt::DashDotLine);
		lineItem->setPen(QPen(Qt::DashLine));
 		//pen.setWidth(3);
		//pen.setBrush(Qt::green);
		//pen.setCapStyle(Qt::RoundCap);
		//pen.setJoinStyle(Qt::RoundJoin);

		//painter.setPen(pen);
		scene->addItem(lineItem);

		
		if(i != numberOfRecords - 1)
		{
			int qnextstart = myQueryStart[i+1]/scale;
			int snextstart = mySubjectStart[i+1]/scale;
			qforwardOverlapLength = qend - qnextstart;
			sforwardOverlapLength = send - snextstart;
			if(qforwardOverlapLength < 0) qforwardOverlapLength = 0;
			if(sforwardOverlapLength < 0) sforwardOverlapLength = 0;
		}
		if( i != 0)
		{
			int qprevend = myQueryEnd[i-1]/scale;
			int sprevend = mySubjectEnd[i-1]/scale;
			qbackwardOverlapLength = qprevend - qstart;
			sbackwardOverlapLength = sprevend - sstart;
			if(qbackwardOverlapLength < 0) qbackwardOverlapLength = 0;
			if(sbackwardOverlapLength < 0) sbackwardOverlapLength = 0;
		}
		
		//qDebug() << forwardOverlapLength;
		QPolygonF qpolygon;
		qpolygon << QPointF(qstart, 0);
		qpolygon << QPointF(qend - qforwardOverlapLength, 0);
		qpolygon << QPointF(qend - qforwardOverlapLength, 10);
		qpolygon << QPointF(qend, 10);
		qpolygon << QPointF(qend, 20);
		qpolygon << QPointF(qstart + qbackwardOverlapLength, 20);
		qpolygon << QPointF(qstart + qbackwardOverlapLength, 10);
		qpolygon << QPointF(qstart, 10);
		
		//QLinearGradient linearGradient((qend-qstart)/2,0,(qend-qstart)/2,20);
    	//linearGradient.setColorAt(0.0,Qt::black);
    	//linearGradient.setColorAt(0.2,colorForMatchIndex);
    	//linearGradient.setColorAt(0.8,colorForMatchIndex);
    	//linearGradient.setColorAt(1.0,Qt::black); //QColor(181, 172, 174)
    	//painter->setBrush(linearGradient);
		//painter->drawPolygon(points, numPoints);
		QGraphicsPolygonItem *qmatch = new QGraphicsPolygonItem(qpolygon);
		qmatch->setPen(Qt::NoPen);
		qmatch->setBrush(colorForMatchIndex(i));
		scene->addItem(qmatch);

		

		QPolygonF spolygon;
		spolygon << QPointF(sstart, 0 + sep);
		spolygon << QPointF(send - sforwardOverlapLength, 0 + sep);
		spolygon << QPointF(send - sforwardOverlapLength, 10 + sep);
		spolygon << QPointF(send, 10 + sep);
		spolygon << QPointF(send, 20 + sep);
		spolygon << QPointF(sstart + sbackwardOverlapLength, 20 + sep);
		spolygon << QPointF(sstart + sbackwardOverlapLength, 10 + sep);
		spolygon << QPointF(sstart, 10 + sep);



		//polygon << QPointF(,);
		
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
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
		}
		
		if(qbackwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(qstart,0);
			path.lineTo(qstart,20);
			QGraphicsPathItem *beginLine = new QGraphicsPathItem(path);
			scene->addItem(beginLine);
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
		}

		if(sforwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(send,0 + sep);
			path.lineTo(send,20 + sep);
			QGraphicsPathItem *endLine = new QGraphicsPathItem(path);
			scene->addItem(endLine);
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
		}
		
		if(sbackwardOverlapLength == 0)
		{
			QPainterPath path;
			path.moveTo(sstart,0 + sep);
			path.lineTo(sstart,20 + sep);
			QGraphicsPathItem *beginLine = new QGraphicsPathItem(path);
			scene->addItem(beginLine);
			//QGraphicsPathItem *beginLine = new QGraphicsPathItem();
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
		sTopLine.moveTo(sstart,0 + sep);
		sTopLine.lineTo(send - sforwardOverlapLength,0 + sep);
		QGraphicsPathItem *sTopLineItem = new QGraphicsPathItem(sTopLine);
		scene->addItem(sTopLineItem);
		
		QPainterPath sBottomLine;
		sBottomLine.moveTo(sstart + sbackwardOverlapLength,20 + sep);
		sBottomLine.lineTo(send, 20 + sep);
		QGraphicsPathItem *sBottomLineItem = new QGraphicsPathItem(sBottomLine);
		scene->addItem(sBottomLineItem);
		
		//QGraphicsRectItem *rectangle = new QGraphicsRectItem(myQueryStart[i],0,myQueryEnd[i],20);
		//scene->addItem(rectangle);
		
	}
	*/
	
}

void MatchesView::clearScene()
{
	QList<QGraphicsItem *> list = scene->items();
	QList<QGraphicsItem *>::Iterator iterator = list.begin();
	for ( ; iterator != list.end(); ++iterator)
	{
		if ( *iterator )
		{
			scene->removeItem(*iterator);
			delete *iterator;
		}
	}

}

void MatchesView::resizeEvent(QResizeEvent* event)
{
	clearScene();
	createScene(event->size().width()-70, event->size().height() - 150);
	
	QGraphicsView::resizeEvent(event);
}

QColor MatchesView::colorForMatchIndex(int index)
{
	QColor colors[5];
	colors[0] = QColor(255, 77, 65);
	colors[1] = QColor(242, 147, 31);
	colors[2] = QColor(229, 202, 33);
	colors[3] = QColor(145, 178, 33);
	colors[4] = QColor(30, 140, 101);
	
	return colors[index % 5];
}
