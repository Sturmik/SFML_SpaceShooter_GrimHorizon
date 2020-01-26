#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <dos.h>
#include "Player.h"
#include "Bullets.h"
#include "Asteroids.h"
#include "EnemySpaceships.h"
#include "EnemySpaceshipRange.h"
#include "AlienBullets.h"
#include "Interface.h"
#include "SupplyPacks.h"
#include "THEDEVASTATOR.h"
#include "DEVASTATORbullets.h"

using namespace std;

// Window Width/Height
constexpr int windowWidth{ 1900 }, windowHeight{ 1000 };

struct Campaign
{
	int campaignGo(sf::RenderWindow &window)
	{
		srand(time(NULL));

		sf::Music BattleOST;
		BattleOST.openFromFile("BattleOst.wav");
		BattleOST.play();
		BattleOST.setVolume(75.0f);
		float volumeDown = 0.0f;

		sf::SoundBuffer buffer;
		sf::Sound WarningSound;

		//Window setup
		/*sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Grim Horizon", sf::Style::Close | sf::Style::Resize);*/

		window.setPosition(sf::Vector2i(5, 1));
		sf::RectangleShape windowTexture;
		windowTexture.setSize(sf::Vector2f(windowWidth, windowHeight));

		sf::Texture windowTextureFile;
		windowTextureFile.loadFromFile("Background1.jpg");
		windowTexture.setTexture(&windowTextureFile);

		// Creating objects
		SpaceshipPl spaceshipPl(windowWidth / 2, windowHeight / 2);

		int bulletsquant = 10;
		Bullet* bullets = nullptr;
		bullets = new Bullet[bulletsquant];

		// 1 - Asteroid wave
		int enemyquant = 15;
		Enemy* enemy = nullptr;
		enemy = new Enemy[enemyquant];
		for (int i = 0; i < enemyquant; i++)
			enemy->spawn(window, enemy, i);


		// 2 - Close quater alien ships

		int enemyClosequant = 8;
		AlienShips* enemyClose = nullptr;
		enemyClose = new AlienShips[enemyClosequant];

		// 3 - Long range alien ships

		int enemyRangequant = 3;
		AlienShipsRange* enemyRange = nullptr;
		enemyRange = new AlienShipsRange[enemyRangequant];

		int enemyBulletsquant = 3;
		AlienBullets* enemyBullets = nullptr;
		enemyBullets = new AlienBullets[enemyBulletsquant];

		// Boss 

		sf::RectangleShape BackGroundBoss;
		sf::Texture BackGroundBossT;
		BackGroundBossT.loadFromFile("THEDEVASTATORBACK.png");
		BackGroundBoss.setTexture(&BackGroundBossT);
		BackGroundBoss.setPosition(-900, 100);
		BackGroundBoss.setSize(sf::Vector2f(900, 900));
		BackGroundBoss.setFillColor(sf::Color::Black);

		int bossbulletsquant = 20;
		DEVASTATORbullets* BossBullets = new DEVASTATORbullets[bossbulletsquant];

		DEVASTATOR Boss;

		int bosshp = 2000;

		// Supply Packs 

		int supplyquant = 3;
		Supply* supplies = new Supply[supplyquant];

		// HUD settings
		HUD inter;
		int Hp = spaceshipPl.Health;
		int time = 100000; // 100000 - optimal time
		int killcount = 0;

		sf::Clock timecheck; float deltatime;
		int firstcheck = 0;

		while (window.isOpen())
		{
			auto deltatime = timecheck.restart().asSeconds();

			firstcheck++;

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (time == 50000)
			{
				//delete[] enemy;
				enemyquant = 0;

				// 2 - Close quater alien ships
				enemyClose = new AlienShips[enemyClosequant];
				// 3 - Long range alien ships
				enemyRange = new AlienShipsRange[enemyRangequant];
			}

			window.clear();
			window.draw(windowTexture);

			if (time < 30000)
			{
				BackGroundBoss.move(110.0f * deltatime, 0);
				window.draw(BackGroundBoss);
			}

			bullets->draw(window, bullets, bulletsquant, enemy, enemyquant, killcount, supplies, supplyquant, deltatime);
			if (time < 50000)
			{
				bullets->draw(window, bullets, bulletsquant, enemyClose, enemyClosequant, killcount, supplies, supplyquant, deltatime);
				bullets->draw(window, bullets, bulletsquant, enemyRange, enemyRangequant, killcount, supplies, supplyquant, deltatime);
			}

			enemyBullets->draw(window, enemyRange, enemyRangequant, enemyBullets, enemyBulletsquant, deltatime);

			spaceshipPl.draw(window);
			spaceshipPl.update(window, bullets, bulletsquant, deltatime);


			spaceshipPl.checkForCol(window, enemy, enemyquant, Hp);
			spaceshipPl.checkForSupply(supplies, supplyquant, Hp);

			if (time < 50000)
			{
				spaceshipPl.checkForCol(window, enemyClose, enemyClosequant, enemyRange, enemyRangequant, Hp);
				spaceshipPl.checkForColShot(enemyRange, enemyRangequant, enemyBullets, enemyBulletsquant, Hp);
			}

			if (enemyquant > 0)
				enemy->draw(window, enemy, enemyquant, deltatime);

			if (enemyClosequant > 0 && time < 50000)
			{
				enemyClose->Draw(window, enemyClose, enemyClosequant, deltatime);
				enemyRange->Draw(window, enemyRange, enemyRangequant, deltatime);
			}

			if (Hp <= 0)
			{
				inter.destroyed(window, killcount);
				window.display();

				sleep(sf::seconds(10));
				return killcount;
			}

			supplies->draw(window, supplies, supplyquant);

			inter.Hp(window, Hp);
			inter.time(window, time);
			inter.KillCount(window, killcount);

			if (time == 60000)
			{
				buffer.loadFromFile("EnemyShipsAproaching.wav");
				WarningSound.setBuffer(buffer);
				WarningSound.play();
			}
	
			if (time > 50000 && time < 60000)
				inter.warning(window);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				return 0;
			}


			window.display();

			if (time == 3000)
				BattleOST.setVolume(45);
			if (time == 2000)
				BattleOST.setVolume(25);
			if (time == 1000)
				BattleOST.setVolume(15);
			if (time == 0)
			{
				BattleOST.stop();
				enemyquant = 0;
				enemyRangequant = 0;
				enemyClosequant = 0;
			}

			// BOSS FIGHT MOMENT
			if (time == 0)
			{
				BattleOST.openFromFile("BossFight.wav");
				BattleOST.play();
				BattleOST.setVolume(60.0f);

				windowTextureFile.loadFromFile("BackgroundBoss.jpg");
				windowTexture.setTexture(&windowTextureFile);

				window.clear();
				window.display();
				window.clear();
				window.draw(windowTexture);
				BackGroundBoss.rotate(90.0f);
				window.display();
				sleep(sf::seconds(1));
				window.clear();
				window.draw(windowTexture);
				BackGroundBoss.setOrigin(1500 / 2, 1300 / 2);
				BackGroundBoss.setSize(sf::Vector2f(1500, 1300));
				window.display();
				sleep(sf::seconds(6));
				window.clear();
				window.draw(windowTexture);
				BackGroundBoss.setPosition(900, -100);
				window.draw(BackGroundBoss);
				window.display();
				sleep(sf::seconds(8));
				window.clear();
				window.draw(windowTexture);
				window.draw(Boss.Devastator);
				inter.DEVASTATOR(window);
				window.display();
				sleep(sf::seconds(3));

				int timeAttack1 = 1000;
				int timeAttack2 = 1000;
				int timeAttack3 = 1000;

				float change1 = spaceshipPl.Speed;

				spaceshipPl.Resetup(change1 - 0.03f * deltatime , change1 - 0.03f * deltatime);
				spaceshipPl.player.setPosition(900, 800);

				while (5)
				{
					auto deltatime = timecheck.restart().asSeconds();

					sf::Event event;
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window.close();
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						return 0;

					window.clear();
					window.draw(windowTexture);

					bullets->draw(window, bullets, bulletsquant, Boss, BossBullets, bossbulletsquant, bosshp, deltatime);
					spaceshipPl.update(window, bullets, bulletsquant, deltatime);
					spaceshipPl.draw(window);

					if (timeAttack1 <= 0)
					{
						Boss.BossSoundAttack.loadFromFile("BossAttack1.wav");
						Boss.BossSound.setBuffer(Boss.BossSoundAttack);
						Boss.BossSound.play();
						BossBullets->spawn(window, BossBullets, bossbulletsquant);
						timeAttack1 = 10000;
					}
					if (bosshp < 1500)
						if (timeAttack2 <= 0)
						{
							Boss.BossSoundAttack.loadFromFile("BossAttack2.wav");
							Boss.BossSound.setBuffer(Boss.BossSoundAttack);
							Boss.BossSound.play();
							timeAttack2 = 26000;
							Boss.SmashWhere *= -1;
						}


					if (bosshp < 500)
					{
						if (Boss.Devastator.getPosition().x > spaceshipPl.player.getPosition().x)
						{
							Boss.Devastator.move(-0.03f, 0);
							Boss.LeftArm.move(-0.03f, 0);
							Boss.RightArm.move(-0.03f, 0);
							Boss.Head.move(-0.03f, 0);
						}
						if (Boss.Devastator.getPosition().x < spaceshipPl.player.getPosition().x)
						{
							Boss.Devastator.move(0.03f, 0);
							Boss.LeftArm.move(0.03f, 0);
							Boss.RightArm.move(0.03f, 0);
							Boss.Head.move(0.03f, 0);
						}
						Boss.ShowDown(deltatime);
						Boss.SmashWhere = 0;
						spaceshipPl.inertion = 0;
						spaceshipPl.lastmove = 0;
					}

					if (Hp <= 0)
					{
						inter.destroyed(window, killcount);
						window.display();
						sleep(sf::seconds(10));
						return killcount;
					}

					if (bosshp <= 0)
					{
						window.clear();
						windowTextureFile.loadFromFile("Win.jpg");
						windowTexture.setTexture(&windowTextureFile);
						killcount += 10000;
						window.draw(windowTexture);
						inter.DestroyingTheEvil(window, killcount);
						window.display();
						sleep(sf::seconds(10));
						return killcount;
					}

					Boss.devastatorSmash(deltatime);
					window.draw(Boss.AssaultArm);

					spaceshipPl.CheckForCol(window, Boss, Hp);
					spaceshipPl.CheckForColShot(BossBullets, bossbulletsquant, Hp);

					BossBullets->draw(window, BossBullets, bossbulletsquant, deltatime);
					window.draw(Boss.Devastator);
					inter.Hp(window, Hp);
					inter.DEVASTATORHEALTH(window, bosshp);

					timeAttack1--;
					timeAttack2--;

					window.display();
				}
			}
		}

		return 0;
	}
};