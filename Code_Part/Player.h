#pragma once

#include <SFML/Graphics.hpp>
#include "Bullets.h"
#include "Asteroids.h"
#include "EnemySpaceships.h"
#include "AlienBullets.h"
#include "THEDEVASTATOR.h"
#include "DEVASTATORbullets.h"

constexpr float PlayerShapeWidth{ 90.0f }, PlayerShapeHeight{ 100.0f };

struct SpaceshipPl
{
	sf::RectangleShape player;
	sf::Texture playerTexture;
	sf::Time Reload = sf::seconds(0.0f);

	sf::CircleShape Hitbox;

	sf::SoundBuffer PlayerHit;
	sf::Sound PlayerHitAct;

	int TimeTillDamage = 1000;

	int Health = 100;
	float Speed = 190.8f;
	float SpeedChange = Speed / 10.0f;
	float adaptiveCourseUp = Speed;
	float adaptiveGoUp = 0.0f;
	float rotateSpeed = 180.5f ;

	float remembertocompare = 0;

	int inertion = 0;
	float lastmove = 0;
	float lastmove2 = 0;

	int plasmaquant = 3;
	bool isFiring = 0;

	sf::Time ReloadTime;

	SpaceshipPl(float mX, float mY);

	void Resetup(float Speed, float rotate);

	void update(sf::RenderWindow& window,Bullet*& bullets, int& bulletsQuant, float deltatime);
	void checkForCol(sf::RenderWindow& window, Enemy*& enemy, int& enemyquant, int& hp);
	void checkForCol(sf::RenderWindow& window, AlienShips*& AlienShip, int& AlienShipquant, AlienShipsRange*& AlienShip2, int& AlienShipquant2, int& hp);
	void checkForColShot(AlienShipsRange*& AlienShip2, int& AlienShipquant2, AlienBullets*& bullets, int& bulletsquant, int& hp);
	
	void CheckForCol(sf::RenderWindow& window, DEVASTATOR& devastator, int& hp);
	void CheckForColShot(DEVASTATORbullets*& bullets, int& bulletsquant, int& hp);

	void checkForSupply(Supply*& supplies, int& suppliesquant, int& hp);
	void draw(sf::RenderWindow& window);
};

