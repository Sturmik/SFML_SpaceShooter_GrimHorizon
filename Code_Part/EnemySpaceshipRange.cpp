#include "EnemySpaceshipRange.h"
#include <fstream>

AlienShipsRange::AlienShipsRange()
{
	enemyTexture.loadFromFile("EnemyRange.png");
	enemy.setTexture(&enemyTexture);
	enemy.setPosition(2000, 1);
	enemy.setSize(sf::Vector2f(EnemyCloseShapeWidth, EnemyCloseShapeHeight));
	enemy.setOrigin(EnemyCloseShapeWidth/ 2, EnemyCloseShapeHeight/ 2);
	CourseUp = 80.0f;
	CourseGoUp = 0;
}

void AlienShipsRange::AlienShipsSpawn(sf::RenderWindow& window, AlienShipsRange*& Ships, int enemyTospawn)
{
	Ships[enemyTospawn].enemy.setPosition(1, rand() % window.getSize().y - 1);
	Ships[enemyTospawn].CourseUp += 80.0f;
	Ships[enemyTospawn].CourseGoUp = 0;
}

bool AlienShipsRange::checkColl(sf::FloatRect checkforhit, AlienShipsRange*& Ships, int& ShipsQuant, int which)
{
	sf::FloatRect checkforhit2 = Ships[which].enemy.getGlobalBounds();
	if (checkforhit.intersects(checkforhit2))
	{
		return 1;
	}
	return 0;
}

void AlienShipsRange::MoveOn(float deltatime)
{
	enemy.move(CourseUp * deltatime, CourseGoUp * deltatime);
}

void AlienShipsRange::Draw(sf::RenderWindow& window, AlienShipsRange*& Ships, int& ShipsQuant, float deltatime)
{
	bool check = 0;
	for (int i = 0; i < ShipsQuant; i++)
	{
		Ships[i].enemy.setTexture(&enemyTexture);
		window.draw(Ships[i].enemy);
		Ships[i].MoveOn(deltatime);

		if (Ships[i].enemy.getPosition().x >= window.getSize().x)
			Ships[i].enemy.setPosition(0, rand() % window.getSize().y);
		else
			if (Ships[i].enemy.getPosition().x <= 0)
				Ships[i].enemy.setPosition(window.getSize().x, Ships[i].enemy.getPosition().y);
	}
}
