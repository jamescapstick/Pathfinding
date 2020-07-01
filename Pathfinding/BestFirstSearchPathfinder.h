#pragma once

#include "AStarPathfinder.h"

class BestFirstSearchPathfinder : public AStarPathfinder
{
	typedef AStarPathfinder super;

protected:
	int		estimate( const MapLocation& from, const MapLocation& to ) const override;
};

