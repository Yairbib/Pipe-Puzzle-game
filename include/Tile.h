#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

using std::pair, std::shared_ptr, std::vector;
const int TILE_SIZE = 90;

enum class Dir {
	up, down, right, left,
};

const sf::Vector2f OFFSET = sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2);

class Tile {
public:
	Tile(const sf::Sprite tx, const sf::Vector2f& pos, const int type, sf::Vector2u center);
	virtual void setInitOpens()=0;
	virtual void draw(sf::RenderWindow& w) = 0;
	bool containesPos(const sf::Vector2f& pos) { const sf::Vector2f p(pos.x, pos.y); return m_sprite.getGlobalBounds().contains(p); }
	virtual void rotate(const sf::Event &e) = 0;
	virtual void rotate(const int) = 0;
	struct side{
		shared_ptr<Tile> m_ptr;
		bool m_open = false;
		bool m_connected = false;
	};
	struct adjancies {
		side m_up;
		side m_down;
		side m_right;
		side m_left;
	} m_adjacencyList;
	bool m_full;
	vector<shared_ptr<Tile>> getConnectList();
protected:
	sf::Sprite m_sprite;
	int m_type;
	int m_size;
	bool m_visited;
};