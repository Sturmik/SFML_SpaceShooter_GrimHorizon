#pragma once

#include <SFML/Graphics.hpp>
#include "Asteroids.h"
#include "EnemySpaceships.h"
#include "EnemySpaceshipRange.h"
#include "SupplyPacks.h"
#include "THEDEVASTATOR.h"
#include "DEVASTATORbullets.h"

using namespace std;
using namespace sf;

constexpr float PlasmaShape{ 3.0f };

struct Bullet
{
	sf::CircleShape plasma;
	float CourseUp = 0;
	float CourseGoUp = 0;

	sf::SoundBuffer EnemyHit;
	sf::Sound EnemyHitAct;

	bool Active = 0;

	Bullet();
	void setPos(sf::Vector2f(newPos));
	void Shoot(float deltatime);
	void draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, Enemy*& enemy, int& enemyquant, int& killcount, Supply*& supplies, int& suppliesquant, float deltatime);
	void draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, AlienShips*& enemy, int& enemyquant, int& killcount, Supply*& supplies, int& suppliesquant, float deltatime);
	void draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, AlienShipsRange*& enemy, int& enemyquant, int& killcount, Supply*& supplies, int& suppliesquant, float deltatime);
	void draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, DEVASTATOR& boss, DEVASTATORbullets*& enemyBullets, int& enemybulletsquant, int& bossHp, float deltatime);
};