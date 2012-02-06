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

#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>

enum BlockType {BLOCK, BLOCK_POINT_LEFT, BLOCK_POINT_RIGHT, BLOCK_INCOMPLETE_LEFT,
	  BLOCK_INCOMPLETE_RIGHT, BLOCK_POINT_LEFT_INCOMPLETE, 
	  BLOCK_POINT_RIGHT_INCOMPLETE, BLOCK_INCOMPLETE_LEFT_RIGHT};

class Block : public QGraphicsItem
{

public:
	Block(int width, int height, BlockType blockType, QColor color);
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	

private:
	int myHeight;
	int myWidth;
	BlockType myBlockType;
	QPointF *points;
	QColor myColor;

};
#endif