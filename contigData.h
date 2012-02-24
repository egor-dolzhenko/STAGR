#ifndef CONTIGDATA_H
#define CONTIGDATA_H

#include<QtCore>
#include<QColor>

//class QColor;

class ContigData
{
public: 
	ContigData();
	int checkPosition(unsigned U, unsigned D);
	void include(unsigned U, unsigned D, QColor color, int position);
	void print();
	QVector<unsigned> Us;
	QVector<unsigned> Ds;
	QVector<QColor> Cols;

private:
	bool checkHole(int i);
	bool checkOneU(int i, unsigned U, unsigned D);
	bool checkOneD(int i, unsigned U, unsigned D);
	bool checkTwoU(int i, unsigned U, unsigned D);
	bool checkTwoD(int i, unsigned U, unsigned D);
	unsigned max(unsigned a, unsigned b);
	unsigned min(unsigned a, unsigned b);
};

#endif