#pragma once
#include "EnemySpaceshipRange.h"

#include <SFML/Graphics.hpp>
constexpr float DeathballShape{ 5.0f };

struct AlienBullets
{
	sf::CircleShape deathball;
	float CourseUp = 0;
	float CourseGoUp = 0;

	bool Active = 0;

	AlienBullets();
	void setPos(float X, float Y);
	void Shoot(float deltatime);
	void draw(sf::RenderWindow& windows, AlienShipsRange*& RangeShips, int& RangeShipsQuant, AlienBullets*& bullets, int& bulletsquant, float deltatime);
};