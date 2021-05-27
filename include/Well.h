#pragma once
#include <Tile.h>

class Well : public Tile {
public:
	Well(const sf::Sprite tx, const sf::Vector2f& pos, const int type, sf::Vector2u center) : Tile(tx, pos, type, center) { setInitOpens(); }
	void setInitOpens()
	{
		if (m_type == 1)
		{
			m_adjacencyList.m_left.m_open = true;//left  open well
			m_adjacencyList.m_down.m_open = m_adjacencyList.m_up.m_open = m_adjacencyList.m_right.m_open = false;
			return;
		}
		//else: right  opening well
		m_adjacencyList.m_right.m_open = true;//left down open sink
		m_adjacencyList.m_down.m_open = m_adjacencyList.m_up.m_open = m_adjacencyList.m_left.m_open = false;
	}
	void rotate(const sf::Event& e) { auto garbage = e.key; garbage = e.key; }//keep compiler happy..//
	void rotate(const int) {}
	void draw(sf::RenderWindow& w) { w.draw(m_sprite); }
};