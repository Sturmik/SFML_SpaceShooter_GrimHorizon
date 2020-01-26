#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

struct HUD
{
	sf::Font font;
	sf::Font font2;

	sf::CircleShape Health;
	sf::Texture HP;
	float HealthRadius{ 40.0f };

	sf::RectangleShape Time;
	sf::Texture TimeT;
	float TimeWidth{ 90.0f }, TimeHeight{ 100.0f };

	sf::RectangleShape KilCount;
	sf::Texture KillcountT;
	float KillCountWidth{ 90.0f }, KillCountHeight{ 100.0f };

	sf::RectangleShape BossHeart;
	sf::Texture BossHeartT;
	float BossHeartWidth{ 90.0f }, BossHeartHeight{ 100.0f };

	HUD()
	{
		HP.loadFromFile("Health.png");
		Health.setTexture(&HP);
		Health.setPosition(100, 10);
		Health.setRadius(HealthRadius);
	
		TimeT.loadFromFile("Time.png");
		Time.setTexture(&TimeT);
		Time.setPosition(900, 10);
		Time.setSize(sf::Vector2f(TimeWidth, TimeHeight));

		KillcountT.loadFromFile("Hostiles.png");
		KilCount.setTexture(&KillcountT);
		KilCount.setPosition(1700, 10);
		KilCount.setSize(sf::Vector2f(KillCountWidth, KillCountHeight));

		BossHeartT.loadFromFile("BossHP.png");
		BossHeart.setTexture(&BossHeartT);
		BossHeart.setPosition(1700, 10);
		BossHeart.setSize(sf::Vector2f(BossHeartWidth, BossHeartHeight));

		font.loadFromFile("BebasNeue-Regular.ttf");
		font2.loadFromFile("FrankKnows.ttf");
	}

	void Hp(sf::RenderWindow& window, int& hp)
	{
		Health.setTexture(&HP); 
		window.draw(Health);
		sf::Text text;
		text.setFont(font);
		std::string out_string;
		std::stringstream ss;
		ss << hp;
		out_string = ss.str();
		text.setString(out_string);
		text.setCharacterSize(100); 
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		text.setPosition(200, 20);
		window.draw(Health);
		window.draw(text);
	}

	void time(sf::RenderWindow& window, int& time)
	{
		Time.setTexture(&TimeT);
		sf::Text text2;
		text2.setFont(font);
		std::string out_string1;
		std::stringstream ss1;
		ss1 << time;
		out_string1 = ss1.str();
		text2.setString(out_string1);
		text2.setCharacterSize(100);
		text2.setFillColor(sf::Color::Green);
		text2.setStyle(sf::Text::Bold);
		text2.setPosition(1000, 20);
		window.draw(Time);
		window.draw(text2);
		time--;
	}

	void KillCount(sf::RenderWindow& window, int& killcount)
	{
		KilCount.setTexture(&KillcountT);
		sf::Text text3;
		text3.setFont(font);
		std::string out_string2;
		std::stringstream ss2;
		ss2 << killcount;
		out_string2 = ss2.str();
		text3.setString(out_string2);
		text3.setCharacterSize(100);
		text3.setFillColor(sf::Color::Yellow);
		text3.setStyle(sf::Text::Bold);
		text3.setPosition(1600, 20);
		window.draw(KilCount);
		window.draw(text3);
	}

	void warning(sf::RenderWindow& window)
	{
		sf::Text text;
		text.setFont(font);
		text.setString("!WARNING, ENEMY SHIPS ARE APPROACHING!");
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		text.setPosition(700, 900);
		window.draw(text);
	}

	void destroyed(sf::RenderWindow& window, int& score)
	{
		sf::Text text;
		text.setFont(font);
		text.setString("You have died...");
		text.setCharacterSize(100);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		text.setPosition(400, 500);
		window.draw(text);

		sf::Text text1;
		text1.setFont(font);
		text1.setString("Your Score: ");
		text1.setCharacterSize(100);
		text1.setFillColor(sf::Color::Red);
		text1.setStyle(sf::Text::Bold);
		text1.setPosition(300, 700);
		window.draw(text1);

		sf::Text text2;
		text2.setFont(font);
		std::string out_string2;
		std::stringstream ss2;
		ss2 << score;
		out_string2 = ss2.str();
		text2.setString(out_string2);
		text2.setCharacterSize(100);
		text2.setFillColor(sf::Color::Yellow);
		text2.setStyle(sf::Text::Bold);
		text2.setPosition(900, 700);
		window.draw(text2);
	}

	void DEVASTATOR(sf::RenderWindow& window)
	{
		sf::Text text;
		text.setFont(font2);
		text.setString("DEVASTATOR");
		text.setCharacterSize(300);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setPosition(150, 500);
		window.draw(text);
	}

	void DEVASTATORHEALTH(sf::RenderWindow& window, int& bosshp)
	{
		Health.setTexture(&HP);
		window.draw(Health);
		sf::Text text;
		text.setFont(font2);
		std::string out_string;
		std::stringstream ss;
		ss << bosshp;
		out_string = ss.str();
		text.setString(out_string);
		text.setCharacterSize(100);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setPosition(1500, 20);
		window.draw(BossHeart);
		window.draw(text);
	}

	void DestroyingTheEvil(sf::RenderWindow& window, int& score)
	{
		sf::Text text;
		text.setFont(font);
		text.setString("You have destroyed the devouver of the worlds");
		text.setCharacterSize(100);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setPosition(100, 500);
		window.draw(text);

		sf::Text text2;
		text2.setFont(font);
		text2.setString("Your Score: ");
		text2.setCharacterSize(100);
		text2.setFillColor(sf::Color::Red);
		text2.setStyle(sf::Text::Bold);
		text2.setPosition(200, 700);
		window.draw(text2);

		sf::Text text3;
		text3.setFont(font);
		std::string out_string3;
		std::stringstream ss3;
		ss3 << score;
		out_string3 = ss3.str();
		text3.setString(out_string3);
		text3.setCharacterSize(100);
		text3.setFillColor(sf::Color::Yellow);
		text3.setStyle(sf::Text::Bold);
		text3.setPosition(600, 700);
		window.draw(text3);
	}
};