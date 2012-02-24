#include <QtGui>
#include <QGraphicsScene>
#include "chordDiagram.h"
#include "hsp.h"

ChordDiagram::ChordDiagram(QWidget *parent, HspLoci *precursorLoci, HspLoci *productLoci)
	:QGraphicsView(parent)
{

	//circular layout
	QVector<QString> contigNames;
	QVector<unsigned> contigSizes;
	
	for(unsigned i = 0; i < precursorLoci->getSize(); i++)
	{
		unsigned precIndex = precursorLoci->pos(i);
		QString contigName = precursorLoci->id(precIndex);
		
		if(!contigNames.contains(contigName))
		{
			contigNames << contigName;
			contigSizes << precursorLoci->contigSize(contigName);
		}
		
	}

	for(unsigned i = 0; i < productLoci->getSize(); i++)
	{
		unsigned prodIndex = productLoci->pos(i);
		QString contigName = productLoci->id(prodIndex);
		if(!contigNames.contains(contigName))
		{
			contigNames << contigName;
			contigSizes << productLoci->contigSize(contigName);
		}
	}

	QVector<bool> layeredLoci;
	for(unsigned i = 0; i < precursorLoci->getSize(); i++) layeredLoci.append(false);
	
	unsigned numAdded = 0;
	
	radius = 100;
	
	while( numAdded != precursorLoci->getSize() )
	{
		layers.append(Layer(contigSizes, contigNames));
		Layer *layer;
		layer = &layers.last();

		for(unsigned i = 0; i < precursorLoci->getSize(); i++)
		{
			unsigned precIndex = precursorLoci->pos(i);
		
			if(!layeredLoci[precIndex])
			{
				QString precName = precursorLoci->id(precIndex);
				unsigned precU = precursorLoci->uCoord(precIndex);
				unsigned precD = precursorLoci->dCoord(precIndex);

				unsigned prodIndex = productLoci->pos(i);
				QString prodName = productLoci->id(prodIndex);
				unsigned prodU = productLoci->uCoord(prodIndex);
				unsigned prodD = productLoci->dCoord(prodIndex);

				if(layer->addMatch(precName, prodName, precU, precD, prodU, prodD))
				{
					layeredLoci[precIndex] = true;
					numAdded++;
				}
			}
		}
		
		
	}
	
	
	setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
	setScene( &scene );
	
	width = 400;
	height = 400;
	plotDiagram();

	
}

void ChordDiagram::clear()
{
	QList<QGraphicsItem *> list = scene.items();
	QList<QGraphicsItem *>::Iterator iterator = list.begin();
	for ( ; iterator != list.end(); ++iterator)
	{
		if ( *iterator )
		{
			scene.removeItem(*iterator);
			delete *iterator;
		}
	}
}

void ChordDiagram::plotLayers()
{
	unsigned layerRadius = radius;
	
	for(unsigned i = 0; i < layers.size(); ++i)
	{
		layers[i].plotLayer(scene, layerRadius);
		layerRadius += 50;
	}
	
	layers[0].plotArcs(scene, radius);
}

void ChordDiagram::plotDiagram() // 400, 400
{
	clear();
	plotLayers();
}

void ChordDiagram::keyPressEvent(QKeyEvent *event)
{
	if( (event->key() == Qt::Key_Equal) && (event->modifiers() == Qt::ControlModifier) ) 
	{ 
	  //if( nucleotideWidth >= 8) alwaysShowNucleotides = true;
	  if( radius <= 250)
	  {
	    //nucleotideWidth++; resizeEvent(&QResizeEvent(size(), size()));
	    radius += 10;
	    plotDiagram();
	  }
	}
	if( (event->key() == Qt::Key_Minus) && (event->modifiers() == Qt::ControlModifier) )  
	{
	  
	  //if(nucleotideWidth < 8)
	  //{
	  //	alwaysShowNucleotides = false;
	  //}
	  
	  if( radius > 30) 
	  {
	    radius -= 10; 
	    plotDiagram();
	  }
	}	
}
