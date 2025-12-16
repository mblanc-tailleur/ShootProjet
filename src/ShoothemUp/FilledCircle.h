#pragma once
#include "Geometry.h"


class FilledCircle : public Geometry
{
public:
	FilledCircle(short radius) : Geometry(radius * 2, radius * 2) {};

	void Draw(SDL_Renderer* renderer);

	int GetRadius() const
	{
		return m_width / 2;
	}

	void SetRadius(short w);
};

