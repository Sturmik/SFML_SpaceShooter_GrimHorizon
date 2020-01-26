#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct AlienShips
{
	float EnemyCloseShapeWidth{ 90.0f }, EnemyCloseShapeHeight{ 100.0f };
	sf::RectangleShape enemy;
	sf::Texture enemyTexture;

	int Type;

	float CourseUp = 0.0f;
	float CourseGoUp = 0.0f;

	AlienShips();
	void AlienShipsSpawn(sf::RenderWindow& window, AlienShips*& Ships, int enemyTospawn);
	bool checkColl(sf::FloatRect checkforhit, AlienShips*& Ships, int& ShipsQuant, int which);
	void MoveOn(float deltatime);
	void Draw(sf::RenderWindow& window, AlienShips*& Ships, int& ShipsQuant, float deltatime);
};