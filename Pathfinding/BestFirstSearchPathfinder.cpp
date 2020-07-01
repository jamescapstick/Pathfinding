#include "stdafx.h"
#include "BestFirstSearchPathfinder.h"

//------------------------------------------------
//! estimates the distance from one map location to another
//  
//! @param from from location
//! @param to to location
//! @return estimate of the distance
//------------------------------------------------
int BestFirstSearchPathfinder::estimate( const MapLocation& from, const MapLocation& to ) const
{
	//if we estimate a huge number for the remaining distance, we simply try to home in on the destination = Greedy Best-First-Search
	return super::estimate( from, to ) * 2000;
}