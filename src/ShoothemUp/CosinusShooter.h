#pragma once
#include <random>
#include "Entity.h"

using namespace std;

class CosinusShooter : public Entity
{

public:
	bool up = 1;

	CosinusShooter(int x, int r, int hp) : Entity(x, r, hp)
	{
		random_device rd;
		mt19937 gen(rd());

		m_x = x;
		uniform_int_distribution<> dist(50, (x / 2) - 50);
		m_y = dist(gen);
		HP = hp;
		m_width = r;
		m_height = r;
	};

	void Draw(SDL_Renderer* renderer) override;

};