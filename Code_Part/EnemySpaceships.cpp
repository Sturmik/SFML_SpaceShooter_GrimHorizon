#include "EnemySpaceships.h"

AlienShips::AlienShips()
{
	enemyTexture.loadFromFile("EnemyClose.png");
	enemy.setTexture(&enemyTexture);
	enemy.setPosition(1, 2000);
	enemy.setSize(sf::Vector2f(EnemyCloseShapeWidth, EnemyCloseShapeHeight));
	enemy.setOrigin(EnemyCloseShapeWidth / 2, EnemyCloseShapeHeight / 2);
	CourseUp = 0;
	CourseGoUp = 180.0f;
}

void AlienShips::AlienShipsSpawn(sf::RenderWindow& window, AlienShips*& Ships, int enemyTospawn)
{
	Ships[enemyTospawn].enemy.setPosition(rand() % window.getSize().x, window.getSize().y - 1);
	Ships[enemyTospawn].CourseUp = 0;
	Ships[enemyTospawn].CourseGoUp += 80.0f;
}

bool AlienShips::checkColl(sf::FloatRect checkforhit, AlienShips*& Ships, int& ShipsQuant, int which)
{
	sf::FloatRect checkforhit2 = Ships[which].enemy.getGlobalBounds();
	if (checkforhit.intersects(checkforhit2))
	{
		return 1;
	}
	return 0;
}

void AlienShips::MoveOn(float deltatime)
{
	enemy.move(CourseUp * deltatime, CourseGoUp * deltatime);
}

void AlienShips::Draw(sf::RenderWindow& window, AlienShips*& Ships, int& ShipsQuant, float deltatime)
{
	bool check = 0;
	for (int i = 0; i < ShipsQuant; i++)
	{
		Ships[i].enemy.setTexture(&enemyTexture);
		window.draw(Ships[i].enemy);
		Ships[i].MoveOn(deltatime);

		if (Ships[i].enemy.getPosition().y >= window.getSize().y)
			Ships[i].enemy.setPosition(rand() % window.getSize().x, 0);
		else
			if (Ships[i].enemy.getPosition().y <= 0)
				Ships[i].enemy.setPosition(Ships[i].enemy.getPosition().x, window.getSize().y);
	}
}

