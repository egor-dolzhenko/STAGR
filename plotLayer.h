#ifndef PLOTLAYER_H
#define PLOTLAYER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QtCore>
//#include "layer.h"
#include "contigData.h"

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
	void plotRegions(QGraphicsScene &scene, unsigned radius);
	void plotContigOutline(QGraphicsScene &scene, unsigned radius);
	void plotContig(QGraphicsScene &scene, unsigned radius);
	void print();
	
private:
	QVector<qreal> initialAngles, terminalAngles;
	QVector<QColor> colors;
	qreal start, end;
};

class Layer
{

public:

	//order in which contigs appear in the array is their display order
	Layer(QVector<unsigned> contigSizes, QVector<QString> contigNames);
	
	//default constructor to ensure that Layer works with Qt containers
	Layer();

	void plotLayer(QGraphicsScene &scene, unsigned radius);
	
	bool addMatch(QString precName, QString prodName, unsigned precU, 
			 unsigned precD, unsigned prodU, unsigned prodD);
	
	void print();
	
	QMap<QString, ContigData> contigs;
	
	QMap<QString, unsigned> size;
	
private:

	int checkInsertable(QVector<unsigned> &Us, QVector<unsigned> &Ds, unsigned U, unsigned D);
	
};

#endif
