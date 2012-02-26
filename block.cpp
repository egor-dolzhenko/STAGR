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
#include "block.h"

Block::Block(int width, int height, BlockType blockType, QColor color)
{
	myWidth = width;
	myHeight = height;
	myBlockType = blockType;
	myColor = color;
}

QRectF Block::boundingRect() const
{
	QRectF rect = QRectF(0, 0, myWidth, myHeight);
	return rect;
}

void Block::paint(QPainter *painter,
			      const QStyleOptionGraphicsItem *option,
			      QWidget *widget)
{
 

	int numPoints = 0;
	//Maybe move to constructor:
	if(myBlockType == BLOCK)
	{
		numPoints = 4;

		points = new QPointF[numPoints];
		points[0] = QPointF(0.0, 0.0);
		points[1] =	QPointF(myWidth, 0.0);
		points[2] =	QPointF(myWidth, myHeight);
		points[3] =	QPointF(0, myHeight);
	}
	else if (myBlockType == BLOCK_POINT_LEFT)
	{
		numPoints = 5;
		points = new QPointF[numPoints];
		
		points[0] =	QPointF(0.0, 0.0);
		points[1] = QPointF(myWidth, 0.0);
		points[2] = QPointF(myWidth, myHeight);
		points[3] = QPointF(0, myHeight);
		points[4] = QPointF(-3.5, myHeight/2);
		
	} else if (myBlockType == BLOCK_POINT_RIGHT)
	{
		numPoints = 5;
		points = new QPointF[numPoints];
		
		points[0] = QPointF(0.0, 0.0);
		points[1] = QPointF(myWidth, 0.0);
		points[2] = QPointF(myWidth + 3.5, myHeight/2);
		points[3] = QPointF(myWidth, myHeight);
		points[4] = QPointF(0, myHeight);
		
	} else if (myBlockType == BLOCK_INCOMPLETE_RIGHT)
	{
	
		int numPointsWiggle = myHeight/5 - 1;
		numPoints = 4 + numPointsWiggle;
		points = new QPointF[numPoints];
		
		points[0] = QPointF(0.0, 0.0);
		points[1] = QPointF(myWidth, 0.0);
		int step = 5;
		int parity = 1;
		for(int i = 2; i <= numPointsWiggle + 1; i++)
		{
			parity = parity * (-1);
			
			points[i] = QPointF(myWidth + 2*parity, step);
			step = step + 5;
		}
		points[numPoints - 2] = QPointF(myWidth, myHeight);
		points[numPoints - 1] =	QPointF(0, myHeight);
			
	}else if (myBlockType == BLOCK_INCOMPLETE_LEFT)
	{

		int numPointsWiggle = myHeight/5 - 1;
		numPoints = 4 + numPointsWiggle;
		points = new QPointF[numPoints];
		
		points[0] = QPointF(0.0, 0.0);
		points[1] = QPointF(myWidth, 0.0);
		points[2] = QPointF(myWidth, myHeight);
		points[3] =	QPointF(0, myHeight);
		int step = myHeight - 5;
		int parity = 1;
		for(int i = 4; i <= numPointsWiggle + 3; i++)
		{
			parity = parity * (-1);
			
			points[i] = QPointF(2*parity, step);
			step = step - 5;
		}
		
	}else if (myBlockType == BLOCK_POINT_LEFT_INCOMPLETE)
	{
		int numPointsWiggle = myHeight/5 - 1;
		numPoints = 5 + numPointsWiggle;
		points = new QPointF[numPoints];
		
		points[0] = QPointF(0.0, 0.0);
		points[1] = QPointF(myWidth, 0.0);
		int step = 5;
		int parity = 1;
		
		for(int i = 2; i <= numPointsWiggle + 1; i++)
		{
			parity = parity * (-1);
			
			points[i] = QPointF(myWidth + 2*parity, step);
			step = step + 5;
			
		}
		points[numPoints - 3] = QPointF(myWidth, myHeight);
		points[numPoints - 2] =	QPointF(0, myHeight);
		points[numPoints - 1] =	QPointF(-3.5, myHeight/2);
		

	}else if (myBlockType == BLOCK_POINT_RIGHT_INCOMPLETE)
	{
		int numPointsWiggle = myHeight/5 - 1;
		numPoints = 5 + numPointsWiggle;
		points = new QPointF[numPoints];
		
		points[0] = QPointF(0.0, 0.0);
		points[1] = QPointF(myWidth, 0.0);
		points[2] = QPointF(myWidth + 3.5, myHeight/2);
		points[3] = QPointF(myWidth, myHeight);
		points[4] =	QPointF(0, myHeight);
		int step = myHeight - 5;
		int parity = 1;
		for(int i = 5; i <= numPointsWiggle + 4; i++)
		{
			parity = parity * (-1);
			
			points[i] = QPointF(2*parity, step);
			step = step - 5;
		}
		

	}else if (myBlockType == BLOCK_INCOMPLETE_LEFT_RIGHT)
	{
		int numPointsWiggle = myHeight/5 - 1;
		numPoints = 4 + 2*numPointsWiggle;
		points = new QPointF[numPoints];
		
		points[0] = QPointF(0.0, 0.0);
		points[1] = QPointF(myWidth, 0.0);
		
		int step = 5;
		int parity = 1;
		
		for(int i = 2; i <= numPointsWiggle + 1; i++)
		{
			parity = parity * (-1);
			
			points[i] = QPointF(myWidth + 2*parity, step);
			step = step + 5;
		}
		
		points[numPointsWiggle + 2] = QPointF(myWidth, myHeight);
		points[numPointsWiggle + 3] =	QPointF(0, myHeight);
		
		step = myHeight - 5;
		parity = 1;
		
		for(int i = numPointsWiggle + 4; i <= 2*numPointsWiggle + 3; i++)
		{
			parity = parity * (-1);
			
			points[i] = QPointF(2*parity, step);
			step = step - 5;
		}
		
	}
    QLinearGradient linearGradient(myWidth/2,0,myWidth/2,myHeight);
    linearGradient.setColorAt(0.0,Qt::black);
    linearGradient.setColorAt(0.2,myColor);
    linearGradient.setColorAt(0.8,myColor);
    linearGradient.setColorAt(1.0,Qt::black); //QColor(181, 172, 174)
    painter->setBrush(linearGradient);
	painter->drawPolygon(points, numPoints);
}