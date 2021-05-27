#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <fstream>

void Controller::run()
{
    Textures textures;
    std::ifstream file("Board.txt");
    auto window = sf::RenderWindow(sf::VideoMode::getDesktopMode(), "The Pipe Puzzle Game", sf::Style::Default);
    setMenu(window, textures);
    for (float i = 0; i < 2; i++)
        m_stages.push_back(std::make_shared<Stage>(file, textures, i, window.getSize()));
   
        while (window.isOpen())
        {
            displayStart(window);
            m_stages[static_cast<__int64>(m_stageNum) - 1]->mixBoard();
            m_stages[static_cast<__int64>(m_stageNum) - 1]->run(window, m_menu.m_background);
            displayEndStage(window);
        }
       
    
    //   window.create(sf::VideoMode::getDesktopMode(), "The Pipe Puzzle Game", sf::Style::Default);
 //  }
}

void Controller::setMenu(sf::RenderWindow& window, const Textures &textures)
{
    m_menu.m_background = sf::Sprite(textures.m_bg);
    m_menu.m_nextS= sf::Sprite(textures.m_nextS);
    m_menu.m_easy= sf::Sprite(textures.m_easy);
    m_menu.m_hard= sf::Sprite(textures.m_hard);
    m_menu.m_solved = sf::Sprite(textures.m_end);
    m_menu.m_easy.setPosition((window.getSize().x - m_menu.m_easy.getGlobalBounds().width) / 2, (window.getSize().y - m_menu.m_easy.getGlobalBounds().height) / 2 - 150);
    m_menu.m_hard.setPosition(m_menu.m_easy.getPosition().x,m_menu.m_easy.getPosition().y + 150);
    m_menu.m_solved.setPosition((window.getSize().x - m_menu.m_solved.getGlobalBounds().width) / 2, (window.getSize().y - m_menu.m_solved.getGlobalBounds().height) / 2 - 150);
    m_menu.m_nextS.setPosition(m_menu.m_solved.getPosition().x + 200, m_menu.m_solved.getPosition().y + 500);
}

void Controller::displayStart(sf::RenderWindow& window)
{
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }
            window.clear();
            window.draw(m_menu.m_background);
            window.draw(m_menu.m_easy);
            window.draw(m_menu.m_hard);
            window.display();
            if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
            {
                auto tmp = sf::Mouse::getPosition(window);
                sf::Vector2f pos((float)tmp.x, (float)tmp.y);
                if (m_menu.m_easy.getGlobalBounds().contains(pos))
                    m_stageNum=1;
                else if(m_menu.m_hard.getGlobalBounds().contains(pos))
                    m_stageNum = 2;
                return;
            }
        }
    }
}

void Controller::displayEndStage(sf::RenderWindow& window)
{
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }

            window.clear();
            window.draw(m_menu.m_background);
            window.draw(m_menu.m_solved);
            window.draw(m_menu.m_nextS);
            window.display();
            if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
            {
                auto tmp = sf::Mouse::getPosition(window);
                sf::Vector2f pos((float)tmp.x, (float)tmp.y);
                if (m_menu.m_nextS.getGlobalBounds().contains(pos))
                    return;
            }
        }
    }
}

