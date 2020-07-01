#include "Map.h"
#include "MapLocation.h"
#include "Path.h"
#include "Node.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>


//------------------------------------------------
//! loads a map from a file path
//  
//! @param filePath file path to load the map from
//! @param startLocation receives the information on the start location
//! @param endLocation receives data on the end location
//! @return true if successfully loaded
//------------------------------------------------
bool Map::load( const std::experimental::filesystem::path& filePath, MapLocation& startLocation, MapLocation& endLocation )
{
	bool startLocationFound = false;
	bool endLocationFound = false;
	std::ifstream mapFile( filePath );

	if ( mapFile.is_open() )
	{
		int yIndex = 0;
		for ( std::string line; std::getline( mapFile, line ); )
		{
			if ( line.length() > 0 )
			{
				m_mapData.push_back( std::vector<Node>() );

				m_mapData[yIndex].resize( line.length() );

				//parse the string into passable and impassable
				int xIndex = 0;
				for ( char mapElement : line )
				{
					Node node;
					switch ( mapElement )
					{
					case ' ':
						//found a space
						node.setTerrain( TerrainType::Space );
						break;
					case 'A':
						//found our start node
						startLocationFound = true;
						startLocation.m_x = xIndex;
						startLocation.m_y = yIndex;
						node.setTerrain( TerrainType::Space );
						break;
					case 'B':
						//found our end node
						endLocationFound = true;
						endLocation.m_x = xIndex;
						endLocation.m_y = yIndex;
						node.setTerrain( TerrainType::Space );
						break;
					default:
						//anything else is a wall
						node.setTerrain( TerrainType::Wall );
						break;
					}
					m_mapData[yIndex][xIndex++] = node;
				}
			}

			++yIndex;
		}

		if ( !startLocationFound )
		{
			std::cout << "Could not find start node in map file - need to include an A";
		}
		if ( !endLocationFound )
		{
			std::cout << "Could not find end node in map file - need to include a B";
		}
	}

	return startLocationFound && endLocationFound;
}


//------------------------------------------------
//! tests to see if a location is within the bounds on the map
//  
//! @param n location to test
//! @return true if the location is valid
//------------------------------------------------
bool Map::isValidLocation( const MapLocation& n ) const
{
	return n.m_y < m_mapData.size() && n.m_x < m_mapData[n.m_y].size();
}

//------------------------------------------------
//! gets the node at the supplied location
//  
//! @param n location to test
//! @return element
//------------------------------------------------
const Node& Map::nodeAt( const MapLocation& n ) const
{
	if ( n.m_y < m_mapData.size() && 
		 n.m_x < m_mapData[n.m_y].size() )
	{
		return m_mapData[n.m_y][n.m_x];
	}

	return invalidNode;
}

//------------------------------------------------
//! gets the node at the supplied location
//  
//! @param n location to test
//! @return element
//------------------------------------------------
Node* Map::nodePtrAt( const MapLocation& n )
{
	if ( n.m_y < m_mapData.size() &&
		 n.m_x < m_mapData[n.m_y].size() )
	{
		return &m_mapData[n.m_y][n.m_x];
	}

	return nullptr;
}

//------------------------------------------------
//! gets the movement cost to go from one location to another
//  
//! @param from from location
//! @param to to location
//! @return distance
//------------------------------------------------
int Map::getMovementCost( const MapLocation& from, const MapLocation& to ) const
{
	//check nodes are adjacent
	assert( std::abs( (int)from.m_x - (int)to.m_x ) <= 1 );
	assert( std::abs( (int)from.m_y - (int)to.m_y ) <= 1 );

	int cost = std::numeric_limits<int>::max();
	if ( std::abs( (int)from.m_x - (int)to.m_x ) <= 1 && 
		 std::abs( (int)from.m_y - (int)to.m_y ) <= 1 )
	{
		//first get distance
		if ( from.m_x != to.m_x &&
			 from.m_y != to.m_y )
		{
			cost = DIAGONAL_DISTANCE;
		}
		else
		{
			cost = ADJACENT_DISTANCE;
		}

		//multiply by terrain cost
		cost *= nodeAt( to ).getMovementCost();
	}

	return cost;
}


//------------------------------------------------
//! sets a flag to show we've visited a location
//  
//! @param l location to set the flag on
//------------------------------------------------
void Map::setVisited( const MapLocation& l )
{
	Node* node = nodePtrAt( l );
	if ( node )
	{
		node->setVisited();
	}
}

//------------------------------------------------
//! shows a path on the map
//  
//! @param path path to show
//------------------------------------------------
void Map::showPath( const Path& path )
{
	size_t count = path.size();
	for ( size_t index = 0; index < count; ++index )
	{
		const MapLocation& location = path[index];
		Node* node = nodePtrAt( location );
		if ( node )
		{
			if ( index == 0 )
			{
				node->setIsStartNode();
			}
			else if ( index == count - 1 )
			{
				node->setIsEndNode();
			}
			else
			{
				node->setIsPath();
			}
		}
	}
}

//------------------------------------------------
//! clears a path from the map
//  
//! @param path path to clear
//------------------------------------------------
void Map::clearPath( const Path& path )
{
	size_t count = path.size();
	for ( size_t index = 0; index < count; ++index )
	{
		const MapLocation& location = path[index];
		Node* node = nodePtrAt( location );
		if ( node )
		{
			node->clearMetaData();
		}
	}
}


//------------------------------------------------
//! clears any additional data we have on the nodes
//------------------------------------------------
void Map::clearMetaData()
{
	for ( size_t y = 0; y < m_mapData.size(); ++y )
	{
		for ( size_t x = 0; x < m_mapData[y].size(); ++x )
		{
			Node& node = m_mapData[y][x];
			node.clearMetaData();
		}
	}
}

//------------------------------------------------
//! dumps the map to console
//------------------------------------------------
void Map::dump() const
{
	for ( size_t y = 0; y < m_mapData.size(); ++y )
	{
		for ( size_t x = 0; x < m_mapData[y].size(); ++x )
		{
			const Node& node = m_mapData[y][x];
			char character = node.toChar();
			std::cout << character;
		}

		std::cout << '\n';
	}
}