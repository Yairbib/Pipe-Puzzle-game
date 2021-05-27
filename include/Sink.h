#pragma once
#include <Fillable.h>

class Sink : public Fillable {
public:
	Sink(const sf::Sprite emptyTx, const sf::Sprite fullTx, const sf::Vector2f& pos, const int type, sf::Vector2u center)
		: Fillable(emptyTx, fullTx, pos, type, center){setInitOpens();}
	void setInitOpens()
	{
		if (m_type == 1)
		{
			m_adjacencyList.m_left.m_open = m_adjacencyList.m_down.m_open = true;//left down open sink
			m_adjacencyList.m_up.m_open = m_adjacencyList.m_right.m_open = false;
			return;
		}
		//else: right down opening sink
		m_adjacencyList.m_right.m_open = m_adjacencyList.m_down.m_open = true;//left down open sink
		m_adjacencyList.m_up.m_open = m_adjacencyList.m_left.m_open = false;
	}
	void rotate(const sf::Event& e) { auto garbage = e.KeyPressed; garbage = e.KeyPressed; }//keep compiler happy..//
	void rotate(const int) {}
private:
	sf::Sprite m_emptySprite;
};
