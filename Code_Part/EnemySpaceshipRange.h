#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct AlienShipsRange
{
	float EnemyCloseShapeWidth{ 110.0f }, EnemyCloseShapeHeight{ 120.0f };
	sf::RectangleShape enemy;
	sf::Texture enemyTexture;

	float CourseUp = 0.0f;
	float CourseGoUp = 0.0f;

	bool Reload = 0;

	AlienShipsRange();
	void AlienShipsSpawn(sf::RenderWindow& window, AlienShipsRange*& Ships, int enemyTospawn);
	bool checkColl(sf::FloatRect checkforhit, AlienShipsRange*& Ships, int& ShipsQuant, int which);
	void MoveOn(float deltatime);
	void Draw(sf::RenderWindow& window, AlienShipsRange*& Ships, int& ShipsQuant, float deltatime);
};