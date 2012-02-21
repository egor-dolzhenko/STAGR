#ifndef LAYER_H
#define LAYER_H

#include <QtCore>
#include "contigData.h"

class Layer
{
public:
	//order in which contigs appear in the array is their display order
	Layer(QVector<unsigned> contigSizes, QVector<QString> contigNames);
	//default constructor to ensure that Layer works with Qt containers
	Layer();
	bool addMatch(QString precName, QString prodName, unsigned precU, 
			 unsigned precD, unsigned prodU, unsigned prodD);
	void print();
	QMap<QString, ContigData> contigs;
	QMap<QString, unsigned> size;
	
private:

	int checkInsertable(QVector<unsigned> &Us, QVector<unsigned> &Ds, unsigned U, unsigned D);
};

#endif