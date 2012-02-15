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


//hsp.h contains the definition of HSP class which is responsible for storing
//data returned by the filtering algorithm

#ifndef HSP_H
#define HSP_H

#include <Python/Python.h>
#include <QtCore>

class HSPs
{

public:
	//Constructor
	HSPs();
	QString loadData(PyObject *output);
	QVector< QMap<QString,QString> > *matchesToPrecursorId(QString id);
	float getAverage(QString precursorId, QString productId, QString fieldName);
	QSet<QString>* getAllValues(QString fieldName);
	unsigned numHSPs(QString precursorId, QString productId);
	
private:
	QVector< QMap<QString,QString> > hsps;

};

#endif //HSP_H