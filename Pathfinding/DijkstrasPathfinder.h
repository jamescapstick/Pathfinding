#pragma once

#include "AStarPathfinder.h"

class DijkstrasPathfinder :	public AStarPathfinder
{
protected:
	int		estimate( const MapLocation& from, const MapLocation& to ) const override;
};

