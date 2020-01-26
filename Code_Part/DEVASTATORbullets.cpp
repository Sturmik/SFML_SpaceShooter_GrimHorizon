#include "DEVASTATORbullets.h"

DEVASTATORbullets::DEVASTATORbullets()
{
	BossBullets.setOrigin(BossBulletsShape / 2, BossBulletsShape / 2);
	BossBullets.setRadius(BossBulletsShape);
	BossBullets.setFillColor(sf::Color::Red);
	BossBullets.setOutlineThickness(4.f);
}

void DEVASTATORbullets::move(float CourseUp, float CourseGoUp)
{
	BossBullets.move(CourseUp, CourseGoUp);
}

void DEVASTATORbullets::spawn(sf::RenderWindow& window, DEVASTATORbullets*& BossBullet, int& bulletquant)
{
	for (int i = 0; i < bulletquant; i++)
	{
		if (BossBullet[i].Active == 0)
		{
			int check = rand() % 4;
			if (check == 0)
			{
				BossBullet[i].Active = 1;
				BossBullet[i].BossBullets.setPosition(1, rand() % window.getSize().y);
				BossBullet[i].BulletType = 1;
			}
			if (check == 1)
			{
				BossBullet[i].Active = 1;
				BossBullet[i].BossBullets.setPosition(window.getSize().x - 1, rand() % window.getSize().y);
				BossBullet[i].BulletType = 2;
			}
			if (check == 2)
			{
				BossBullet[i].Active = 1;
				BossBullet[i].BossBullets.setPosition(rand() % window.getSize().x, 0);
				BossBullet[i].BulletType = 1;
			}
			if (check == 3)
			{
				BossBullet[i].Active = 1;
				BossBullet[i].BossBullets.setPosition(rand() % window.getSize().x, rand() % window.getSize().y - 1);
				BossBullet[i].BulletType = 2;
			}

			BossBullet[i].CourseUp = 160.f;
			BossBullet[i].CourseGoUp = 160.f;
		}
	}
}

void DEVASTATORbullets::draw(sf::RenderWindow& window, DEVASTATORbullets*& BossBullet, int& bulletquant, float deltatime)
{
	for (int i = 0; i < bulletquant; i++)
	{
		if (BossBullet[i].Active == 1)
		{
			window.draw(BossBullet[i].BossBullets);

			if (BossBullet[i].BulletType == 1)
				BossBullet[i].move(CourseUp * deltatime, CourseGoUp * deltatime);
			if (BossBullet[i].BulletType == 2)
				BossBullet[i].move(-CourseUp * deltatime, -CourseGoUp * deltatime);

			if (BossBullet[i].BossBullets.getPosition().x >= window.getSize().x)
				BossBullet[i].BossBullets.setPosition(0, BossBullet[i].BossBullets.getPosition().y);
			else
				if (BossBullet[i].BossBullets.getPosition().x <= 0)
					BossBullet[i].BossBullets.setPosition(window.getSize().x, BossBullet[i].BossBullets.getPosition().y);

			if (BossBullet[i].BossBullets.getPosition().y >= window.getSize().y)
				BossBullet[i].BossBullets.setPosition(BossBullet[i].BossBullets.getPosition().x, 0);
			else
				if (BossBullet[i].BossBullets.getPosition().y <= 0)
					BossBullet[i].BossBullets.setPosition(BossBullet[i].BossBullets.getPosition().x, window.getSize().y);
		}
		else
		{
			BossBullet[i].BossBullets.setPosition(3000, 3000);
		}
	}
}
