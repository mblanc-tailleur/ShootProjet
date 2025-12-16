#include "SDL.h"
#include <cmath>
#include <iostream>
#include <vector>

#include "Rectangle.h"
#include "Circle.h"
#include "Image.h"
#include "InputManager.h"
#include "FilledCircle.h"
#include "SmallShooter.h"
#include "DiagonalShooter.h"
#include "CosinusShooter.h"
#include "Projectile.h"
#include "GameManager.h"


#define WIDTH 960
#define HEIGHT (WIDTH * 9 / 16)

#define CENTER_X (WIDTH - 1) / 2
#define CENTER_Y (HEIGHT - 1) / 2

#define TARGET_FPS 100
#define TARGET_DELTA_TIME 1.f / TARGET_FPS

SDL_Renderer* renderer;

Color White = { 255, 255, 255, 255 };
Color Grey = { 127, 127, 127, 255 };
Color Black = { 0, 0, 0, 255 };
Color Red = { 255, 0, 0, 255 };
Color Orange = { 255, 127, 0, 255 };
Color Yellow = { 255, 255, 0, 255 };
Color Green = { 0, 255, 0, 255 };
Color Cyan = { 0, 255, 255, 255 };
Color Blue = { 0, 0, 255, 255 };
Color Magenta = { 255, 0, 255, 255 };

void ChooseColor(std::string s)
{
	if (s == "Red")
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	}

	else if (s == "Orange")
	{
		SDL_SetRenderDrawColor(renderer, 255, 127, 0, 255);
	}

	else if (s == "Yellow")
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	}

	else if (s == "Green")
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	}

	else if (s == "Cyan")
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	}

	else if (s == "Blue")
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	}

	else if (s == "Magenta")
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	}

	else if (s == "Pink")
	{
		SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
	}

	else if (s == "White")
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	else if (s == "Grey")
	{
		SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
	}

	else if (s == "Black")
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
}



long double GetDistance(Vector2f a, Vector2f b)
{
	return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}



vector<SmallShooter> Erase(vector<SmallShooter> SmallShooters, int e)
{
	vector<SmallShooter> newVector;

	for (int i = 0; i < e; i++)
	{
		newVector.push_back(SmallShooters[i]);
	}

	for (int i = e; i < (SmallShooters.size() - 1); i++)
	{
		newVector.push_back(SmallShooters[i + 1]);
	}

	return newVector;
}


vector<DiagonalShooter> Erase(vector<DiagonalShooter> DiagonalShooters, int e)
{
	vector<DiagonalShooter> newVector;

	for (int i = 0; i < e; i++)
	{
		newVector.push_back(DiagonalShooters[i]);
	}

	for (int i = e; i < (DiagonalShooters.size() - 1); i++)
	{
		newVector.push_back(DiagonalShooters[i + 1]);
	}

	return newVector;
}



vector<CosinusShooter> Erase(vector<CosinusShooter> CosinusShooters, int e)
{
	vector<CosinusShooter> newVector;

	for (int i = 0; i < e; i++)
	{
		newVector.push_back(CosinusShooters[i]);
	}

	for (int i = e; i < (CosinusShooters.size() - 1); i++)
	{
		newVector.push_back(CosinusShooters[i + 1]);
	}

	return newVector;
}

GameManager Erase(GameManager gm, int e)
{
	GameManager newGM;

	for (int i = 0; i < e; i++)
	{
		newGM.Projectile.push_back(gm.Projectile[i]);
	}

	for (int i = e; i < (gm.Projectile.size() - 1); i++)
	{
		newGM.Projectile.push_back(gm.Projectile[i + 1]);
	}

	return newGM;
}





int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
		return 1;
	}

	SDL_Window* window;


	window = SDL_CreateWindow("Draw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		std::cout << "Error window creation";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Error renderer creation";
		return false;
	}

	Vector2 projectiles;

	//init
	Entity Player(WIDTH / 19, HEIGHT / 25, 20);
	Player.SetPosition(50, 50);

	cout << Player.GetPosition(0.5, 0.5).x << endl;
	cout << Player.GetPosition(0.5, 0.5).y << endl;

	int HorizontalPlayerSpeed = WIDTH / 6;
	int VerticalPlayerSpeed = HEIGHT / 3;

	int PlayerProjectileSpeed = WIDTH;

	float deltaTime = 0;

	long double totalFrames = 0;

	vector<SmallShooter> SmallShooters;
	int SmallShootersSpeed = WIDTH / 8;

	vector<DiagonalShooter> DiagonalShooters;
	int DiagonalShootersSpeed = WIDTH / 6;

	vector<CosinusShooter> CosinusShooters;
	int CosinusShootersSpeed = WIDTH / 5;


	SmallShooter defaultSmallShooter(WIDTH - 20, 8, 10);

	SmallShooters.push_back(defaultSmallShooter);

	long double cooldownSmallShooters = 0;
	long double cooldownDiagonalShooters = 0;
	long double cooldownCosinusShooters = 0;

	Projectile EnnemyShoot(20, 8);
	EnnemyShoot.Damage = 3;
	EnnemyShoot.Speed = WIDTH / 2;


	//SDL_GetPerformanceCounter()

	GameManager gm;

	while (Player.HP > 0)
	{
		Uint64 start = SDL_GetTicks64();

		//EVENT
		InputManager::Get()->Update();

		//UPDATE
		if (InputManager::Get()->IsHeld(SDLK_z))
		{
			//move up
			Player.Move(0.f, -VerticalPlayerSpeed * deltaTime);
		}

		if (InputManager::Get()->IsHeld(SDLK_q))
		{
			//move left
			Player.Move(-HorizontalPlayerSpeed * deltaTime, 0.f);
		}

		if (InputManager::Get()->IsHeld(SDLK_s))
		{
			//move down
			Player.Move(0.f, VerticalPlayerSpeed * deltaTime);
		}

		if (InputManager::Get()->IsHeld(SDLK_d))
		{
			//move right
			Player.Move(HorizontalPlayerSpeed * deltaTime, 0.f);
		}

		Projectile proj(20, 8);


		if (InputManager::Get()->IsDown(SDLK_SPACE))
		{

			// shoot normal projectile

			proj.m_color = White;
			proj.SetPosition(Player.GetPosition(1, 0.5).x, Player.GetPosition(1, 0.5).y);
			gm.Projectile.push_back(proj);
			cout << "Created new projectile " << gm.Projectile.size() - 1 << endl;
			proj.Move(PlayerProjectileSpeed * deltaTime, 0.f);
		}

		if (InputManager::Get()->IsHeld(SDLK_d))
		{
			//shoot projectile tete cherch
			//Player.Move(speedc1 * deltaTime, 0.f);
		}

		if (Player.GetPosition(0.5f, 0.f).y < 0)
		{
			Player.SetPosition(Player.GetPosition(0.5f, 0.5f).x, 0, 0.5, 0);
		}

		if (Player.GetPosition(0.5f, 1.f).y > HEIGHT)
		{
			Player.SetPosition(Player.GetPosition(0.5f, 0.5f).x, HEIGHT, 0.5, 1);
		}

		if (Player.GetPosition(0.f, 0.5f).x < 0)
		{
			Player.SetPosition(0, Player.GetPosition(0.5f, 0.5f).y, 0, 0.5);
		}

		if (Player.GetPosition(1.f, 0.5f).x > WIDTH / 4)
		{
			Player.SetPosition(WIDTH / 4, Player.GetPosition(0.5f, 0.5f).y, 1, 0.5);
		}

		for (int i = 0; i < gm.Projectile.size(); i++)
		{
			if (gm.Projectile[i].GetPosition(0, 0.5).x > WIDTH)
			{
				gm.Projectile.erase(gm.Projectile.begin() + i);
			}

		}


		//DRAW
		ChooseColor("Black");
		SDL_RenderClear(renderer);
		ChooseColor("Yellow");
		Player.Draw(renderer);

		for (int i = 0; i < gm.Projectile.size(); i++)
		{
			gm.Projectile[i].Draw(renderer);
			gm.Projectile[i].Move(PlayerProjectileSpeed * deltaTime, 0.f);
		}

		totalFrames++;

		long double x = totalFrames / TARGET_FPS;

		cooldownSmallShooters += deltaTime;
		cooldownDiagonalShooters += deltaTime;
		cooldownCosinusShooters += deltaTime;


		// Scope des Small Shooters
		{
			// Cette partie gère l'apparition de Small Shooters
			float timeBetweenSmallShooters = 1;
			if (cooldownSmallShooters >= timeBetweenSmallShooters)
			{
				SmallShooter newSmallShooter(WIDTH + 10, 8, 8);

				SmallShooters.push_back(newSmallShooter);

				cooldownSmallShooters -= timeBetweenSmallShooters;
			}

			// Ce for déplace les Small Shooters
			for (int i = 0; i < SmallShooters.size(); i++)
			{
				SmallShooters[i].Move(-SmallShootersSpeed * deltaTime, 0.f);
				SmallShooters[i].Draw(renderer);
			}

			// Ce for gère les collisions avec les Small Shooters ainsi que leur disparition
			for (float j = 0; j <= 1; j += 0.1)
			{
				for (float k = 0; k <= 1; k += 0.1)
				{
					for (int i = 0; i < SmallShooters.size(); i++)
					{
						for (int l = 0; l < gm.Projectile.size(); l++)
						{
							if (GetDistance(SmallShooters[i].GetPosition(0.5, 0.5), gm.Projectile[l].GetPosition(j, k)) <= 16)
							{
								SmallShooters[i].HP -= 3;
								gm = Erase(gm, l);
							}
						}

						if ((GetDistance(SmallShooters[i].GetPosition(0.5, 0.5), Player.GetPosition(j, k)) <= 16) or ((SmallShooters[i].HP <= 0) or (SmallShooters[i].GetPosition(1, 0.5).x < -8)))
						{
							if (GetDistance(SmallShooters[i].GetPosition(0.5, 0.5), Player.GetPosition(j, k)) <= 16)
							{
								Player.HP -= 3;
							}

							SmallShooters.erase(SmallShooters.begin() + i);
						}
					}
				}
			}
			






			// Ce for gère les projectiles tirés par les Small Shooters
			for (int i = 0; i < SmallShooters.size(); i++)
			{
				if (SmallShooters[i].ReloadTime >= 1)
				{
					Projectile* Ennemyproj = new Projectile(25,10);
					Ennemyproj->m_color = { 255,255,255,255 };
					Ennemyproj->Position = SmallShooters[i].GetPosition(0.5, 0.5);
				 //   Enne(Ennemyproj);
					SmallShooters[i].ReloadTime -= 1;
				}

				for (int j = 0; j < SmallShooters[i].Shoots.size(); j ++)
				{
					SmallShooters[i].Shoots[j].Draw(renderer);
					SmallShooters[i].Shoots[j].Move(EnnemyShoot.Speed * deltaTime, 0.f);
					for (float k = 0; k <= 1; k += 0.1)
					{
						for (float l = 0; l <= 1; l += 0.1)
						{
							if (GetDistance(SmallShooters[i].Shoots[j].Position, Player.GetPosition(k, l)) <= 6)
							{
								Player.HP -= 3;
								SmallShooters[i].Shoots.erase(SmallShooters[i].Shoots.begin() + j);
							}
						}
					}

					if (SmallShooters[i].Shoots[j].Position.x < -5)
					{
						SmallShooters[i].Shoots.erase(SmallShooters[i].Shoots.begin() + j);
					}
				}

				SmallShooters[i].ReloadTime += deltaTime;
				
			}
		}






		/*
		// Scope des Diagonal Shooters
		{
			// Cette partie gère l'apparition de Diagonal Shooters
			float timeBetweenDiagonalShooters = 3;
			if (cooldownDiagonalShooters >= timeBetweenDiagonalShooters)
			{
				DiagonalShooter newDiagonalShooter(WIDTH + 30, 15, 15);

				DiagonalShooters.push_back(newDiagonalShooter);

				if (DiagonalShooters[DiagonalShooters.size() - 1].GetPosition(0.5, 0.5).y < HEIGHT / 2)
				{
					DiagonalShooters[DiagonalShooters.size() - 1].up = 0;
				}

				cooldownDiagonalShooters -= timeBetweenDiagonalShooters;
			}
			
			// Ce for déplace les Diagonal Shooters
			for (int i = 0; i < DiagonalShooters.size(); i++)
			{
				if (DiagonalShooters[i].up == 1)
				{
					DiagonalShooters[i].Move(-DiagonalShootersSpeed * deltaTime, -DiagonalShootersSpeed * deltaTime);
				}

				else
				{
					DiagonalShooters[i].Move(-DiagonalShootersSpeed * deltaTime, DiagonalShootersSpeed * deltaTime);
				}
				

				if (DiagonalShooters[i].GetPosition(0.5, 0).y <= 0)
				{
					DiagonalShooters[i].up = 0;
				}

				else if (DiagonalShooters[i].GetPosition(0.5, 1).y >= HEIGHT)
				{
					DiagonalShooters[i].up = 1;
				}

				DiagonalShooters[i].Draw(renderer);
			}

			// Ce for gère les collisions avec les Diagonal Shooters ainsi que leur disparition
			for (float j = 0; j <= 1; j += 0.1)
			{
				for (float k = 0; k <= 1; k += 0.1)
				{
					for (int i = 0; i < DiagonalShooters.size(); i++)
					{
						for (int l = 0; l < gm.Projectile.size(); l++)
						{
							if (GetDistance(DiagonalShooters[i].GetPosition(0.5, 0.5), gm.Projectile[l].GetPosition(j, k)) <= 16)
							{
								DiagonalShooters[i].HP -= 3;
								gm = Erase(gm, l);
							}
						}

						if ((GetDistance(DiagonalShooters[i].GetPosition(0.5, 0.5), Player.GetPosition(j, k)) <= 16) or ((DiagonalShooters[i].HP <= 0) or (DiagonalShooters[i].GetPosition(1, 0.5).x < -8)))
						{
							if (GetDistance(DiagonalShooters[i].GetPosition(0.5, 0.5), Player.GetPosition(j, k)) <= 16)
							{
								Player.HP -= 5;
							}

							DiagonalShooters.erase(DiagonalShooters.begin() + i);
						}
					}
				}
			}
		}
		
		// Scope des Cosinus Shooters
		{
			// Cette partie gère l'apparition de Cosinus Shooters
			float timeBetweenCosinusShooters = 2;
			if (cooldownCosinusShooters >= timeBetweenCosinusShooters)
			{
				CosinusShooter newCosinusShooter(WIDTH + 30, 4, 3);

				CosinusShooters.push_back(newCosinusShooter);

				if (CosinusShooters[CosinusShooters.size() - 1].GetPosition(0.5, 0.5).y < HEIGHT / 2)
				{
					CosinusShooters[CosinusShooters.size() - 1].up = 0;
				}

				cooldownCosinusShooters -= timeBetweenCosinusShooters;
			}

			// Ce for déplace les Cosinus Shooters
			for (int i = 0; i < CosinusShooters.size(); i++)
			{
				CosinusShooters[i].Move(-CosinusShootersSpeed * deltaTime, 4 * cos(CosinusShooters[i].GetPosition().x / 30));

				CosinusShooters[i].Draw(renderer);
			}

			// Ce for gère les collisions avec les Cosinus Shooters ainsi que leur disparition
			for (float j = 0; j <= 1; j += 0.1)
			{
				for (float k = 0; k <= 1; k += 0.1)
				{
					for (int i = 0; i < CosinusShooters.size(); i++)
					{
						for (int l = 0; l < gm.Projectile.size(); l++)
						{
							if (GetDistance(CosinusShooters[i].GetPosition(0.5, 0.5), gm.Projectile[l].GetPosition(j, k)) <= 16)
							{
								CosinusShooters[i].HP -= 3;
								gm = Erase(gm, l);
							}
						}

						if ((GetDistance(CosinusShooters[i].GetPosition(0.5, 0.5), Player.GetPosition(j, k)) <= 16) or ((CosinusShooters[i].HP <= 0) or (CosinusShooters[i].GetPosition(1, 0.5).x < -8)))
						{
							if (GetDistance(CosinusShooters[i].GetPosition(0.5, 0.5), Player.GetPosition(j, k)) <= 16)
							{
								Player.HP -= 5;
							}

							CosinusShooters.erase(CosinusShooters.begin() + i);
						}
					}
				}
			}
		}
		*/


		SDL_RenderPresent(renderer);
		Uint64 end = SDL_GetTicks64();

		deltaTime = (end - start) / 1000.f;
		float diff = TARGET_DELTA_TIME - deltaTime;

		//Cap FPS
		if (diff > 0)
		{
			SDL_Delay(diff * 1000);
			deltaTime = TARGET_DELTA_TIME;
		}
	}

	SDL_Delay(0);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}