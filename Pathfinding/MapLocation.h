#pragma once

#include <functional>

class MapLocation
{
public:
	MapLocation&		operator=( const MapLocation& rhs );
	bool		operator==( const MapLocation& rhs ) const;

	size_t		m_x{ std::numeric_limits<size_t>::max() };
	size_t		m_y{ std::numeric_limits<size_t>::max() };
};

bool operator<( const MapLocation& n1, const MapLocation& n2 );

