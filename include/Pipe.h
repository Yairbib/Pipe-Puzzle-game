#pragma once
#include <vector>
#include <Fillable.h>

class Pipe : public Fillable {
public:
	Pipe(const sf::Sprite emptyTx, const sf::Sprite fullTx, const sf::Vector2f& pos, const int pipeType, const float angle, sf::Vector2u center);
	void rotate(const sf::Event &e);
	void rotate(const int deg);
	void setInitOpens();
	void setAdjsAfterMove();
	void turnPipe1();
	void turnPipe2();
	void turnPipe3();
private:
	int m_angle;
};

