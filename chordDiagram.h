#ifndef CHORD_DIAGRAM_H
#define CHORD_DIAGRAM_H

#include <QGraphicsView>
#include "plotLayer.h"

class QGraphicsScene;
class HspLoci;
//class Layer;

class ChordDiagram : public QGraphicsView
{
	Q_OBJECT
	
public:
	ChordDiagram(QWidget *parent, HspLoci *precursorLoci, HspLoci *productLoci);

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	QGraphicsScene scene;
	unsigned radius;
	QVector<Layer> layers;
	void clear();
	void plotLayers();
	void plotDiagram();
	unsigned width; 
	unsigned height;

};

#endif //CHORD_DIAGRAM_H