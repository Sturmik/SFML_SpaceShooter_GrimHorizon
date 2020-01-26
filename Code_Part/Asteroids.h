#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Enemy
{
	sf::CircleShape enemy;
	sf::Texture enemyTexture;

	float CourseUp = 0.0f;
	float CourseGoUp = 0.0f;
	float EnemyShape = rand() % 100 + 50.0f;

	Enemy();
	void setPos(float X, float Y);
	bool checkColl(sf::FloatRect checkforhit, Enemy*& enemy, int& enemyquant, int which);
	void moveOn(float deltatime);
	void spawn(sf::RenderWindow& window, Enemy*& enemy, int enemytospawn);
	void draw(sf::RenderWindow& window, Enemy*& enemy, int& enemyquant, float deltatime);
};
