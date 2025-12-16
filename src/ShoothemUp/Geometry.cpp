#include "Geometry.h"

Geometry::Geometry(int width, int height)
{
	m_x = 0;
	m_y = 0;
	m_width = width;
	m_height = height;

	m_color = { 255,255,0,255 };
}

Vector2f Geometry::GetPosition(float anchorX, float anchorY) const
{
	Vector2f pos;
	
	pos.x = m_x + m_width * anchorX;
	pos.y = m_y + m_height * anchorY;

	return pos;
}

void Geometry::SetPosition(const Vector2f& position, float anchorX, float anchorY)
{
	SetPosition(position.x, position.y, anchorX, anchorY);
}

void Geometry::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Geometry::SetPosition(float x, float y, float anchorX, float anchorY)
{
	m_ax = anchorX;
	m_ay = anchorY;

	m_x = x - (m_ax * m_width);
	m_y = y - (m_ay * m_height);
}

void Geometry::Move(float x, float y) 
{
	m_x += x;
	m_y += y;
}