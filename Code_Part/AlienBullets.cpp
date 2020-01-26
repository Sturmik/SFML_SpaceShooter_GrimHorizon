#include "AlienBullets.h"

AlienBullets::AlienBullets()
{
	deathball.setOrigin(DeathballShape / 2, DeathballShape / 2);
	deathball.setRadius(DeathballShape);
	deathball.setFillColor(sf::Color::Red);
	deathball.setOutlineThickness(2.f);
}

void AlienBullets::setPos(float X, float Y)
{
	deathball.setPosition(X, Y);
}

void AlienBullets::Shoot(float deltatime)
{
	deathball.move(CourseUp * deltatime, CourseGoUp * deltatime);
}

void AlienBullets::draw(sf::RenderWindow& window, AlienShipsRange*& RangeShips, int& RangeShipsQuant, AlienBullets*& bullets, int& bulletsquant, float deltatime)
{
	bool check;
	for (int i = 0; i < bulletsquant; i++)
	{
		if (bullets[i].Active == 0)
		{
			bullets[i].setPos(3000, 3000);
		}
		if (bullets[i].Active == 1)
		{
			window.draw(bullets[i].deathball);
			bullets[i].Shoot(deltatime);

			if (bullets[i].deathball.getPosition().x > window.getSize().x || bullets[i].deathball.getPosition().x < 0
				|| bullets[i].deathball.getPosition().y > window.getSize().y || bullets[i].deathball.getPosition().y < 0)
			{
				for (int j = 0; j < RangeShipsQuant; j++)
				{
					if (RangeShips[j].Reload == 1)
					{
						RangeShips[j].Reload = 0;
						break;
					}
				}
				bullets[i].Active = 0;
			}
		}
	}
}