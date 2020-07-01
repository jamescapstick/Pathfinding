#pragma once

#include "Pathfinder.h"


class AStarPathfinder : public Pathfinder
{
public:
	bool		findPath( Map& map, const MapLocation& startNode, const MapLocation& endNode, Path& path ) override;

protected:
	virtual int	estimate( const MapLocation& from, const MapLocation& to ) const;
};

