#include "Asteroids.h"

Enemy::Enemy()
{
	enemy.setRadius(EnemyShape);
	enemyTexture.loadFromFile("Asteroid.png");
	enemy.setTexture(&enemyTexture);
}

void Enemy::setPos(float X, float Y)
{
	enemy.setPosition(X, Y);
}

bool Enemy::checkColl(sf::FloatRect checkforhit, Enemy*& enemy, int& enemyquant, int which)
{
	sf::FloatRect checkforhit2 = enemy[which].enemy.getGlobalBounds();
	if (checkforhit.intersects(checkforhit2))
	{
		return 1;
	}
	return 0;
}

void Enemy::moveOn(float deltatime)
{
	enemy.move(CourseUp * deltatime, CourseGoUp * deltatime);
}

void Enemy::spawn(sf::RenderWindow& window, Enemy*& enemy, int enemyTospawn)
{
		int randpos = rand() % 4;
		if (randpos == 0)
		{
			enemy[enemyTospawn].setPos(-5, rand() % window.getSize().y);
			enemy[enemyTospawn].CourseUp = rand() % 180 + 150;
			enemy[enemyTospawn].CourseGoUp = 0;
		}
		if (randpos == 1)
		{
			enemy[enemyTospawn].setPos(window.getSize().x - 1, rand() % window.getSize().y - 5);
			enemy[enemyTospawn].CourseUp = -rand() % 180 + 150;
			enemy[enemyTospawn].CourseGoUp = 0;
		}
		if (randpos == 2)
		{
			enemy[enemyTospawn].setPos(rand() % window.getSize().x - 5, window.getSize().y );
			enemy[enemyTospawn].CourseUp = 0;
			enemy[enemyTospawn].CourseGoUp = -rand() % 180 + 150;
		}
		if (randpos == 3)
		{
			enemy[enemyTospawn].setPos(rand() % window.getSize().x - 5, -5);
			enemy[enemyTospawn].CourseUp = 0;
			enemy[enemyTospawn].CourseGoUp = rand() % 180 + 150;
		}
}

void Enemy::draw(sf::RenderWindow& window, Enemy*& enemy, int& enemyquant, float deltatime)
{
	bool check = 0;
	for (int i = 0; i < enemyquant; i++)
	{
		window.draw(enemy[i].enemy);
		enemy[i].enemy.setTexture(&enemyTexture);
		enemy[i].moveOn(deltatime);

		if (enemy[i].enemy.getPosition().x >= window.getSize().x)
			enemy[i].enemy.setPosition(0, enemy[i].enemy.getPosition().y);
		else
			if (enemy[i].enemy.getPosition().x <= 0)
				enemy[i].enemy.setPosition(window.getSize().x, enemy[i].enemy.getPosition().y);

		if (enemy[i].enemy.getPosition().y >= window.getSize().y)
			enemy[i].enemy.setPosition(enemy[i].enemy.getPosition().x, 0);
		else
			if (enemy[i].enemy.getPosition().y <= 0)
				enemy[i].enemy.setPosition(enemy[i].enemy.getPosition().x, window.getSize().y);
	}
}
