#pragma once

#include "Node.h"

#include <filesystem>

//14 = 10 * sqrt(2)....ish
//technically this is octile distance
constexpr int DIAGONAL_DISTANCE = 14;
constexpr int ADJACENT_DISTANCE = 10;

class MapLocation;
class Path;

class Map
{
public:

	bool									load( const std::experimental::filesystem::path& filePath, MapLocation& startNode, MapLocation& endNode );

	bool									isValidLocation( const MapLocation& n ) const;
	const Node&								nodeAt( const MapLocation& n ) const;
	int										getMovementCost( const MapLocation& from, const MapLocation& to ) const;

	void									setVisited( const MapLocation& l );
	void									showPath( const Path& path );
	void									clearPath( const Path& path );
	void									clearMetaData();

	void									dump() const;
private:
	Node*									nodePtrAt( const MapLocation& n );

	std::vector<std::vector<Node>>	m_mapData;
};

