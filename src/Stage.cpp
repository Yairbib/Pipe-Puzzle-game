#include "Stage.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include "Well.h"
#include "Sink.h"

using std::make_shared, sf::Sprite;

const float angle = 90;

Stage::Stage(std::ifstream& file, const Textures& textures, int stageNum, const sf::Vector2u& screenSize) : m_stageNum(stageNum), m_mousePresses(0), m_succeed(false)
{
	file >> m_boardSize;
	m_boardSize *= TILE_SIZE;

	//inserting tiles to net bt there specific type//
	for (float y = 0; y < m_boardSize; y += TILE_SIZE) {
		char c;  file.get(c);	//gettings 2 'end lines' of windows
		
		std::vector<std::shared_ptr<Tile>> v;
		for (float x = 0; x < m_boardSize; x += TILE_SIZE) {
			file.get(c);
			v.push_back(createTile(y, x, c, textures, screenSize));
		}
		m_board.push_back(v);
	}
	checkLegalitiy();
	setAdjacencies();
	connectTiles();
	
}

std::shared_ptr<Tile> Stage::createTile(float y, float x, const char c, const Textures &textures, const sf::Vector2u& screenSize)
{
	 m_center = sf::Vector2u((screenSize.x - m_boardSize) / 2,
								(screenSize.y - m_boardSize) / 2);
	sf::Vector2f pos(x, y);
	switch (c)
	{
	case'1': return(make_shared<Pipe>(Sprite(textures.m_pipe1.m_empty), Sprite(textures.m_pipe1.m_full), pos, 1, angle * 0, m_center));
	case'2': return(make_shared<Pipe>(Sprite(textures.m_pipe1.m_empty), Sprite(textures.m_pipe1.m_full), pos, 2, angle * 1, m_center));
	case'3': return(make_shared<Pipe>(Sprite(textures.m_pipe2.m_empty), Sprite(textures.m_pipe2.m_full), pos, 3, angle * 3, m_center));
	case'4': return(make_shared<Pipe>(Sprite(textures.m_pipe2.m_empty), Sprite(textures.m_pipe2.m_full), pos, 4, angle * 2, m_center));
	case'5': return(make_shared<Pipe>(Sprite(textures.m_pipe2.m_empty), Sprite(textures.m_pipe2.m_full), pos, 5, angle * 1, m_center));
	case'6': return(make_shared<Pipe>(Sprite(textures.m_pipe2.m_empty), Sprite(textures.m_pipe2.m_full), pos, 6, angle * 0, m_center));
	case'7': return(make_shared<Pipe>(Sprite(textures.m_pipe3.m_empty), Sprite(textures.m_pipe3.m_full), pos, 7, angle * 2, m_center));
	case'8': return(make_shared<Pipe>(Sprite(textures.m_pipe3.m_empty), Sprite(textures.m_pipe3.m_full), pos, 8, angle * 1, m_center));
	case'9': return(make_shared<Pipe>(Sprite(textures.m_pipe3.m_empty), Sprite(textures.m_pipe3.m_full), pos, 9, angle * 0, m_center));
	case'A': return(make_shared<Pipe>(Sprite(textures.m_pipe3.m_empty), Sprite(textures.m_pipe3.m_full), pos, 10, angle * 3, m_center));
	case'B': m_sinks.push_back(make_shared<Sink>(Sprite(textures.m_sink_LD.m_empty), Sprite(textures.m_sink_LD.m_full), pos, 1, m_center));
		return m_sinks[m_sinks.size() - 1];
	case'C':m_sinks.push_back(make_shared<Sink>(Sprite(textures.m_sink_RD.m_empty), Sprite(textures.m_sink_RD.m_full), pos, 2, m_center));
		return m_sinks[m_sinks.size() - 1];
	case'D': m_wells.push_back(make_shared<Well>(Sprite(textures.m_well_L), pos, 1, m_center));
		return m_wells[m_wells.size() - 1];
	case'E': m_wells.push_back(make_shared<Well>(Sprite(textures.m_well_R), pos, 2, m_center));
		return m_wells[m_wells.size() - 1];
	default:
	std::string s("Character not allowed!\n");
	throw s;
	}
}

void Stage::checkLegalitiy()
{
	std::string s = "Error Readin stages from file!\n";
	for (auto i : m_board)
		if (i.size() != m_board.size())
			throw s;
}

float getRandRotation() {
	auto r = rand() % 3 + 1;
	switch (r)
	{
	case 1: return 90.f;
	case 2: return 270.f;
	case 3: return 180.f;
	};
	return 0.f;//keep compiler happy...(;
}

void Stage::mixBoard()
{
	srand((unsigned int)time(0));
	for (auto& i : m_board)
		for (auto& j : i) 
			j->rotate((int)getRandRotation());
}

void Stage::setAdjacencies()
{
	for(int i=0; i<m_board.size(); i++)
		for (int j = 0; j < m_board.size(); j++)
		{
			if (!i)//first line//
				m_board[i][j]->m_adjacencyList.m_up.m_ptr = NULL;
			else
				m_board[i][j]->m_adjacencyList.m_up.m_ptr = m_board[static_cast<__int64>(i) - 1][j];
			if (i == m_board.size() - 1)//last line//
				m_board[i][j]->m_adjacencyList.m_down.m_ptr = NULL;
			else
				m_board[i][j]->m_adjacencyList.m_down.m_ptr = m_board[static_cast<__int64>(i) + 1][j];
			if (!j)//first col//
				m_board[i][j]->m_adjacencyList.m_left.m_ptr = NULL;
			else
				m_board[i][j]->m_adjacencyList.m_left.m_ptr = m_board[i][static_cast<__int64>(j) - 1];
			if (j == m_board.size() - 1)//last col//
				m_board[i][j]->m_adjacencyList.m_right.m_ptr = NULL;
			else
				m_board[i][j]->m_adjacencyList.m_right.m_ptr = m_board[i][static_cast<__int64>(j) + 1];
		}
}

void Stage::run(sf::RenderWindow& window, const sf::Sprite& bg)
{
	while (window.isOpen()) {
		
		sf::Event e;
		if (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
				exit(0);
			}
			getMove(window, e);
			connectTiles();
			emptyAll();
			handlWaterDFS();
			if (m_succeed) {
				m_succeed = false;//for next time
				m_mousePresses = 0;
				return;
			}
			display(window, bg);
		}
	}
}

std::shared_ptr<Tile> Stage::getTilePressed(const sf::Vector2f& pos)
{
	for (auto i : m_board)
		for (auto j : i)
			if (j->containesPos(pos))
				return j;
	return NULL;//keep compiler happy...(;
}

void Stage::getMove(sf::RenderWindow& window, const sf::Event &e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i tmp = sf::Mouse::getPosition(window);
		sf::Vector2f pos((float)tmp.x, (float)tmp.y); //keep compiler happy
		if (outOfBoard(pos))	return;
		auto TilePressed = getTilePressed(pos);
		TilePressed->rotate(e);
		m_mousePresses++;
	}
}

void Stage::connectTiles()
{
	for (int i = 0; i < m_board.size(); i++)
		for (int j = 0; j < m_board.size(); j++) 
			connectTileToAdjs(i, j);	
}

void Stage::connectTileToAdjs(const int i, const int j)
{ 
	m_board[i][j]->m_adjacencyList.m_up.m_connected = (i > 0 && m_board[i][j]->m_adjacencyList.m_up.m_open && m_board[static_cast<__int64>(i) - 1][j]->m_adjacencyList.m_down.m_open) ? true : false;
	m_board[i][j]->m_adjacencyList.m_down.m_connected = (i < m_board.size() - 1 && m_board[i][j]->m_adjacencyList.m_down.m_open && m_board[static_cast<__int64>(i) + 1][j]->m_adjacencyList.m_up.m_open) ? true : false;
	m_board[i][j]->m_adjacencyList.m_right.m_connected = (j < m_board.size()-1 && m_board[i][j]->m_adjacencyList.m_right.m_open && m_board[i][static_cast<__int64>(j) +1]->m_adjacencyList.m_left.m_open) ? true : false;
	m_board[i][j]->m_adjacencyList.m_left.m_connected = (j > 0 && m_board[i][j]->m_adjacencyList.m_left.m_open && m_board[i][static_cast<__int64>(j) -1]->m_adjacencyList.m_right.m_open) ? true : false;
}

void Stage::handlWaterDFS()
{
	//fillinig on water from every well:
	for (auto& i : m_wells) 
	{
		i->m_full = true;
		fillOn(i->getConnectList());
	}
	//check if all sinks are full//
	for (auto i : m_sinks)
		if (!i->m_full)
			return;
	//if got here: all sinks full
	m_succeed = true;
}

void Stage::fillOn(vector<shared_ptr<Tile>> list)
{
	for (auto& i : list) 
	{
		if (i->m_full)	continue;
		i->m_full = true;
		fillOn(i->getConnectList());
	}
}

bool Stage::outOfBoard(const sf::Vector2f pos)
{
	 return ((pos.x >= m_boardSize + m_center.x) || (pos.y >= m_boardSize + m_center.y) 
			|| pos.x <m_center.x || pos.y< m_center.y) 
		 ? true : false; 
}

void Stage::emptyAll()
{
	for (auto& i : m_board)
		for (auto& j : i)
			j->m_full = false;
}

void Stage::display(sf::RenderWindow& window, const sf::Sprite& bg)
{
	auto frame = sf::RectangleShape(sf::Vector2f((float)m_boardSize + 40, (float)m_boardSize + 40));
	frame.setPosition((float)m_center.x - 20, (float)m_center.y - 20);
	frame.setFillColor(sf::Color::Blue);
	window.draw(bg);
	window.draw(frame);
	for (auto i : m_board)
		for (auto j : i)
			j->draw(window);
	std::string s = "Mouse Tapping: ";
	s += std::to_string(m_mousePresses);
	m_text.m_string.setString(s);
	m_text.m_string.setPosition(20.f, ((float)m_boardSize + m_center.y) -300);
	window.draw(m_text.m_string);
	window.display();
}
