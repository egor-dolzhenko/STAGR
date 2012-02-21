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
	
	//calculateCoordinates();

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
	
	//calculateCoordinates();
	
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

QStringList* HSPs::getKeys()
{
	QStringList *keys = new QStringList(hsps.at(0).keys());
	return keys;
}

unsigned HSPs::numHSPs()
{
	return hsps.size();
}

QString HSPs::getElement(unsigned numHsp, QString id)
{
	return hsps.at(numHsp)[id];
}

void HSPs::printTable()
{

	QStringList header = hsps.at(0).keys();
	for(unsigned i = 0; i < hsps.size(); i++)
	{
		QStringList row;
		for(unsigned j = 0; j < header.size(); j++)
		{
			row << hsps.at(i)[header[j]];
		}
		qDebug() << row;
	}

}

HspLoci::HspLoci(HSPs *hsps, QString upstreamId, QString downstreamId, QString idId)
{
	minUpstream = smallestValue(hsps, upstreamId) - 1; //"qstart"
	maxDownstream = largestValue(hsps, downstreamId); //"qend"
	//minUpstreamProduct = smallestValue(hsps, "sstart") - 1;
	//maxDownstreamProduct = largestValue(hsps, "send");
	
	for(unsigned i = 0; i < hsps->numHSPs(); ++i)
	{
	
		unsigned beginCoord = hsps->getElement(i,upstreamId).toInt() - minUpstream;
		unsigned endCoord = hsps->getElement(i,downstreamId).toInt() - minUpstream;
		
			//const QString qstartValueString(qstartValue);
			
		if(beginCoord > endCoord)
		{
			upstreamCoord.append(endCoord);
			downstreamCoord.append(beginCoord);
			dirs.append(LEFT);	
		}
		else
		{
			upstreamCoord.append(beginCoord);
			downstreamCoord.append(endCoord);
			dirs.append(RIGHT);
		}
			
		ids.append(hsps->getElement(i, idId));
		
		position.append(i);
		
		//upstreamCoord.append(hsps->getElement(i,upstreamId).toInt() - minUpstream);
		//downstreamCoord.append(hsps->getElement(i,downstreamId).toInt() - minUpstream);
		
		//prodUpstreamCoord.append(hsps->getElement(i,"sstart").toInt() - minUpstreamProduct);
		//prodDownstreamCoord.append(hsps->getElement(i,"send").toInt() - minUpstreamProduct);
	}

	size = hsps->numHSPs();
	
	sort();
	
	//invert position
	unsigned tempPosition[size];
	
	for(unsigned i = 0; i < size; i++)
	{
		tempPosition[position[i]] = i;
	}
	
	for(unsigned i = 0; i < size; i++)
	{
		position[i] = tempPosition[i];
	}
	
}

unsigned HspLoci::smallestValue(HSPs *hsps, QString id)
{
	unsigned minValue = hsps->getElement(0, id).toInt();
	
	for(unsigned i = 0; i < hsps->numHSPs(); ++i)
	{
		unsigned currentValue = hsps->getElement(i,id).toInt();
		if(currentValue < minValue)
		{
			minValue = currentValue;
		}
	}
	
	return minValue;
}

unsigned HspLoci::largestValue(HSPs *hsps, QString id)
{
	unsigned maxValue = hsps->getElement(0, id).toInt();
	for(unsigned i = 0; i < hsps->numHSPs(); ++i)
	{
		unsigned currentValue = hsps->getElement(i,id).toInt();
		if(currentValue > maxValue)
		{
			maxValue = currentValue;
		}
	}
	
	return maxValue;

}

unsigned HspLoci::uCoord(unsigned index)
{
	return upstreamCoord[index];
}

unsigned HspLoci::dCoord(unsigned index)
{
	return downstreamCoord[index];
}

QString HspLoci::id(unsigned index)
{
	return ids[index];
}

void HspLoci::sort()
{
	bool change = true;
	unsigned numberSwap;
	QString stringSwap;
	while(change == true)
	{
		change = false;
		for(int i = 0; i < ids.size() - 1; ++i)
		{
			if(upstreamCoord[i] > upstreamCoord[i + 1])
			{
				numberSwap = upstreamCoord[i];
				upstreamCoord[i] = upstreamCoord[i + 1];
				upstreamCoord[i + 1] = numberSwap;
				
				numberSwap = downstreamCoord[i];
				downstreamCoord[i] = downstreamCoord[i + 1];
				downstreamCoord[i + 1] = numberSwap;
				
				stringSwap = ids[i];
				ids[i] = ids[i+1];
				ids[i + 1] = stringSwap;
				
				numberSwap = position[i];
				position[i] = position[i + 1];
				position[i + 1] = numberSwap;
				
				change = true;
			}
		}
	}
}

unsigned HspLoci::getSize()
{
	return size;
}

Direction HspLoci::dir(unsigned index)
{
	return dirs[index];
}

unsigned HspLoci::pos(unsigned index)
{
	return position[index];
}

unsigned HspLoci::contigSize(QString contigName)
{
	unsigned maxValue = dCoord(0);
	
	for(unsigned i = 0; i < size; ++i)
	{
		if( (contigName == id(i))&&(dCoord(i) > maxValue) ) maxValue = dCoord(i);
	}
	
	return maxValue;
}

void HspLoci::print()
{
	for(unsigned i = 0; i < size; ++i)
	{
		qDebug() << "contig name = " << id(i) << " U = " << uCoord(i) << " D = " << dCoord(i);
	}
}