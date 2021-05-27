#pragma once
#include <SFML/System.hpp>
#include <Pipe.h>
#include <vector>
#include "Textures.h"
using std::vector, std::shared_ptr;
struct text {
	text() { m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf"); m_string.setFont(m_font); m_string.setFillColor(sf::Color::Red); m_string.setCharacterSize(50); }
	sf::Font m_font;
	sf::Text m_string;
};

class Stage {
public:
	Stage(std::ifstream& file, const Textures& textures, int stageNum, const sf::Vector2u& screenSize);
	std::shared_ptr<Tile> createTile(float y, float x, const char c, const Textures &textures, const sf::Vector2u &screenSize);
	void checkLegalitiy();
	void mixBoard();
	void setAdjacencies();
	void run(sf::RenderWindow& window, const sf::Sprite & bg);
	std::shared_ptr<Tile> getTilePressed(const sf::Vector2f& pos);
	void getMove(sf::RenderWindow& window, const sf::Event& e);
	void connectTiles();
	void connectTileToAdjs(const int i, const int j);
	void emptyAll();
	void handlWaterDFS();
	void fillOn(vector<shared_ptr<Tile>> list);
	bool outOfBoard(const sf::Vector2f pos); 
	bool m_succeed;
	size_t getBoardSize() const { return m_board.size(); }
	void display(sf::RenderWindow& window, const sf::Sprite& bg);
private:
	vector<vector<shared_ptr<Tile>>> m_board;               
	vector<shared_ptr<Tile>> m_wells;
	vector<shared_ptr<Tile>> m_sinks;
	int m_boardSize;
	int m_stageNum;
	int m_mousePresses;
	sf::Vector2u m_center;       
	text m_text;
};