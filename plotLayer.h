#ifndef PLOTLAYER_H
#define PLOTLAYER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QtCore>
#include "layer.h"

class Region : public QGraphicsPathItem
{

public:
	Region(unsigned radius, unsigned width, qreal initialAngle, 
		   qreal terminalAngle, qreal upstreamNeighborTerminalAngle, 
		   qreal donwstreamNeighborInitialAngle, QColor color);
private:		   
	void arc(QPainterPath &path, unsigned radius, qreal initialAngle,
			 qreal terminalAngle);
			 
	qreal max(qreal a, qreal b);
	qreal min(qreal a, qreal b);	
};

class ContigOutline : public QGraphicsPathItem
{
public:
	ContigOutline(unsigned radius, unsigned width, qreal initialAngle, 
				  qreal terminalAngle, QColor color);

private:		   
	void arc(QPainterPath &path, unsigned radius, qreal initialAngle,
			 qreal terminalAngle);

};

class Contig
{

public:
	Contig(qreal start, qreal end, QVector<qreal> newInitialAngles, QVector<qreal> newTerminalAngles, 
		   QVector<QColor> newColors);
	void plotRegions(QGraphicsScene &scene);
	void plotContigOutline(QGraphicsScene &scene);
	void plotContig(QGraphicsScene &scene);
	void print();
	
private:
	QVector<qreal> initialAngles, terminalAngles;
	QVector<QColor> colors;
	qreal start, end;
};

class PlotLayer
{
public:
	PlotLayer(Layer &layer, QGraphicsScene &scene);
};

#endif
