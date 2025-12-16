#pragma once
#include <random>
#include "Entity.h"

using namespace std;

class SmallShooter : public Entity
{
	public:

		SmallShooter(int x, int r, int hp) : Entity(x, r, hp)
		{
			random_device rd;
			mt19937 gen(rd());

			m_x = x;
			uniform_int_distribution<> dist(8, ((x * 9) / 16) - 8);
			m_y = dist(gen);
			HP = hp;
			m_width = r;
			m_height = r;
			std::vector<Projectile> Ennemyproj;
		};

		void Draw(SDL_Renderer* renderer) override;
		
};