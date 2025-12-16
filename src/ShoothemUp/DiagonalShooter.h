#pragma once
#include <random>
#include "Entity.h"

using namespace std;

class DiagonalShooter : public Entity
{

public:
	bool up = 1;

	DiagonalShooter(int x, int r, int hp) : Entity(x, r, hp)
	{
		random_device rd;
		mt19937 gen(rd());

		m_x = x;
		uniform_int_distribution<> dist(0, x / 2);
		m_y = dist(gen);
		HP = hp;
		m_width = r;
		m_height = r;
	};

	void Draw(SDL_Renderer* renderer) override;

};