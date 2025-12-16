#pragma once
#include "SDL.h"
#include "Entity.h"


Entity::Entity(int w, int h, int hp) : Geometry(m_width, m_height)
{
	m_width = w;
	m_height = h;
	HP = hp;
}


void Entity::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { m_x, m_y, m_width, m_height };

	SDL_RenderFillRect(renderer, &rect);
}