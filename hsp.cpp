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
		QString precursorId = hsp["precursorId"];
 		QString productId = hsp["productId"];
		if( precursorIds.contains(precursorId) && productIds.contains(productId) )
		{
			QMapIterator<QString, QString> j(hObj->hsps.at(i));
			
			QMap<QString, QString> hspCopy;// = new QMap<QString, QString>(0);
			
			while (j.hasNext())
			{
     			j.next();
     			hspCopy[j.key()] = j.value();
 			}
 			
 			hsps.append(hspCopy);
		}
		
	}
	
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


float HSPs::getAverage(QString precursorId, QString productId, QString fieldName)
{
	float sum = 0;
	unsigned numHspsFound = 0;
	
	for(unsigned i = 0; i < hsps.size(); i++)
	{
		if( (precursorId == hsps.at(i)["precursorId"]) && (productId == hsps.at(i)["productId"]) )
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
		if( (precursorId == hsps.at(i)["precursorId"]) && (productId == hsps.at(i)["productId"]) )
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
	minUpstream = smallestValue(hsps, upstreamId) - 1;
	unsigned minDonwsteam = smallestValue(hsps, downstreamId) - 1;
	if( minDonwsteam < minUpstream ) minUpstream = minDonwsteam;
	maxDownstream = largestValue(hsps, downstreamId);
	unsigned maxUpstream = largestValue(hsps, upstreamId);
	if(maxUpstream > maxDownstream) maxDownstream = maxUpstream;
	
	for(unsigned i = 0; i < hsps->numHSPs(); ++i)
	{
	
		unsigned beginCoord = hsps->getElement(i,upstreamId).toInt() - minUpstream;
		unsigned endCoord = hsps->getElement(i,downstreamId).toInt() - minUpstream;
		
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

unsigned HspLoci::span()
{
	unsigned maxD = downstreamCoord[0];
	unsigned minU = upstreamCoord[0];
	
	for(unsigned i = 0; i < size; ++i)
	{
		if(downstreamCoord[i] > maxD) maxD = downstreamCoord[i];
		if(upstreamCoord[i] < minU) minU = upstreamCoord[i];
	}
	
	return maxD - minU;
}