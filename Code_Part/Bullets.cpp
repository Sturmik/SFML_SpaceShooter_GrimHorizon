#include "Bullets.h"

Bullet::Bullet()
{
	plasma.setOrigin(PlasmaShape / 2, PlasmaShape / 2);
	plasma.setRadius(PlasmaShape);
	plasma.setFillColor(sf::Color::Blue);
	plasma.setOutlineThickness(2.f);
	EnemyHit.loadFromFile("Enemyhit.wav");
}

void Bullet::setPos(Vector2f(newPos))
{
	plasma.setPosition(newPos);
}

void Bullet::Shoot(float deltatime)
{
	plasma.move(CourseUp * deltatime, CourseGoUp * deltatime);
}

void Bullet::draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, Enemy*& enemy, int& enemyquant, int& killcount,Supply*& supplies, int& suppliesquant, float deltatime)
{
	bool check;
	for (int i = 0; i < bulletquant; i++)
	{
		if(bullet[i].Active == 1)
		{
			window.draw(bullet[i].plasma);
			bullet[i].Shoot(deltatime);

			if (bullet[i].plasma.getPosition().x > window.getSize().x || bullet[i].plasma.getPosition().x < 0
				|| bullet[i].plasma.getPosition().y > window.getSize().y || bullet[i].plasma.getPosition().y < 0)
				bullet[i].Active = 0;

				for (int j = 0; j < enemyquant; j++)
				{
					sf::FloatRect checkforhit = bullet[i].plasma.getGlobalBounds();
        			
					check = enemy[j].checkColl(checkforhit, enemy, enemyquant, j);

					if (check == 1)
					{
						if (rand() % 100 < 20)
						{
							for (int p = 0; j < suppliesquant; j++)
							{
								if (supplies[p].Activity == 0)
								{
									supplies[p].SupplyApear.loadFromFile("SupplySpawn.wav");
									supplies[p].SupplyApearAct.setBuffer(supplies[p].SupplyApear);
									supplies[p].SupplyApearAct.play();
									supplies[p].Medkit.setPosition(enemy[j].enemy.getPosition());
									supplies[p].Activity = 1;
									supplies[p].Time = 30000;
									break;
								}
							}
						}
						EnemyHitAct.setBuffer(EnemyHit);
						EnemyHitAct.setVolume(30.f);
						EnemyHitAct.play();
						enemy[j].spawn(window, enemy, j);
						bullet[i].Active = 0;
						killcount++;
					}
				}
		}
	}
}

void Bullet::draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, AlienShips*& enemy, int& enemyquant, int& killcount, Supply*& supplies, int& suppliesquant, float deltatime)
{
	bool check;
	for (int i = 0; i < bulletquant; i++)
	{
		if (bullet[i].Active == 1)
		{
			window.draw(bullet[i].plasma);
			bullet[i].Shoot(deltatime);

			if (bullet[i].plasma.getPosition().x > window.getSize().x || bullet[i].plasma.getPosition().x < 0
				|| bullet[i].plasma.getPosition().y > window.getSize().y || bullet[i].plasma.getPosition().y < 0)
				bullet[i].Active = 0;

			for (int j = 0; j < enemyquant; j++)
			{
				sf::FloatRect checkforhit = bullet[i].plasma.getGlobalBounds();

				check = enemy[j].checkColl(checkforhit, enemy, enemyquant, j);

				if (check == 1)
				{
					if (rand() % 100 < 25)
					{
						for (int p = 0; j < suppliesquant; j++)
						{
							if (supplies[p].Activity == 0)
							{
								supplies[p].SupplyApear.loadFromFile("SupplySpawn.wav");
								supplies[p].SupplyApearAct.setBuffer(supplies[p].SupplyApear);
								supplies[p].SupplyApearAct.play();
								supplies[p].Medkit.setPosition(enemy[j].enemy.getPosition());
								supplies[p].Activity = 1;
								supplies[p].Time = 15000;
								break;
							}
						}
					}
					EnemyHitAct.setBuffer(EnemyHit);
					EnemyHitAct.setVolume(30.f);
					EnemyHitAct.play();
					enemy[j].AlienShipsSpawn(window, enemy, j);
					bullet[i].Active = 0;
					killcount++;
				}
			}
		}
	}
}

void Bullet::draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, AlienShipsRange*& enemy, int& enemyquant, int& killcount, Supply*& supplies, int& suppliesquant, float deltatime)
{
	bool check;
	for (int i = 0; i < bulletquant; i++)
	{
		if (bullet[i].Active == 1)
		{
			window.draw(bullet[i].plasma);
			bullet[i].Shoot(deltatime);

			if (bullet[i].plasma.getPosition().x > window.getSize().x || bullet[i].plasma.getPosition().x < 0
				|| bullet[i].plasma.getPosition().y > window.getSize().y || bullet[i].plasma.getPosition().y < 0)
				bullet[i].Active = 0;

			for (int j = 0; j < enemyquant; j++)
			{
				sf::FloatRect checkforhit = bullet[i].plasma.getGlobalBounds();

				check = enemy[j].checkColl(checkforhit, enemy, enemyquant, j);

				if (check == 1)
				{
					if (rand() % 100 < 10)
					{
						for (int p = 0; j < suppliesquant; j++)
						{
							if (supplies[p].Activity == 0)
							{
								supplies[p].SupplyApear.loadFromFile("SupplySpawn.wav");
								supplies[p].SupplyApearAct.setBuffer(supplies[p].SupplyApear);
								supplies[p].SupplyApearAct.play();
								supplies[p].Medkit.setPosition(enemy[j].enemy.getPosition());
								supplies[p].Activity = 1;
								supplies[p].Time = 30000;
								break;
							}
						}
					}

					EnemyHitAct.setBuffer(EnemyHit);
					EnemyHitAct.setVolume(30.f);
					EnemyHitAct.play();
					enemy[j].AlienShipsSpawn(window, enemy, j);
					bullet[i].Active = 0;
					killcount++;
				}
			}
		}
	}
}

void Bullet::draw(sf::RenderWindow& window, Bullet*& bullet, int& bulletquant, DEVASTATOR& boss, DEVASTATORbullets*& enemyBullets, int& enemybulletsquant, int& bossHp, float deltatime)
{
	for (int i = 0; i < bulletquant; i++)
	{
		window.draw(bullet[i].plasma);
		bullet[i].Shoot(deltatime);

		if (bullet[i].plasma.getPosition().x > window.getSize().x || bullet[i].plasma.getPosition().x < 0
			|| bullet[i].plasma.getPosition().y > window.getSize().y || bullet[i].plasma.getPosition().y < 0)
			bullet[i].Active = 0;

		for (int j = 0; j < enemybulletsquant; j++)
		{
			if (bullet[i].plasma.getGlobalBounds().intersects(enemyBullets[j].BossBullets.getGlobalBounds()))
			{
				EnemyHitAct.setBuffer(EnemyHit);
				EnemyHitAct.setVolume(30.f);
				EnemyHitAct.play();
				enemyBullets[j].Active = 0;
				bullet[i].Active = 0;
			}
		}

		if (bullet[i].plasma.getGlobalBounds().intersects(boss.LeftArm.getGlobalBounds()) || bullet[i].plasma.getGlobalBounds().intersects(boss.RightArm.getGlobalBounds()))
		{
			EnemyHitAct.setBuffer(EnemyHit);
			EnemyHitAct.setVolume(30.f);
			EnemyHitAct.play();
			bullet[i].Active = 0;
			bossHp -= 10;
		}

		if (bullet[i].plasma.getGlobalBounds().intersects(boss.Head.getGlobalBounds()))
		{
			boss.Crit.loadFromFile("BossCritHit.wav");
			boss.CritA.setBuffer(boss.Crit);
			boss.CritA.play();
			bullet[i].Active = 0;
			bossHp -= 20;
		}
	}
}

