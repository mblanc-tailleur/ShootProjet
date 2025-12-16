#pragma once
#include "SDL.h"
#include "FilledCircle.h"
#include "SmallShooter.h"

void SmallShooter::Draw(SDL_Renderer* renderer)
{
	FilledCircle c(m_width);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	c.SetPosition(m_x, m_y);
	c.Draw(renderer);
}



