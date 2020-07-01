#include "stdafx.h"
#include "DijkstrasPathfinder.h"

//------------------------------------------------
//! estimates the distance from one map location to another
//  
//! @param from from location
//! @param to to location
//! @return estimate of the distance
//------------------------------------------------
int DijkstrasPathfinder::estimate( const MapLocation& /*from*/, const MapLocation& /*to*/ ) const
{
	//if we estimate 0 for the remaining distance, we test all nodes = Dijkstra's algorithm
	return 0;
}