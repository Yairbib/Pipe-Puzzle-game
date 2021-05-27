#pragma once
#include <vector>
#include <Tile.h>

class Fillable : public Tile {
public:
	Fillable(const sf::Sprite emptyTx, const sf::Sprite fullTx, const sf::Vector2f& pos, const int type, sf::Vector2u center)
		: Tile(fullTx, pos, type, center), m_emptySprite(emptyTx) {
		m_emptySprite.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
		m_emptySprite.setPosition(pos.x + center.x, pos.y + center.y);
	//	m_emptySprite.setPosition(pos);
		m_emptySprite.move(OFFSET);
		//m_emptySprite.move(center);
	}
	void draw(sf::RenderWindow& w) { m_full ? w.draw(m_sprite) : w.draw(m_emptySprite); }
protected:
	sf::Sprite m_emptySprite;
	std::vector<std::shared_ptr<Tile>> m_openTo;
};

