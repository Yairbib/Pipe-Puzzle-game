#pragma once
#include "Stage.h"

struct Menu {
	sf::Sprite m_background;
	sf::Sprite m_nextS;
	sf::Sprite m_easy;
	sf::Sprite m_hard;
	sf::Sprite m_solved;
};

class Controller {
public:
	void run();
	void setMenu(sf::RenderWindow& window, const Textures& textures);
	void displayStart(sf::RenderWindow &window);
	void displayEndStage(sf::RenderWindow &window);
private:
	vector<std::shared_ptr<Stage>> m_stages;
	Menu m_menu;
	int m_stageNum=0;
};