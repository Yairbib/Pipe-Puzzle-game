#include "Tile.h"

Tile::Tile(const sf::Sprite tx, const sf::Vector2f& pos, const int type, sf::Vector2u center)
	: m_sprite(tx), m_type(type), m_size(TILE_SIZE), m_visited(false), m_full(false)
{
	m_sprite.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
	m_sprite.setPosition(pos.x+center.x, pos.y+center.y);
	//m_sprite.setPosition(pos);
	m_sprite.move(OFFSET);
//	m_sprite.move(center);
}

vector<shared_ptr<Tile>> Tile::getConnectList()
{
	 vector<shared_ptr<Tile>> v;
	 if (m_adjacencyList.m_up.m_connected)	v.push_back(m_adjacencyList.m_up.m_ptr);
	 if (m_adjacencyList.m_down.m_connected)	v.push_back(m_adjacencyList.m_down.m_ptr);
	 if (m_adjacencyList.m_right.m_connected)	v.push_back(m_adjacencyList.m_right.m_ptr);
	 if (m_adjacencyList.m_left.m_connected)	v.push_back(m_adjacencyList.m_left.m_ptr);
	 return v;
}


