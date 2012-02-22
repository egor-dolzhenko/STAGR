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
#include "sequenceView.h"

SequenceView::SequenceView(QWidget* parent, HspLoci *hspLoci, QString newSequence//, int newSequenceLength//, int newnumberAlignments, 
						   //int* newMatchesStart, int* newMatchesEnd, QString *annotation, QVector<Direction> *newAlignmentsDirection
						   )
	:QGraphicsView(parent)
{
	
	hsps = hspLoci;
	
	//references to arrays containing alignment coordinates
	sequenceLength = hspLoci->span() + 1; //don't need to copy
	numberAlignments = hspLoci->getSize();//newnumberAlignments; // //newnumberAlignments don't need to copy
	//qDebug() << "numberAlignments = " << numberAlignments;
	
	//matchesStart = new int[numberAlignments];
	//matchesEnd = new int[numberAlignments];
	//matchNames = new QString[numberAlignments];
	
	//for(unsigned i = 0; i < numberAlignments; ++i)
	//{
	//	matchNames[i] = annotation[i];
	//	matchesStart[i] = newMatchesStart[i]; //need to copy
	//	matchesEnd[i] = newMatchesEnd[i]; //need to copy
	//}	

	
	sequence = newSequence; //don't need to copy
	//alignmentsDirection = newAlignmentsDirection; //need to copy

	//width of each nucleotide
	nucleotideWidth = 7;
	
	//setup scene
	scene = new QGraphicsScene(this);
	setAlignment(Qt::AlignCenter);
	setRenderHints(QPainter::Antialiasing|
				   QPainter::TextAntialiasing);
	setScene(scene);
	
	
	//timer is used for disabling display 
	//of nucleotide sequence during resizing
	timer = new QTimer(this);
	timer->setInterval(100);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
	timerIterations = 0;
	showNucleotides = true;
	windowHeight = 0;
	windowWidth = 0;
	alwaysShowNucleotides = true;
	
	
	
}

void SequenceView::createScene(int width, int height)
{
	//each track gets only one match at any given time
	int alignmentTracks[numberAlignments];
	
	//loci of the end of the track; useful to determine when a track becomes free so that
	//another match can use it
	int tracksEnd[numberAlignments];
	
	//stores index of the highest track; useful to know when drawing the main sequence
	int maxTrackIndex = 0;
	
	//initialization of both arrays
	for(int i = 0; i < numberAlignments; i++)
	{
		alignmentTracks[i] = 0;
		tracksEnd[i] = 0;
	}
	
	//the following two nested loops assign tracks to alignments
	
	//for every alignment
	for(int matchIndex = 0; matchIndex < numberAlignments; matchIndex++)
	{
		//check every track
		for(int trackIndex = 0; trackIndex < numberAlignments; trackIndex++)
		{
			//until find track that ends before this match starts
			if(tracksEnd[trackIndex] <= hsps->uCoord(matchIndex)) //matchesStart[matchIndex]
			{
				//in this case assign the track to the current match
				alignmentTracks[matchIndex] = trackIndex;
				//and update the end of the track to be same as end of the match
				tracksEnd[trackIndex] = hsps->dCoord(matchIndex); //matchesEnd[matchIndex]
				//further, if track index is the highest seen so far, update
				//maxTrackIndex with it
				if(trackIndex > maxTrackIndex) maxTrackIndex = trackIndex;
				break;
			}
		}
	}
	
	Block *block;
	BlockType blockType;
	

	// how many nucleotides will fit in each row
	int nucleotidesPerRow = width/nucleotideWidth;
	
	
	// required number of rows (each row consisit of spacers, tracks, and reference sequence) (rename rowsForMainSequence)
	int numRows = sequenceLength / nucleotidesPerRow;

	// if sequenceLength % width != 0 need an extra row 
	if (sequenceLength % nucleotidesPerRow != 0) numRows++;
	
	// height of an individual track
	int trackHeight = 20;
	
	// height of a sequence
	int sequenceHeight = 20;
	
	// space between tracks
	int gapBetweenTracks = 5;
	
	// to be used as y coordinate in placing blocks
	int currentHeight = 0;
	
	//row height
	int rowHeight = trackHeight*(maxTrackIndex + 1) + sequenceHeight + 
					gapBetweenTracks*(maxTrackIndex + 2);
	
	QFont font1("Monospace");
	font1.setStyleHint(QFont::TypeWriter);
	setFont(font1);
	
	QString firstRow = sequence.mid(0, nucleotidesPerRow);
	
	font1 = setFontSize(nucleotideWidth, nucleotidesPerRow, firstRow, font1);
	QGraphicsSimpleTextItem *text2;

	
	//ACTGACTGACTGACTGACTGACTGACTGACTGACTGACTGACTGACTGACTGACTGACTGACTG
	//1 -------------------------------------------------------------60
	//61 -----------------------------------------------------------120
	//121 ----------------------------------------------------------180
	
	// match 1 thru 20  
	
	//for each row consider all possible matches and determine whether any
	//blocks should be placed
	for(int rowIndex = 0; rowIndex < numRows; rowIndex++)
	{
		for(int matchIndex = 0; matchIndex < numberAlignments; matchIndex++)
		{
				
			//color of the current match
			QColor color = colorForMatchIndex(matchIndex);
			
			//index of the first nucleotide in the current row
			int rowBegin = rowIndex*nucleotidesPerRow + 1;
			
			//index of the last nucleotide in the current row
			int rowEnd = (rowIndex + 1)*nucleotidesPerRow;
			
			//index of the first nucleotide in the match
			int matchStart = hsps->uCoord(matchIndex); //matchesStart[matchIndex]
			
			//index of the last nucleotide in the match
			int matchEnd = hsps->dCoord(matchIndex); //matchesEnd[matchIndex]
			
			//change index to make sure track with smaller index is closer to the
			//sequence (change later)
			int currentTrack = maxTrackIndex - alignmentTracks[matchIndex];
			
			//use current track index to calculate the current track height
			int currentTrackHeight = rowHeight*rowIndex + currentTrack*(trackHeight+gapBetweenTracks)
								     + gapBetweenTracks;
			
			//begins before this row but ends in this row
			if( (matchStart < rowBegin) && 
				(rowBegin <= matchEnd ) && (matchEnd <= rowEnd)  )
			{
				if(hsps->dir(matchIndex) == LEFT) blockType = BLOCK_INCOMPLETE_LEFT; //(*alignmentsDirection)[matchIndex]
				else blockType = BLOCK_POINT_RIGHT_INCOMPLETE;
				
				block = new Block((matchEnd - rowBegin + 1)*nucleotideWidth,
								   trackHeight, blockType, color);
				block->setPos(QPoint(0,currentTrackHeight));
				scene->addItem(block);
				Annotate(0,currentTrackHeight, (matchEnd - rowBegin + 1)*nucleotideWidth, trackHeight, matchIndex);
			}
			//begins and ends in this row
			else if ( (rowBegin <= matchStart) && ( matchEnd <= rowEnd ) )
			{
				if(hsps->dir(matchIndex) == LEFT) blockType = BLOCK_POINT_LEFT; //(*alignmentsDirection)[matchIndex]
				else blockType = BLOCK_POINT_RIGHT;

				block = new Block((matchEnd - matchStart + 1)*nucleotideWidth,
								  trackHeight, blockType, color);
				block->setPos(QPoint((matchStart - rowBegin)*nucleotideWidth, currentTrackHeight));
				scene->addItem(block);
				Annotate((matchStart - rowBegin)*nucleotideWidth, currentTrackHeight, (matchEnd - matchStart + 1)*nucleotideWidth, trackHeight, matchIndex);
			}
			//begins in this row but does not end in it
			else if ( (rowBegin <= matchStart) && ( matchStart <= rowEnd )
					  && (rowEnd < matchEnd) )
			{
				if(hsps->dir(matchIndex) == LEFT) blockType = BLOCK_POINT_LEFT_INCOMPLETE; //(*alignmentsDirection)[matchIndex]
				else blockType = BLOCK_INCOMPLETE_RIGHT;

				block = new Block((rowEnd - matchStart  + 1)*nucleotideWidth, trackHeight, blockType, color );
				block->setPos(QPoint((matchStart-rowBegin)*nucleotideWidth,currentTrackHeight));
				scene->addItem(block);
				Annotate((matchStart - rowBegin)*nucleotideWidth,currentTrackHeight, (rowEnd - matchStart  + 1)*nucleotideWidth, trackHeight, matchIndex);
				
			}
			//begins before this row and ends after this row
			else if ( (matchStart < rowBegin) && (rowEnd < matchEnd) )
			{
				block = new Block(nucleotidesPerRow*nucleotideWidth, 
								  trackHeight, BLOCK_INCOMPLETE_LEFT_RIGHT , color); //
				block->setPos(QPoint(0, currentTrackHeight));
				scene->addItem(block);
				Annotate(0,currentTrackHeight,nucleotidesPerRow*nucleotideWidth,trackHeight, matchIndex);
			}
		}
		
		int currentSequenceHeight = rowHeight*(rowIndex + 1) - sequenceHeight;

		if(rowIndex != numRows - 1)
		{
			block = new Block((nucleotidesPerRow)*nucleotideWidth, sequenceHeight, BLOCK, Qt::white);
			block->setPos(QPoint(0,currentSequenceHeight));
			scene->addItem(block);
	
			if( (showNucleotides)&&(alwaysShowNucleotides) )
			{
				text2 = new QGraphicsSimpleTextItem();
				text2->setText(sequence.mid(rowIndex*nucleotidesPerRow, nucleotidesPerRow)); //QString( )
				text2->setFont(font1);
				text2->setPos(2,currentSequenceHeight + (sequenceHeight - text2->boundingRect().height())/2); //sequenceHeight/4
				scene->addItem(text2);
			}


		}
		else
		{
			block = new Block((sequenceLength - (numRows - 1)*nucleotidesPerRow)*nucleotideWidth, sequenceHeight, BLOCK, Qt::white);
			block->setPos(QPoint(0,currentSequenceHeight));
			scene->addItem(block);
			if( (showNucleotides)&&(alwaysShowNucleotides) )
			{
				text2 = new QGraphicsSimpleTextItem();
				text2->setText(sequence.mid(rowIndex*nucleotidesPerRow, sequenceLength - (numRows - 1)*nucleotidesPerRow));
				text2->setFont(font1);
				text2->setPos(2, currentSequenceHeight + (sequenceHeight - text2->boundingRect().height())/2);
				scene->addItem(text2);	
			}	
		}		
	}
	scene->setSceneRect(-10, 0, width + 10, rowHeight*numRows + gapBetweenTracks);
}

void SequenceView::clearScene()
{
	QList<QGraphicsItem *> list = scene->items();
	QList<QGraphicsItem *>::Iterator iterator = list.begin();
	for ( ; iterator != list.end(); ++iterator)
	{
		if ( *iterator )
		{
			scene->removeItem(*iterator);
			delete *iterator;
		}
	}
}

void SequenceView::resizeEvent(QResizeEvent* event)
{
	timer->stop();
	timer->start();
	showNucleotides = false;
		
	clearScene();
	createScene(event->size().width()-70, event->size().height() - 150);
	windowWidth = event->size().width()-70;
	windowHeight = event->size().height()-150;
	QGraphicsView::resizeEvent(event);
}

QColor SequenceView::colorForMatchIndex(int index)
{
	QColor colors[5];
	colors[0] = QColor(255, 77, 65);
	colors[1] = QColor(242, 147, 31);
	colors[2] = QColor(229, 202, 33);
	colors[3] = QColor(145, 178, 33);
	colors[4] = QColor(30, 140, 101);
	
	return colors[index % 5];
}

void SequenceView::Annotate(int x, int y, int width, int height, int matchIndex)
{
	
	QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(hsps->id(matchIndex)); //matchNames[matchIndex]
	text->setPos(x + 3, y + (height - text->boundingRect().height())/2);
	if((x + 3 + text->boundingRect().width()) <= x + width) scene->addItem(text);
}

QFont SequenceView::setFontSize(int nucleotideWidth, int nucleotidesPerRow, QString firstRow, QFont font1)
{
	float factor = (float)nucleotideWidth / (float)fontMetrics().width('A');
	QFont f("Monospace");
	f.setStyleHint(QFont::TypeWriter);
	f.setPointSizeF(f.pointSizeF()*factor);
	setFont(f);
	f.setLetterSpacing(QFont::AbsoluteSpacing, (float)(nucleotideWidth*nucleotidesPerRow - fontMetrics().width(firstRow) - 3)/(float)firstRow.length());
	return f;
}

void SequenceView::timerSlot()
{
	showNucleotides = true;
	clearScene();
	createScene(windowWidth, windowHeight);
}

void SequenceView::keyPressEvent(QKeyEvent *event)
{
	if( (event->key() == Qt::Key_Equal) && (event->modifiers() == Qt::ControlModifier) ) 
	{ 
	  if( nucleotideWidth >= 8) alwaysShowNucleotides = true;
	  if( nucleotideWidth <= 11)
	  {
	    nucleotideWidth++; resizeEvent(&QResizeEvent(size(), size()));
	  }
	}
	if( (event->key() == Qt::Key_Minus) && (event->modifiers() == Qt::ControlModifier) )  
	{
	  
	  if(nucleotideWidth < 8)
	  {
	  	alwaysShowNucleotides = false;
	  }
	  
	  if( nucleotideWidth > 1) 
	  {
	    nucleotideWidth--; 
	    resizeEvent(&QResizeEvent(size(), size()));
	  }
	}	
}

