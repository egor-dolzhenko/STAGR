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

#include <QtGui>
#include "Table.h"

Table::Table(QWidget* parent, QStringList header, 
			QStringList* entries, int numberOfEntries)
			:QTableWidget(parent)
{
	setRowCount(numberOfEntries);
	setColumnCount(header.size());
	setAlternatingRowColors(true);
	setHorizontalHeaderLabels(header);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	//setSelectionMode(QAbstractItemView::SingleSelection);
	horizontalHeader()->setHighlightSections(false);
	for(int rowIndex = 0; rowIndex < numberOfEntries; rowIndex++)
	{
		for(int columnIndex = 0; columnIndex < entries[rowIndex].size(); columnIndex++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setText(entries[rowIndex][columnIndex]);
			setItem(rowIndex, columnIndex, item);
		}
	}
}

Table::Table(QWidget* parent, QStringList header, QVector< QMap<QString, QString> > *entries)
{
	setRowCount(entries->size());
	setColumnCount(header.size());
	setAlternatingRowColors(true);
	setHorizontalHeaderLabels(header);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	horizontalHeader()->setHighlightSections(false);
	
	for(int rowIndex = 0; rowIndex < entries->size(); rowIndex++)
	{
		for(int columnIndex = 0; columnIndex < header.size(); columnIndex++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setText(entries->at(rowIndex)[header[columnIndex]]);
			setItem(rowIndex, columnIndex, item);
		}
	}	
}

Table::Table(QWidget* parent, QStringList header, QVector<QStringList> *entries)
{
	setRowCount(entries->size());
	setColumnCount(header.size());
	setAlternatingRowColors(true);
	setHorizontalHeaderLabels(header);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	horizontalHeader()->setHighlightSections(false);
	
	for(int rowIndex = 0; rowIndex < entries->size(); rowIndex++)
	{
		for(int columnIndex = 0; columnIndex < header.size(); columnIndex++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setText(entries->at(rowIndex)[columnIndex]);
			setItem(rowIndex, columnIndex, item);
		}
	}	

}
