#include "MapLocation.h"


//------------------------------------------------
//! assignment operator
//  
//! @param rhs object to test against
//! @return ref to this
//------------------------------------------------
MapLocation& MapLocation::operator=( const MapLocation& rhs )
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;

	return *this;
}

//------------------------------------------------
//! equality operator
//  
//! @param rhs object to test against
//! @return true if the objects are equal
//------------------------------------------------
bool MapLocation::operator==( const MapLocation& rhs ) const
{
	return m_x == rhs.m_x && m_y == rhs.m_y;
}


//------------------------------------------------
//! less than operator
//  
//! @param n1 first node to compare
//! @param n2 second node to compare
//! @return true if n1 < n2
//------------------------------------------------
bool operator<( const MapLocation& n1, const MapLocation& n2 )
{
	return n1.m_x < n2.m_x || (n1.m_x == n2.m_x && n1.m_y < n2.m_y);
}