#pragma once

#include <cstdint>

enum class TerrainType : std::int8_t
{
	Space = 0,
	Wall
};

class Node
{
public:
	char			toChar() const;
	bool			isImpassable() const;
	int				getMovementCost() const;

	void			setIsStartNode() { m_isStartNode = true; }
	void			setIsEndNode() { m_isEndNode = true; }
	void			setIsPath() { m_isPath = true; }
	void			setVisited() { m_visited = true; }
	void			setTerrain( TerrainType t ) { m_terrain = t; }
	void			clearMetaData();

private:
	bool			m_isStartNode{ false };
	bool			m_isEndNode{ false };
	bool			m_isPath{ false };
	bool			m_visited{ false };
	TerrainType		m_terrain{ TerrainType::Wall };
};

extern const Node invalidNode;
