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

#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include "hsp.h"

class Table : public QTableWidget
{
	Q_OBJECT
	
public:
	Table(QWidget* parent, QStringList header,
		  QStringList* entries, int numberOfEntries);
	Table(QWidget* parent, QStringList header, QVector< QMap<QString, QString> > *entries);
	Table(QWidget* parent, QStringList header, QVector<QStringList> *entries);
	Table(QWidget* parent, HSPs *hsps);//
};

#endif //TABLE_H