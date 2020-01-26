#include "Player.h"
#include <iostream>

SpaceshipPl::SpaceshipPl(float mX, float mY)
{
	player.setPosition(mX, mY);
	player.setOrigin(PlayerShapeWidth / 2, PlayerShapeHeight / 2);
	player.setSize(sf::Vector2f(PlayerShapeWidth, PlayerShapeHeight));

	Hitbox.setRadius(12.0f);

	PlayerHit.loadFromFile("Playerhit.wav");

	playerTexture.loadFromFile("Ship.png");
	player.setTexture(&playerTexture);

	ReloadTime = sf::seconds(30.0f);
}

void SpaceshipPl::Resetup(float speed, float rotate)
{
	Speed = speed;
	SpeedChange = speed / 10.0f;
	adaptiveCourseUp = speed;
	adaptiveGoUp = 0.0f;
	rotateSpeed = rotate;
	remembertocompare = 0;
	inertion = 0;
	lastmove = 0;
	lastmove2 = 0;

	ReloadTime = sf::seconds(30.0f);
}



void SpaceshipPl::update(sf::RenderWindow& window,Bullet*& bullets, int& bulletsQuant, float deltatime)
{
	Hitbox.setPosition(player.getPosition().x, player.getPosition().y);

	for (int i = 0; i < bulletsQuant; i++)
	{
		if (bullets[i].Active == 0)
			bullets[i].setPos(sf::Vector2f(player.getPosition().x, player.getPosition().y));
	}


	if (player.getPosition().x >= window.getSize().x)
		player.setPosition(0, player.getPosition().y);
	else
		if (player.getPosition().x <= 0)
			player.setPosition(window.getSize().x, player.getPosition().y);

	if (player.getPosition().y >= window.getSize().y)
			player.setPosition(player.getPosition().x, 0);
			else
				if (player.getPosition().y <= 0)
					player.setPosition(player.getPosition().x, window.getSize().y);

	if (inertion > 0)
	{
		player.move(lastmove * deltatime, lastmove2 * deltatime);

		if (lastmove > 0.1 || lastmove < -0.1)
			if (lastmove2 > 0.1 || lastmove2 < -0.1)
			{
				if (lastmove > 0)
					lastmove -= (double)0.01 ;
				else
					if (lastmove < 0)
						lastmove += (double)0.01;

				if (lastmove2 > 0)
					lastmove2 -= (double)0.01;
				else
					if (lastmove < 0)
						lastmove2 += (double)0.01;
			}

		inertion--;
	}

	if (player.getRotation() > 0 && player.getRotation() < 90)
	{
		if (player.getRotation() > 0.0 && player.getRotation() < 1.0)
		{
			adaptiveGoUp = 0.0f;
			adaptiveCourseUp = Speed;
			remembertocompare = 0;
		}
		if (player.getRotation() > remembertocompare + 10.0)
		{
			adaptiveGoUp += SpeedChange;
			adaptiveCourseUp -= SpeedChange;
			remembertocompare = player.getRotation();
		}
		else
		{
			if (player.getRotation() < remembertocompare - 10.0)
			{
				adaptiveGoUp -= SpeedChange;
				adaptiveCourseUp += SpeedChange;
				remembertocompare = player.getRotation();
			}
		}
	}
	if (player.getRotation() >= 90 && player.getRotation() <= 180)
	{
		if (player.getRotation() > 90.0 && player.getRotation() < 91.0)
		{
			adaptiveGoUp = Speed;
			adaptiveCourseUp = 0.0f;
			remembertocompare = 90.0;
		}
		if (player.getRotation() > remembertocompare + 10.0)
		{
			adaptiveGoUp -= SpeedChange;
			adaptiveCourseUp -= SpeedChange;
			remembertocompare = player.getRotation();
		}
		else
		{
			if (player.getRotation() < remembertocompare - 10.0)
			{
				adaptiveGoUp += SpeedChange;
				adaptiveCourseUp += SpeedChange;
				remembertocompare = player.getRotation();
			}
		}
	}
	if (player.getRotation() >= 180 && player.getRotation() <= 270)
	{
		if (player.getRotation() > 180.0 && player.getRotation() < 181.0)
		{
			adaptiveGoUp = 0.0f;
			adaptiveCourseUp = -Speed;
			remembertocompare = 90.0;
		}
		if (player.getRotation() > remembertocompare + 10.0)
		{
			adaptiveGoUp -= SpeedChange;
			adaptiveCourseUp += SpeedChange;
			remembertocompare = player.getRotation();
		}
		else
		{
			if (player.getRotation() < remembertocompare - 10.0)
			{
				adaptiveGoUp += SpeedChange;
				adaptiveCourseUp -= SpeedChange;
				remembertocompare = player.getRotation();
			}
		}
	}
	if (player.getRotation() >= 270)
	{
		if (player.getRotation() > 358.0 && player.getRotation() < 359.9)
		{
			adaptiveGoUp = 0.0f;
			adaptiveCourseUp = Speed;
			remembertocompare = 0;
		}
		if (player.getRotation() > 270.0 && player.getRotation() < 271.0)
		{
			adaptiveGoUp = -Speed;
			adaptiveCourseUp = 0.0f;
			remembertocompare = 90.0;
		}
		if (player.getRotation() > remembertocompare + 10.0)
		{
			adaptiveGoUp += SpeedChange;
			adaptiveCourseUp += SpeedChange;
			remembertocompare = player.getRotation();
		}
		else
		{
			if (player.getRotation() < remembertocompare - 10.0)
			{
				adaptiveGoUp -= SpeedChange;
				adaptiveCourseUp -= SpeedChange;
				remembertocompare = player.getRotation();
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		player.move(adaptiveCourseUp* deltatime, adaptiveGoUp* deltatime);
		inertion = 50;
		lastmove = adaptiveCourseUp;
		lastmove2 = adaptiveGoUp;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		player.move(-adaptiveCourseUp * deltatime, -adaptiveGoUp * deltatime);
		inertion = 50;
		lastmove = -adaptiveCourseUp;
		lastmove2 = -adaptiveGoUp;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		player.rotate(-rotateSpeed * deltatime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		player.rotate(rotateSpeed * deltatime);
	}
	if (Reload == sf::seconds(0.0f))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			isFiring = 1;
			Reload = ReloadTime;
		}
	}

	if (isFiring == true)
	{
		for (int i = 0; i < bulletsQuant; i++)
		{
			if (bullets[i].Active == 0)
			{ 
				bullets[i].Active = 1;
				bullets[i].CourseUp = adaptiveCourseUp * 5;
				bullets[i].CourseGoUp = adaptiveGoUp * 5;
				isFiring = false;
				break;
			}
		}
	}

	if (Reload >= sf::seconds(0.1))
		Reload -= sf::seconds(0.1f);

}

void SpaceshipPl::checkForCol(sf::RenderWindow& window,Enemy*& enemy, int& enemyquant, int& hp)
{
	for (int i = 0; i < enemyquant; i++)
	{
		sf::FloatRect checkforhit = Hitbox.getGlobalBounds();
		sf::FloatRect checkforhit2;
		checkforhit2 = enemy[i].enemy.getGlobalBounds();

		if (checkforhit.intersects(checkforhit2))
		{
			hp -= 10;
			PlayerHitAct.setBuffer(PlayerHit);
			PlayerHitAct.play();
			enemy[i].spawn(window, enemy,  i);
		}
	}
}

void SpaceshipPl::checkForCol(sf::RenderWindow& window, AlienShips*& AlienShip, int& AlienShipquant, AlienShipsRange*& AlienShip2, int& AlienShipquant2, int& hp)
{
	for (int i = 0; i < AlienShipquant; i++)
	{
		sf::FloatRect checkforhit = Hitbox.getGlobalBounds();
		sf::FloatRect checkforhit2;
		checkforhit2 = AlienShip[i].enemy.getGlobalBounds();


		if (checkforhit.intersects(checkforhit2))
		{
			hp -= 20;
			PlayerHitAct.setBuffer(PlayerHit);
			PlayerHitAct.play();
			AlienShip[i].AlienShipsSpawn(window, AlienShip, i);
		}
	}

	for (int i = 0; i < AlienShipquant2; i++)
	{
		sf::FloatRect checkforhit = player.getGlobalBounds();
		sf::FloatRect checkforhit2;
		checkforhit2 = AlienShip2[i].enemy.getGlobalBounds();

		if (checkforhit.intersects(checkforhit2))
		{
			hp -= 20;
			PlayerHitAct.setBuffer(PlayerHit);
			PlayerHitAct.play();
			AlienShip2[i].AlienShipsSpawn(window, AlienShip2, i);
		}
	}
}

void SpaceshipPl::checkForColShot(AlienShipsRange*& AlienShip2, int& AlienShipquant2, AlienBullets*& bullets, int& bulletsquant, int& hp)
{
	for (int i = 0; i < AlienShipquant2; i++)
	{
		float pos1 = AlienShip2[i].enemy.getPosition().x;
		float pos2 = player.getPosition().x;

		int poser1 = pos1;
		int poser2 = pos2;

		if (poser1 == poser2)
		{
			for (int j = 0; j < bulletsquant; j++)
			{
				if (bullets[j].Active == 0)
				{
					if (AlienShip2[i].Reload == 0)
					{
						AlienShip2[i].Reload = 1;
						bullets[j].Active = 1;
						if (AlienShip2[i].enemy.getPosition().y < player.getPosition().y)
							bullets[j].CourseGoUp = 150.0f;
						if (AlienShip2[i].enemy.getPosition().y > player.getPosition().y)
							bullets[j].CourseGoUp = -150.0f;
						bullets[j].setPos(AlienShip2[i].enemy.getPosition().x, AlienShip2[i].enemy.getPosition().y);
					}
				}
			}
		}

		for (int j = 0; j < bulletsquant; j++)
		{
			if (bullets[j].deathball.getGlobalBounds().intersects(Hitbox.getGlobalBounds()))
			{
				hp -= 5;
				PlayerHitAct.setBuffer(PlayerHit);
				PlayerHitAct.play();
				bullets[j].Active = 0;

				if (AlienShip2[i].Reload == 1)
				{
					AlienShip2[i].Reload = 0;
					break;
				}

			}
		}
	}			
}

void SpaceshipPl::CheckForCol(sf::RenderWindow& window, DEVASTATOR& devastator, int& hp)
{
	sf::FloatRect checkforhit = Hitbox.getGlobalBounds();
	if (checkforhit.intersects(devastator.LeftArm.getGlobalBounds()))
	{
		hp -= 5;
		PlayerHitAct.setBuffer(PlayerHit);
		PlayerHitAct.play();
		player.setPosition(devastator.Devastator.getPosition().x, 900);
	}
	if (checkforhit.intersects(devastator.RightArm.getGlobalBounds()))
	{
		hp -= 5;
		PlayerHitAct.setBuffer(PlayerHit);
		PlayerHitAct.play();
		player.setPosition(devastator.Devastator.getPosition().x, 900);
	}
	if (checkforhit.intersects(devastator.Head.getGlobalBounds()))
	{
		hp -= 10;
		PlayerHitAct.setBuffer(PlayerHit);
		PlayerHitAct.play();
		player.setPosition(devastator.Devastator.getPosition().x, 900);
	}
	if (checkforhit.intersects(devastator.AssaultArm.getGlobalBounds()))
	{
		if (TimeTillDamage < 0)
		{
			hp -= 25;
			PlayerHitAct.setBuffer(PlayerHit);
			PlayerHitAct.play();
			TimeTillDamage = 1000;
		}
	}
	TimeTillDamage--;
}

void SpaceshipPl::CheckForColShot(DEVASTATORbullets*& bullets, int& bulletsquant, int& hp)
{
	for (int j = 0; j < bulletsquant; j++)
	{
		if (bullets[j].BossBullets.getGlobalBounds().intersects(Hitbox.getGlobalBounds()))
		{
			hp -= 10;
			PlayerHitAct.setBuffer(PlayerHit);
			PlayerHitAct.play();
			bullets[j].Active = 0;
		}
	}
}

void SpaceshipPl::checkForSupply(Supply*& supplies, int& suppliesquant, int& hp)
{
	for (int i = 0; i < suppliesquant; i++)
	{
		if (supplies[i].Medkit.getGlobalBounds().intersects(player.getGlobalBounds()))
		{
			supplies[i].SupplyApear.loadFromFile("SupplyPickUp.wav");
			supplies[i].SupplyApearAct.setBuffer(supplies[i].SupplyApear);
			supplies[i].SupplyApearAct.play();
			hp += 15;
			supplies[i].Activity = 0;
		}
	}
}

void SpaceshipPl::draw(sf::RenderWindow& window)
{
	window.draw(player);
}
