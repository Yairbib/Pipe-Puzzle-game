#include "Pipe.h"

Pipe::Pipe(const sf::Sprite emptyTx, const sf::Sprite fullTx, const sf::Vector2f& pos, const int t, const float angle, sf::Vector2u center)
	: Fillable(emptyTx, fullTx, pos, t, center) , m_angle(angle)
{
		m_emptySprite.rotate(angle);
		m_sprite.rotate(angle); 
		setInitOpens();
}

void Pipe::rotate(const sf::Event &e)
{
	if (e.key.code == sf::Mouse::Left) 
		rotate(90);
	
	else if (e.key.code == sf::Mouse::Right)
		rotate(-90);
}

void Pipe::rotate(const int deg)
{
	m_angle += deg;
	if (m_angle == 360) m_angle = 0;
	if (m_angle == 450) m_angle = 90;
	if (m_angle == 540) m_angle = 180;
	if (m_angle == -90)	m_angle = 270;
	//if (m_angle == -180)	m_angle = 180;
	m_sprite.rotate(deg);
	m_emptySprite.rotate(deg);
	setAdjsAfterMove();
}

void Pipe::setInitOpens()
{
	switch (m_type)
	{
	case 1: 
		m_adjacencyList.m_left.m_open = m_adjacencyList.m_right.m_open = true;
		m_adjacencyList.m_down.m_open = m_adjacencyList.m_up.m_open = false;
		  break;
	case 2: 
		m_adjacencyList.m_left.m_open = m_adjacencyList.m_right.m_open = false;
		m_adjacencyList.m_down.m_open = m_adjacencyList.m_up.m_open = true;  
		m_type = 1;//set pipe type to general type of shape - after initialzation no more need for specific type of directed shape
		break;
	case 3:
		m_adjacencyList.m_left.m_open = true; m_adjacencyList.m_right.m_open = false;
		m_adjacencyList.m_down.m_open = true; m_adjacencyList.m_up.m_open = false;
		m_type = 2;
		break;
	case 4:
		m_adjacencyList.m_left.m_open = false; m_adjacencyList.m_right.m_open = true;
		m_adjacencyList.m_down.m_open = true; m_adjacencyList.m_up.m_open = false;
		m_type = 2;
		break;
	case 5:
		m_adjacencyList.m_left.m_open = false; m_adjacencyList.m_right.m_open = true;
		m_adjacencyList.m_down.m_open = false; m_adjacencyList.m_up.m_open = true;
		m_type = 2;
		break;
	case 6:
		m_adjacencyList.m_left.m_open = true; m_adjacencyList.m_right.m_open = false;
		m_adjacencyList.m_down.m_open = false; m_adjacencyList.m_up.m_open = true;
		m_type = 2;
		break;
	case 7:
		m_adjacencyList.m_left.m_open = true; m_adjacencyList.m_right.m_open = true;
		m_adjacencyList.m_down.m_open = true; m_adjacencyList.m_up.m_open = false;
		m_type = 3;
		break;
	case 8:
		m_adjacencyList.m_left.m_open = false; m_adjacencyList.m_right.m_open = true;
		m_adjacencyList.m_down.m_open = true; m_adjacencyList.m_up.m_open = true;
		m_type = 3;
		break;
	case 9:
		m_adjacencyList.m_left.m_open = true; m_adjacencyList.m_right.m_open = true;
		m_adjacencyList.m_down.m_open = false; m_adjacencyList.m_up.m_open = true;
		m_type = 3;
		break;
	case 10:
		m_adjacencyList.m_left.m_open = true; m_adjacencyList.m_right.m_open = false;
		m_adjacencyList.m_down.m_open = true; m_adjacencyList.m_up.m_open = true;
		m_type = 3;
	}
}

void Pipe::setAdjsAfterMove()
{
	switch (m_type)
	{
	case 1: turnPipe1();	break;
	case 2: turnPipe2();	break;
	case 3: turnPipe3();	
	}
}

void Pipe::turnPipe1()
{
	if (m_angle == 0 || m_angle == 180)
	{
		m_adjacencyList.m_left.m_open = m_adjacencyList.m_right.m_open = true;
		m_adjacencyList.m_up.m_open = m_adjacencyList.m_down.m_open = false;
	}
	else
	{
		m_adjacencyList.m_left.m_open = m_adjacencyList.m_right.m_open = false;
		m_adjacencyList.m_up.m_open = m_adjacencyList.m_down.m_open = true;
	}
}

void Pipe::turnPipe2()
{
	switch (m_angle)
	{
	case 0: m_adjacencyList.m_left.m_open = m_adjacencyList.m_up.m_open = true;
		m_adjacencyList.m_right.m_open = m_adjacencyList.m_down.m_open = false;	break;
	case 90: m_adjacencyList.m_right.m_open = m_adjacencyList.m_up.m_open = true;
		m_adjacencyList.m_left.m_open = m_adjacencyList.m_down.m_open = false;	break;
	case 180: m_adjacencyList.m_right.m_open = m_adjacencyList.m_down.m_open = true;
		m_adjacencyList.m_left.m_open = m_adjacencyList.m_up.m_open = false;	break;
	case 270: m_adjacencyList.m_left.m_open = m_adjacencyList.m_down.m_open = true;
		m_adjacencyList.m_right.m_open = m_adjacencyList.m_up.m_open = false;	
	}
}

void Pipe::turnPipe3()
{
	switch (m_angle)
	{
	case 0: m_adjacencyList.m_left.m_open = m_adjacencyList.m_right.m_open = m_adjacencyList.m_up.m_open = true;
		 m_adjacencyList.m_down.m_open = false;	break;
	case 90: m_adjacencyList.m_right.m_open = m_adjacencyList.m_up.m_open = m_adjacencyList.m_down.m_open = true;
		m_adjacencyList.m_left.m_open = false;	break;
	case 180: m_adjacencyList.m_right.m_open = m_adjacencyList.m_left.m_open = m_adjacencyList.m_down.m_open = true;
		m_adjacencyList.m_up.m_open = false;	break;
	case 270: m_adjacencyList.m_left.m_open = m_adjacencyList.m_down.m_open = m_adjacencyList.m_up.m_open = true;
		m_adjacencyList.m_right.m_open = false;	break;
	}
}



