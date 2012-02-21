#include "plotLayer.h"

Region::Region(unsigned radius, unsigned width, qreal initialAngle, 
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

void Region::arc(QPainterPath &path, unsigned radius, qreal initialAngle,
			 qreal terminalAngle)
{
	QRect pathRectangle(-radius, -radius, 2*radius, 2*radius);	
	path.arcTo(pathRectangle, initialAngle, terminalAngle - initialAngle);
}

qreal Region::max(qreal a, qreal b)
{
	if( a > b ) return a;
	return b;
}

qreal Region::min(qreal a, qreal b)
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

void Contig::plotRegions(QGraphicsScene &scene)
{
	Region *region;
	unsigned size = initialAngles.size();
	if( size == 1 )
	{
		region = new Region(150, 40, initialAngles[0], terminalAngles[0], initialAngles[0], terminalAngles[0], colors[0]);
		scene.addItem(region);
		return;
	} else
	{
		region = new Region(150, 40, initialAngles[0], terminalAngles[0], initialAngles[0], initialAngles[1], colors[0]);
		scene.addItem(region);
	}
	
	for(unsigned i = 1; i < size - 1; i++)
	{
		qreal init = initialAngles[i];
		qreal term = terminalAngles[i];
		QColor color = colors[i];
		
		region = new Region(150, 40, initialAngles[i], terminalAngles[i], terminalAngles[i - 1], initialAngles[i + 1], colors[i]);
		scene.addItem(region);
	}
	
	region = new Region(150, 40, initialAngles[size - 1], terminalAngles[size - 1], terminalAngles[size - 2], terminalAngles[size - 1], colors[size - 1]);
	scene.addItem(region);
	
}

void Contig::plotContigOutline(QGraphicsScene &scene)
{
	ContigOutline *outline = new ContigOutline(150, 40, start, end, QColor(10,10,10,10));
	scene.addItem(outline);
}

void Contig::plotContig(QGraphicsScene &scene)
{
	plotRegions(scene);
	plotContigOutline(scene);
}

PlotLayer::PlotLayer(Layer &layer, QGraphicsScene &scene)
{
	QMap<QString, ContigData> *contigs = &layer.contigs;
	
	QMap<QString, ContigData>::iterator i;
	
	//L is the size of the entire sequence (including gaps) to be displayed
	qreal L = 0;
	i = contigs->begin();
	
	qreal gap = 50;
	
	while (i != contigs->end())
	{
		//qDebug() << "contig: " << i.key();
		L = L + layer.size[i.key()] + gap;
		++i;
	}
	
	gap = gap*360/L; //from nt to deg
	
	i = contigs->begin();
	qreal contigStartAngle = 0;
	qreal contigEndAngle = 0;
	
	while (i != contigs->end())
	{
    	ContigData *contig = &i.value();
    	QString contigName = i.key();
    	
    	QVector<qreal> newInitialAngles;
    	QVector<qreal> newTerminalAngles;
    	QVector<QColor> newColors;
    	
    	contigEndAngle = contigStartAngle + layer.size[contigName]*360/L;
    	
    	qreal segmentStartAngle = contigStartAngle;
    	qreal segmentEndAngle = 0;
    	
    	for(int j = 0; j < contig->Us.size(); j++)
    	{
    		//initial angle for sequence i
    		qreal U = contig->Us[j];
    		qreal D = contig->Ds[j];
    		
    		segmentStartAngle = contigStartAngle + U*360/L;
			segmentEndAngle = segmentStartAngle + (D - U)*360/L;
    			
    		newInitialAngles.append(segmentStartAngle);
    		newTerminalAngles.append(segmentEndAngle);
    		newColors.append(QColor(rand()%255,rand()%255,rand()%255));
    	}
    	
    	Contig ctg(contigStartAngle, contigEndAngle, newInitialAngles, newTerminalAngles, newColors);
    	ctg.print();
		ctg.plotContig(scene);
		
		contigStartAngle = contigEndAngle + gap;
		
     ++i;
 	}
}

void Contig::print()
{
	qDebug() << initialAngles;
	qDebug() << terminalAngles;
}