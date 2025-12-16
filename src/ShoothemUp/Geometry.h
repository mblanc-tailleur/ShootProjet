#pragma once

#include "Maths.h"

struct SDL_Renderer;

struct Color 
{
	int r;
	int g;
	int b;
	int a;
};

class Geometry
{
protected:
	float m_x;
	float m_y;
	float m_ax;
	float m_ay;
	int m_width;
	int m_height;

	


public:
	Color m_color;

	Geometry(int width, int height);

	Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) const;

	void SetPosition(const Vector2f& position, float anchorX = 0.5f, float anchorY = 0.5f);
	void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
	void Move(float x, float y);

	void SetColor(const Color& color) { m_color = color; }

	virtual void Resize(int width, int height);

	virtual void Draw(SDL_Renderer* renderer) = 0;

};

