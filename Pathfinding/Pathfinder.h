#pragma once

class Map;
class MapLocation;
class Path;

class Pathfinder
{
public:
	virtual bool		findPath( Map& map, const MapLocation& startLocation, const MapLocation& endLocation, Path& path ) = 0;
};

