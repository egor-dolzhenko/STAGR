#ifndef LAYERARCS_H
#define LAYERARCS_H

#include <QtCore>

class LayerArcs
{
public:
	LayerArcs();
	QMap<QString, QMap<QString, QVector<unsigned> > > precPos;
	QMap<QString, QMap<QString, QVector<unsigned> > > prodPos;
	//QVector<unsigned> precPos;
	//QVector<unsigned> prodPos; 
};
#endif
