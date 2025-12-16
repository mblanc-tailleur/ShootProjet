#pragma once
#include "Geometry.h"
#include "Projectile.h"
#include <vector>

class Entity : public Geometry
{
	public:
		std::vector<Projectile> Shoots;
		long double ReloadTime = 1;

		int HP = 1;

		Entity(int w, int h, int hp);

		void Draw(SDL_Renderer* renderer);

};