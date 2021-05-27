#pragma once
#include <SFML/Graphics.hpp>

struct Shape {
	sf::Texture m_full;
	sf::Texture m_empty;
};

struct Textures {
	Textures() {
		m_well_R.loadFromFile("well_R.png");
		m_well_L.loadFromFile("well_L.png");
		m_sink_RD.m_empty.loadFromFile("sink_empty_RD.png");
		m_sink_LD.m_empty.loadFromFile("sink_empty_LD.png");
		m_sink_RD.m_full.loadFromFile("sink_full_RD.png");
		m_sink_LD.m_full.loadFromFile("sink_full_LD.png");
		m_pipe1.m_full.loadFromFile("pipe1_full.png");
		m_pipe1.m_empty.loadFromFile("pipe1_empty.png");
		m_pipe2.m_full.loadFromFile("pipe2_full.png");
		m_pipe2.m_empty.loadFromFile("pipe2_empty.png");
		m_pipe3.m_full.loadFromFile("pipe3_full.png");
		m_pipe3.m_empty.loadFromFile("pipe3_empty.png");
		m_bg.loadFromFile("background.png");
		m_nextS.loadFromFile("playMore.png");
		m_next.loadFromFile("next_stage.png");
		m_easy.loadFromFile("easy.png");
		m_hard.loadFromFile("hard.png");
		m_pre.loadFromFile("previous_stage.png");
		m_end.loadFromFile("solved.png");
	}
	sf::Texture m_well_R, m_well_L, m_bg, m_easy, m_hard, m_nextS, m_next, m_pre, m_end;
	Shape m_pipe1, m_pipe2, m_pipe3, m_sink_RD, m_sink_LD;
};