#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int RightArm1 = 250, RightArm2 = 1110;
const int LeftArm1 = 250, LeftArm2 = 1110;
const int Headoro = 300;

struct DEVASTATOR
{
	sf::RectangleShape Devastator;
	sf::Texture DevastatorT;

	sf::RectangleShape LeftArm;
	sf::RectangleShape RightArm;
	sf::RectangleShape Head;

	sf::RectangleShape AssaultArm;

	sf::SoundBuffer Crit;
	sf::Sound CritA;

	sf::SoundBuffer BossSoundAttack;
	sf::Sound BossSound;

	int BossHp;
	int SmashWhere = -1; 
	int Pos;

	DEVASTATOR();
	void devastatorSmash(float deltatime);
	void ShowDown(float deltatime);
};