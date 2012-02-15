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

#include "hsp.h"
#include <QtCore>

HSPs::HSPs()
{
	//hsps = QVector< QMap<QString,QString> >(0);
}

HSPs::HSPs(HSPs *hObj, QSet<QString> &precursorIds, QSet<QString> &productIds)
{

	for(unsigned i = 0; i < hObj->hsps.size(); ++i)
	{
		QMap<QString,QString> hsp = hObj->hsps.at(i);
		QString precursorId = hsp["qseqid"];
 		QString productId = hsp["sseqid"];
		if( precursorIds.contains(precursorId) && productIds.contains(productId) )
		{
			QMapIterator<QString, QString> j(hObj->hsps.at(i));
			
			QMap<QString, QString> hspCopy;// = new QMap<QString, QString>(0);
			
			while (j.hasNext())
			{
     			j.next();
     			hspCopy[j.key()] = j.value(); //(*hspCopy)
     			//qDebug() << j.key() << ": " << j.value();
 			}
 			
 			hsps.append(hspCopy);
		}
		
		//for(unsigned j = 0; j < hObj->hsps.at(i).size(); ++j)
		//{
		//	qDebug() << hObj->hsps.at(i)["qseqid"];
		//}
	}

// 	alignmentsPairContigs = new QVector< QMap<QString,QString> >(0);
// 	alignmentsDirection = new QVector<Direction>(0);
// 	
// 	QString qseqidValue("");
// 	QString sseqidValue("");
// 	for(unsigned i = 0; i < filteredAlignments->size(); ++i)
// 	{
// 		qseqidValue = filteredAlignments->at(i)["qseqid"];
// 		sseqidValue = filteredAlignments->at(i)["sseqid"];
// 		if( (qseqidValue == queryName) && (subjectNames.contains(sseqidValue)) )
// 		{
// 			
// 			unsigned qstartValue = filteredAlignments->at(i)["qstart"].toInt();
// 			unsigned qendValue = filteredAlignments->at(i)["qend"].toInt();
// 			unsigned sstartValue = filteredAlignments->at(i)["sstart"].toInt();
// 			unsigned sendValue = filteredAlignments->at(i)["send"].toInt();
// 			QString qendValueString(qendValue);
// 			const QString qstartValueString(qstartValue);
// 			if(qstartValue > qendValue)
// 			{
// 				(*filteredAlignments)[i].insert("qstart", QString::number(qendValue));
// 				(*filteredAlignments)[i].insert("qend", QString::number(qstartValue));
// 				alignmentsDirection->append(LEFT);
// 			}
// 			else if(sstartValue > sendValue)
// 			{
// 				(*filteredAlignments)[i].insert("sstart", QString::number(sendValue));
// 				(*filteredAlignments)[i].insert("send", QString::number(sstartValue));
// 				alignmentsDirection->append(LEFT);
// 			}
// 			else
// 			{
// 				alignmentsDirection->append(RIGHT);
// 			}
// 
// 			alignmentsPairContigs->append(filteredAlignments->at(i)); //QMap<QString,QString>()
// 		}
// 	}	
// 	
// 	QStringList header;
// 	header = filteredAlignments->at(0).keys();
}

QString HSPs::loadData(PyObject *output)
{

	PyObject *key, *value;

	if( PyList_Size(output) < 1 )
	{
		return "The annotation script did not return any relevant data";
	}
	for( unsigned i = 0; i < PyList_Size(output); ++i)
	{
		PyObject *dictionary = PyList_GetItem(output, i);
		
		Py_ssize_t pos = 0;
		QMap<QString, QString> hsp;
		
		
		while (PyDict_Next(dictionary, &pos, &key, &value))
		{
			if(!PyString_Check(key))
				return "error: key is not a string";
			
			
			if(PyInt_Check(value))
			{
				hsp[PyString_AsString(key)] = QString::number(PyInt_AsLong(value));
			}
			else if(PyFloat_Check(value))
			{
				hsp[QString(PyString_AsString(key))] = QString::number(PyFloat_AsDouble(value));
			}
			else if(PyString_Check(value))
			{
				hsp[PyString_AsString(key)] = QString(PyString_AsString(value));
			}
			else return "conversion error: expected string";
		
		}
		hsps.append(hsp);
	}
	
	return "";
}


QVector< QMap<QString,QString> > *HSPs::matchesToPrecursorId(QString id)
{

}

float HSPs::getAverage(QString precursorId, QString productId, QString fieldName)
{
	float sum = 0;
	unsigned numHspsFound = 0;
	
	for(unsigned i = 0; i < hsps.size(); i++)
	{
		if( (precursorId == hsps.at(i)["qseqid"]) && (productId == hsps.at(i)["sseqid"]) )
		{
			sum += hsps.at(i)[fieldName].toInt();
			numHspsFound++;
		}
	}
	
	if(numHspsFound == 0) return 0;
	
	return sum/(float)numHspsFound;
}

QSet<QString>* HSPs::getAllValues(QString fieldName)
{
	QSet<QString> *values = new QSet<QString>;
	
	for(unsigned i = 0; i < hsps.size(); i++)
	{
		values->insert(hsps.at(i)[fieldName]);
	}
	
	return values;
}

unsigned HSPs::numHSPs(QString precursorId, QString productId)
{
	unsigned numHspsFound = 0;
	
	for(unsigned i = 0; i < hsps.size(); i++)
	{
		if( (precursorId == hsps.at(i)["qseqid"]) && (productId == hsps.at(i)["sseqid"]) )
		{
			numHspsFound++;
		}
	}
	
	return numHspsFound;
}

