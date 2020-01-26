#include "THEDEVASTATOR.h"

DEVASTATOR::DEVASTATOR()
{
	DevastatorT.loadFromFile("THEDEVASTATOR.png");
	Devastator.setTexture(&DevastatorT);
	Devastator.setSize(sf::Vector2f(1500, 1300));
	Devastator.setOrigin(1500 / 2, 1300 / 2);
	Devastator.setPosition(900, 0);

	AssaultArm.setSize(sf::Vector2f(10, 1000));
	AssaultArm.setOrigin(10/ 2,1000/2 );
	AssaultArm.setPosition(1900, 500);
	AssaultArm.setFillColor(sf::Color::Red);
	AssaultArm.setOutlineColor(sf::Color::White);

	LeftArm.setSize(sf::Vector2f(RightArm1, RightArm2));
	LeftArm.setOrigin(RightArm1 / 2, RightArm2 / 2);
	LeftArm.setPosition(600, 0);

	RightArm.setSize(sf::Vector2f(LeftArm1, LeftArm2));
	RightArm.setOrigin(LeftArm1 / 2, LeftArm2 / 2);
	RightArm.setPosition(1200, 0);

	Head.setSize(sf::Vector2f(Headoro, Headoro));
	Head.setOrigin(Headoro / 2, Headoro / 2);
	Head.setPosition(900, 0);
}

void DEVASTATOR::devastatorSmash(float deltatime)
{
	if (SmashWhere == 1 && AssaultArm.getPosition().x > 0)
	{
		AssaultArm.move(-150.5f * deltatime, 0);
	}
	if (SmashWhere == -1 && AssaultArm.getPosition().x < 1900)
	{
		AssaultArm.move(150.5f * deltatime, 0);
	}
}

void DEVASTATOR::ShowDown(float deltatime)
{
	if (Devastator.getPosition().y <= 500)
	{
		Devastator.move(0, 80.f * deltatime);
		LeftArm.move(0, 80.f * deltatime);
		RightArm.move(0, 80.f * deltatime);
		Head.move(0, 80.f * deltatime);
	}
}