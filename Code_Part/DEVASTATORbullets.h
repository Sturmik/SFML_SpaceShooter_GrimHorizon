#pragma once

#include <SFML/Graphics.hpp>

constexpr float BossBulletsShape{ 10.0f };

struct DEVASTATORbullets
{
	sf::CircleShape BossBullets;
	sf::CircleShape BossBulletsT;

	float CourseUp, CourseGoUp;

	int BulletType;
	bool Active = 0;

	DEVASTATORbullets();
	void move(float CourseUp, float CourseGoUp);
	void spawn(sf::RenderWindow& window, DEVASTATORbullets*& BossBullet, int& bulletquant);
	void draw(sf::RenderWindow& window, DEVASTATORbullets*& BossBullet, int& bulletquant, float deltatime);
};