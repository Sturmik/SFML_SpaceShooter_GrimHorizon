#pragma once

#include <SFML/Graphics.hpp>

struct Supply
{
	sf::CircleShape Medkit;
	sf::Texture MedkitT;
	float MedkitRadius{ 30.0f };

	sf::SoundBuffer SupplyApear;
	sf::Sound SupplyApearAct;

	bool Activity = 0;
	int Time = 0;

	Supply()
	{
		MedkitT.loadFromFile("Heal.png");
		Medkit.setTexture(&MedkitT);
		Medkit.setRadius(MedkitRadius);
		Medkit.setOrigin(MedkitRadius / 2, MedkitRadius/2);
	}

	void draw(sf::RenderWindow& window, Supply*& SupplyPack, int& suppliesquant)
	{
		for (int i = 0; i < suppliesquant; i++)
		{
			SupplyPack[i].Medkit.setTexture(&MedkitT);
			window.draw(SupplyPack[i].Medkit);

			SupplyPack[i].Medkit.rotate(0.05f);

			if (SupplyPack[i].Activity == 0)
				SupplyPack[i].Medkit.setPosition(3000, 3000);

			if (SupplyPack[i].Activity == 1 && SupplyPack[i].Time >= 0)
			{
				SupplyPack[i].Time -= 1;
			}
			else
			{
				if (SupplyPack[i].Activity == 1 && SupplyPack[i].Time <= 0)
				{
					SupplyApear.loadFromFile("SupplyPickFail.wav");
					SupplyApearAct.setBuffer(SupplyApear);
					SupplyApearAct.play();
					SupplyPack[i].Activity = 0;
					SupplyPack[i].Medkit.setPosition(3000, 3000);
				}
			}
		}
	}
};