#include "contigData.h"

ContigData::ContigData()
{
	
}

unsigned ContigData::max(unsigned a, unsigned b)
{
	if( a > b) return a;
	return b;
}

unsigned ContigData::min(unsigned a, unsigned b)
{
	if( a < b ) return a;
	return b;
}

bool ContigData::checkHole(int i)
{
	if( Ds[i] < Us[i + 1] ) return true;
	return false;
}

bool ContigData::checkOneU(int i, unsigned U, unsigned D)
{
	if( ( Us[i] < U )&&( Ds[i] < D ) ) return true;
	return false;
}	

bool ContigData::checkOneD(int i, unsigned U, unsigned D)
{
	if( ( U < Us[i + 1] )&&( D < Ds[i + 1] ) ) return true;
	return false;
}	

bool ContigData::checkTwoU(int i, unsigned U, unsigned D)
{
	if( ( U > max(Ds[i-1], Us[i]) )&&( D > Ds[i] ) ) return true;
	return false;
}

bool ContigData::checkTwoD(int i, unsigned U, unsigned D)
{
	if( ( U < Us[i + 1] )&&( D < min(Ds[i + 1], Us[i + 2]) ) ) return true;
	return false;
}

int ContigData::checkPosition(unsigned U, unsigned D)
{
	unsigned size = Us.size();
	
	if( size == 0 ) return 0;
	
	if( size == 1 )
	{
		if( checkOneD(-1, U, D) ) return 0;
		if( checkOneU(0, U, D) ) return 1;
		return -1;
	}
	
	//check size 0-2
	if( checkTwoD(-1, U, D) ) return 0;
	
	//check size 2-0
	if( checkTwoU(size - 1, U, D) ) return size;
	
	if( size == 2 )
	{
		//check size 1-1
		if( checkHole(0) && checkOneU(0, U, D) && checkOneD(0, U, D) )
		{
			return 1;
		}
		
		return -1;
	}
	
	//size 3 and above

	//check size 1-2
	if( checkHole(0) && checkOneU(0, U, D) && checkTwoD(0, U, D) )
	{
		return 1;
	}
	
	//check size 2-1
	if( checkHole(size - 2) && checkTwoU(size - 2, U, D) && checkOneD(size - 2, U, D) )
	{
		return size - 1;
	}

	//check size 2-2
	for(unsigned i = 1; i < size - 2; i++)
	{
		if( checkHole(i) && checkTwoU(i, U, D) && checkTwoD(i, U, D) )
		{
			return i + 1;
		}
	}
	
	return -1;
}

void ContigData::include(unsigned U, unsigned D, QColor color, int position)
{
	if(Us.size() == 0)
	{
		Us.append(U);
		Ds.append(D);
		Cols.append(color);
	}
	else
	{
		Us.insert(position, U);
		Ds.insert(position, D);
		Cols.insert(position, color);
	}
}

void ContigData::print()
{
	qDebug() << "Us = " << Us;
	qDebug() << "Ds = " << Ds;
}