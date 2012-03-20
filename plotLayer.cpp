#include "plotLayer.h"

#define PI 3.14159

SRegion::SRegion(unsigned radius, unsigned width, qreal initialAngle, 
			   qreal terminalAngle, qreal upstreamNeighborTerminalAngle, 
			   qreal donwstreamNeighborInitialAngle, QColor color)
			   : QGraphicsPathItem(NULL)
{
	QPainterPath p = path();
	
	QRect pathRectangle(-radius, -radius, 2*radius, 2*radius);
	p.arcMoveTo(pathRectangle, initialAngle);

	
	//terminal angle of the outer arc is terminalAngle
	//while initial angle is 
	qreal outerInitial = max(initialAngle, upstreamNeighborTerminalAngle);
	
	if( outerInitial == upstreamNeighborTerminalAngle )
	{
		arc(p, radius, initialAngle, upstreamNeighborTerminalAngle);
	}
	
	arc(p, radius + width/2, outerInitial, terminalAngle);
	
	
	//initial angle of the inner arc is initialAngle
	//while terminal angle is
	qreal innerTerminal = min(terminalAngle, donwstreamNeighborInitialAngle);
	
	if( innerTerminal == donwstreamNeighborInitialAngle )
	{
		arc(p, radius, terminalAngle, donwstreamNeighborInitialAngle); 
	}
	
	arc(p, radius - width/2, innerTerminal, initialAngle);
	
	p.closeSubpath();

	setPen(Qt::NoPen);
	setBrush(color);
	setPath(p);

}

void SRegion::arc(QPainterPath &path, unsigned radius, qreal initialAngle,
			 qreal terminalAngle)
{
	QRect pathRectangle(-radius, -radius, 2*radius, 2*radius);	
	path.arcTo(pathRectangle, initialAngle, terminalAngle - initialAngle);
}

qreal SRegion::max(qreal a, qreal b)
{
	if( a > b ) return a;
	return b;
}

qreal SRegion::min(qreal a, qreal b)
{
	if( a < b ) return a;
	return b;
}


ContigOutline::ContigOutline(unsigned radius, unsigned width, qreal initialAngle, 
				  			 qreal terminalAngle, QColor color)
{
	QPainterPath p = path();
	
	QRect pathRectangle(-radius, -radius, 2*radius, 2*radius);
	p.arcMoveTo(pathRectangle, initialAngle);
	arc(p, radius + width/2, initialAngle, terminalAngle);
	arc(p, radius - width/2, terminalAngle, initialAngle);
	
	p.closeSubpath();
	QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	setPen(pen); //Qt::NoPen
	setBrush(color);
	setPath(p);
}

  
void ContigOutline::arc(QPainterPath &path, unsigned radius, qreal initialAngle,
			 			qreal terminalAngle)
{
	QRect pathRectangle(-radius, -radius, 2*radius, 2*radius);	
	path.arcTo(pathRectangle, initialAngle, terminalAngle - initialAngle);
}


Contig::Contig(qreal newStart, qreal newEnd, QVector<qreal> newInitialAngles, QVector<qreal> newTerminalAngles, QVector<QColor> newColors)
{
	start = newStart;
	end = newEnd;
	initialAngles = newInitialAngles;
	terminalAngles = newTerminalAngles;
	colors = newColors;
}

void Contig::plotRegions(QGraphicsScene &scene, unsigned radius)
{
	SRegion *region;
	unsigned size = initialAngles.size();
	if( size == 1 )
	{
		region = new SRegion(radius, 40, initialAngles[0], terminalAngles[0], initialAngles[0], terminalAngles[0], colors[0]);
		scene.addItem(region);
		return;
	} else
	{
		region = new SRegion(radius, 40, initialAngles[0], terminalAngles[0], initialAngles[0], initialAngles[1], colors[0]);
		scene.addItem(region);
	}
	
	for(unsigned i = 1; i < size - 1; i++)
	{
		qreal init = initialAngles[i];
		qreal term = terminalAngles[i];
		QColor color = colors[i];
		
		region = new SRegion(radius, 40, initialAngles[i], terminalAngles[i], terminalAngles[i - 1], initialAngles[i + 1], colors[i]);
		scene.addItem(region);
	}
	
	region = new SRegion(radius, 40, initialAngles[size - 1], terminalAngles[size - 1], terminalAngles[size - 2], terminalAngles[size - 1], colors[size - 1]);
	scene.addItem(region);
	
}

void Contig::plotContigOutline(QGraphicsScene &scene, unsigned radius)
{
	ContigOutline *outline = new ContigOutline(radius, 40, start, end, QColor(10,10,10,10));
	scene.addItem(outline);
}

void Contig::plotContig(QGraphicsScene &scene, unsigned radius)
{
	if(initialAngles.size() != 0)
		plotRegions(scene, radius);
	
	plotContigOutline(scene, radius);
}

void Layer::plotLayer(QGraphicsScene &scene, unsigned radius)
{
	
	QMap<QString, ContigData>::iterator i;
	
	//L is the size of the entire sequence (including gaps) to be displayed
	qreal L = 0;
	i = contigs.begin();
	
	qreal gap = 50;
	
	while (i != contigs.end())
	{
		L = L + size[i.key()] + gap;
		++i;
	}
	
	totalLen = L;
	
	gap = gap*360/L; 
	
	i = contigs.begin();
	qreal contigStartAngle = 0;
	qreal contigEndAngle = 0;
	
	while (i != contigs.end())
	{
    	ContigData *contig = &i.value();
    	QString contigName = i.key();
    	
    	QVector<qreal> newInitialAngles;
    	QVector<qreal> newTerminalAngles;
    	QVector<QColor> newColors;
    	
    	contigEndAngle = contigStartAngle + size[contigName]*360/L;
    	
    	qreal segmentStartAngle = contigStartAngle;
    	qreal segmentEndAngle = 0;

		contigStartAngles[contigName] = contigStartAngle;    	
    	
    	for(int j = 0; j < contig->Us.size(); j++)
    	{
    		//initial angle for sequence i
    		qreal U = contig->Us[j];
    		qreal D = contig->Ds[j];
    		QColor color = contig->Cols[j];
    		
    		segmentStartAngle = contigStartAngle + U*360/L;
			segmentEndAngle = segmentStartAngle + (D - U)*360/L;
    		
    		newInitialAngles.append(segmentStartAngle);
    		newTerminalAngles.append(segmentEndAngle);
    		newColors.append(color); 
    	}
    	
    	Contig ctg(contigStartAngle, contigEndAngle, newInitialAngles, newTerminalAngles, newColors);
    	
		ctg.plotContig(scene, radius);
		
		contigStartAngle = contigEndAngle + gap;
		
     ++i;
 	}
}

void Layer::plotArcs(QGraphicsScene &scene, unsigned radius)
{

	QMap<QString, QMap<QString, QVector<unsigned> > >::iterator Prec;
	QMap<QString, QVector<unsigned> >::iterator Prod;
	
	Prec = layerArcs.precPos.begin();
	
	while( Prec != layerArcs.precPos.end() )
	{
		qreal precStartAngle = contigStartAngles[Prec.key()];
		
		Prod = Prec.value().begin();	
		
		while( Prod != Prec.value().end() ) 
		{
			
			qreal prodStartAngle = contigStartAngles[Prod.key()];
			
			QVector<unsigned> *precLoci = &Prod.value();
			QVector<unsigned> *prodLoci = &layerArcs.prodPos[Prec.key()][Prod.key()];
			
			for(unsigned index = 0; index < precLoci->size(); index++)
			{
 				qreal precX = 360*(precLoci->at(index))/totalLen + precStartAngle; //
 				qreal precY = 360*(precLoci->at(index))/totalLen + precStartAngle; //
				
				qreal prodX = 360*(prodLoci->at(index))/totalLen + prodStartAngle; //
 				qreal prodY = 360*(prodLoci->at(index))/totalLen + prodStartAngle; //
								
				precX = (radius-20)*qCos(PI*precX/180);
 				precY = (radius-20)*qSin(PI*precY/180);

				prodX = (radius-20)*qCos(PI*prodX/180);
				prodY = (radius-20)*qSin(PI*prodY/180);

				QGraphicsPathItem *arc = new QGraphicsPathItem();

				QPainterPath p = arc->path();
				p.moveTo(precX, -precY);
				//p.lineTo(QPointF(prodX, -prodY));
				//p.cubicTo(QPointF(0,0), QPointF(0,0), QPointF(prodX, -prodY) );
				p.quadTo(QPointF(0,0), QPointF(prodX, -prodY));
								
				arc->setPath(p);
				QPen pen;
				pen.setStyle(Qt::DashLine);
 				arc->setPen(pen);
 				scene.addItem(arc);
 				
			}
			++Prod;
		}
		
		++Prec;
	}
	
}

Layer::Layer(QVector<unsigned> contigSizes, QVector<QString> contigNames)
{
	for(unsigned i = 0; i < contigNames.size(); ++i)
	{
		QString name = contigNames[i];
		contigs[name] = ContigData();
		size[name] = contigSizes[i];
	}
}

Layer::Layer()
{
	
}

bool Layer::addMatch(QString precName, QString prodName, unsigned precU, 
			  unsigned precD, unsigned prodU, unsigned prodD)
{

	ContigData *precContig = &contigs[precName];
	int precPos = precContig->checkPosition(precU, precD);
	
	ContigData *prodContig = &contigs[prodName];
	int prodPos = prodContig->checkPosition(prodU, prodD);
	
	if( (precPos == -1) || (prodPos == -1) ) return false;
	
	QColor color(rand()%255,rand()%255,rand()%255);
	precContig->include(precU, precD, color, precPos);
	prodContig->include(prodU, prodD, color, prodPos);
	
	layerArcs.precPos[precName][prodName].append( (precU + precD)/2 );
	layerArcs.prodPos[precName][prodName].append( (prodU + prodD)/2 );
	
	return true;
}

void Layer::print()
{
 	QMap<QString, ContigData>::iterator i = contigs.begin();
	
	while (i != contigs.end()) 
	{
    	qDebug() << i.key() << ": "; 
    	(i.value()).print();
    	++i;
 	}
}

void Contig::print()
{
	qDebug() << initialAngles;
	qDebug() << terminalAngles;
}
