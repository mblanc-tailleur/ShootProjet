#include "FilledCircle.h"
#include "SDL.h"

void FilledCircle::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rectangle;

	int x = m_x + (m_width * 1.5);
	int y = m_y + (m_width * 1.5);

	x -= (m_ax * m_width);
	y -= (m_ay * m_width);

	for (short i = 0; i < m_width; i++)
	{
		rectangle = { x, y, i, (int)sqrt((m_width * m_width) - (i * i)) };
		SDL_RenderFillRect(renderer, &rectangle);

		rectangle = { x - (int)sqrt((m_width * m_width) - (i * i)), y, (int)sqrt((m_width * m_width) - (i * i)), i };
		SDL_RenderFillRect(renderer, &rectangle);

		rectangle = { x + i - m_width, y - (int)sqrt((m_width * m_width) - ((m_width - i) * (m_width - i))), m_width - i, (int)sqrt((m_width * m_width) - ((m_width - i) * (m_width - i))) };
		SDL_RenderFillRect(renderer, &rectangle);

		rectangle = { x, y - m_width + i, (int)sqrt((m_width * m_width) - ((m_width - i) * (m_width - i))), m_width - i };
		SDL_RenderFillRect(renderer, &rectangle);
	}
}

void FilledCircle::SetRadius(short radius)
{
	m_width = radius;
}