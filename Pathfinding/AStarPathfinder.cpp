#include "stdafx.h"
#include "AStarPathfinder.h"

#include "Map.h"
#include "MapLocation.h"
#include "Path.h"

#include <iostream>
#include <map>
#include <limits>
#include <queue>

class MapLocationInfo
{
public:
	MapLocation	m_parentLocation;
	int			m_gScore{ std::numeric_limits<int>::max() };
	int			m_fScore{ std::numeric_limits<int>::max() };
	bool		m_closed{ false };
};

class MapLocationInfoMap : public std::map<MapLocation, MapLocationInfo>
{
public:
	bool operator()( const MapLocation& lhs, const MapLocation& rhs )
	{
		return (*this)[lhs].m_fScore > (*this)[rhs].m_fScore;
	}
};


//------------------------------------------------
//! finds a path from start to end on the supplied map
//  
//! @param map map to use
//! @param startLocation start node
//! @param endLocation end node
//! @param path receives the found path
//! @return true if a path was found
//------------------------------------------------
bool AStarPathfinder::findPath( Map& map, const MapLocation& startLocation, const MapLocation& endLocation, Path& path )
{
	std::cout << "Using " << typeid(*this).name() << ":\n";

	//map of node to extra info on the node
	MapLocationInfoMap locationInfoMap;
	locationInfoMap[startLocation] = MapLocationInfo();
	locationInfoMap[startLocation].m_gScore = 0;
	locationInfoMap[startLocation].m_fScore = estimate( startLocation, endLocation );

	//all known nodes - just the start node to begin with
	std::vector<MapLocation> openList;
	openList.push_back( startLocation );

	size_t nodesVisited = 0;

	while ( !openList.empty() )
	{
		MapLocation currentLocation = openList[openList.size() - 1];
		auto it = locationInfoMap.find( currentLocation );

		if ( currentLocation == endLocation )
		{
			//found the last node!
			std::cout << "Finished pathfinding\n";
			std::cout << "Final movement cost: " << it->second.m_fScore << ".\n";

			path.insert( path.begin(), currentLocation );
			while ( it != locationInfoMap.end() )
			{
				currentLocation = it->second.m_parentLocation;
				if ( map.isValidLocation( currentLocation ) )
				{
					path.insert( path.begin(), currentLocation );
				}
				it = locationInfoMap.find( currentLocation );
			}
			std::cout << "We visited " << nodesVisited << " nodes.\n";
			return true;
		}

		openList.erase( openList.begin() + (openList.size() - 1) );

		//look at each neighbour
		MapLocationInfo& currentLocationInfo = it->second;
		for ( int xOffset = -1; xOffset <= 1; ++xOffset )
		{
			for ( int yOffset = -1; yOffset <= 1; ++yOffset )
			{
				//use this one if we can use diagonals
				if ( (xOffset == 0) && (yOffset == 0) )
				{
					//same node if no offset, ignore
					continue;
				}
				//use this one if we can only go to adjacent squares
				//if ( (xOffset == 0) == (yOffset == 0) )
				//{
				//	//same node if no offset, ignore
				//	continue;
				//}

				MapLocation neighbourLocation = currentLocation;
				neighbourLocation.m_x += xOffset;
				neighbourLocation.m_y += yOffset;

				const Node& neighbourNode = map.nodeAt( neighbourLocation );
				if ( neighbourNode.isImpassable() )
				{
					//can't pass through walls
					continue;
				}

				//add a default entry for this node if we don't have one
				if ( locationInfoMap.find( neighbourLocation ) == locationInfoMap.end() )
				{
					locationInfoMap[neighbourLocation] = MapLocationInfo();
				}

				if ( locationInfoMap[neighbourLocation].m_closed )
				{
					//already looked here
					continue;
				}

				//this test score is the distance from the start to the neighbour through the current node
				int testGScore = currentLocationInfo.m_gScore + map.getMovementCost( currentLocation, neighbourLocation );
				if ( testGScore < locationInfoMap[neighbourLocation].m_gScore )
				{
					//this path is better than the one we had before
					locationInfoMap[neighbourLocation].m_parentLocation = currentLocation;
					locationInfoMap[neighbourLocation].m_gScore = testGScore;
					locationInfoMap[neighbourLocation].m_fScore = testGScore + estimate( neighbourLocation, endLocation );

					if ( std::find( openList.begin(), openList.end(), neighbourLocation ) == openList.end() )
					{
						openList.push_back( neighbourLocation );
						map.setVisited( neighbourLocation );
						++nodesVisited;
					}
				}
			}
		}

		//sort the open list by f score
		std::sort( openList.begin(), openList.end(), locationInfoMap );
		currentLocationInfo.m_closed = true;
	}

	return false;
}


//------------------------------------------------
//! estimates the distance from one map location to another
//  
//! @param from from location
//! @param to to location
//! @return estimate of the distance
//------------------------------------------------
int AStarPathfinder::estimate( const MapLocation& from, const MapLocation& to ) const
{
	int xDistance = std::abs( (int)from.m_x - (int)to.m_x );
	int yDistance = std::abs( (int)from.m_y - (int)to.m_y );
	int smallestDistance = std::min( xDistance, yDistance );

	return (smallestDistance * DIAGONAL_DISTANCE) + ((xDistance - smallestDistance) * ADJACENT_DISTANCE) + ((yDistance - smallestDistance) * ADJACENT_DISTANCE);
}