#include "stdafx.h"
#include "Node.h"

const Node invalidNode;

//------------------------------------------------
//! represents the node as a character
//  
//! @return character
//------------------------------------------------
char Node::toChar() const
{
	char character = ' ';
	if ( m_isStartNode )
	{
		character = 'A';
	}
	else if ( m_isEndNode )
	{
		character = 'B';
	}
	else if ( m_isPath )
	{
		character = '.';
	}
	else if ( m_visited )
	{
		character = 'v';
	}
	else
	{
		switch ( m_terrain )
		{
		case TerrainType::Wall:
			character = '#';
			break;
		case TerrainType::Space:
			character = ' ';
			break;
		case TerrainType::Mountain:
			character = 'M';
		}
	}

	return character;
}


//------------------------------------------------
//! tests to see if this node is impassable
//  
//! @return true if it is
//------------------------------------------------
bool Node::isImpassable() const
{
	return m_terrain == TerrainType::Wall;
}


//------------------------------------------------
//! gets the movement cost of moving on to this node
//  
//! @return cost
//------------------------------------------------
int Node::getMovementCost() const
{
	switch ( m_terrain )
	{
	case TerrainType::Mountain:
		return 3;
	case TerrainType::Space:
		return 1;
	case TerrainType::Wall:
		return 1000;
	}
	return 1;
}


//------------------------------------------------
//! clears all meta data
//------------------------------------------------
void Node::clearMetaData()
{
	m_isEndNode = false;
	m_isPath = false;
	m_isStartNode = false;
	m_visited = false;
}