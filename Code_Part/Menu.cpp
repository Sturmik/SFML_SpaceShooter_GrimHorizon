#include "Menu.h"

//#define TEST

template <class T>
void AddElemPos(T*& a, int& n, T o = 0, int pos = 0)
{
	T* p = new T[n + 1];
	for (int j = 0; j < pos; j++)
		p[j] = a[j];
	p[pos] = o;
	for (int i = pos; i < n; i++)
		p[i + 1] = a[i];
	delete[] a;
	n++;
	a = p;
}

template <class T>
void DelElemPos(T*& a, int& n, int pos = 0)
{

	T* p = new T[n - 1];
	for (int j = 0; j < pos; j++)
		p[j] = a[j];
	for (int i = pos; i < n - 1; i++)
		p[i] = a[i + 1];
	delete[] a;
	n--;
	a = p;
}

void SaveInfo(StatisticsPlayer*& Hscore, int& StatisticsQuant)
{
	ofstream outCol("Quant.txt");
	outCol << StatisticsQuant;
	outCol.close();

	ofstream out("Scores.bin", ios::binary);
	if (out.is_open())
	{
		for (int i = 0; i < StatisticsQuant; i++)
		{
			out.write((char*)&Hscore[i], sizeof(StatisticsPlayer));

			int player_name = strlen(Hscore[i].name) + 1;
			out.write((char*)& player_name, sizeof(int));
			out.write((char*)Hscore[i].name, player_name);
		}
	}
	out.close();
}

void LoadInfoFrom(StatisticsPlayer*& Hscore, int& StatisticsQuant)
{
	ifstream ifs("Scores.bin", ios::binary);
	if (ifs.is_open())
	{
		for (int i = 0; i < StatisticsQuant; i++)
		{
			ifs.read((char*)& Hscore[i], sizeof(StatisticsPlayer));

			int player_name;
			ifs.read((char*)& player_name, sizeof(int));
			Hscore[i].name = new char[player_name];
			ifs.read((char*)Hscore[i].name, player_name);
		}
	}
	ifs.close();
}

void BasicSort(StatisticsPlayer*& Hscore, int& StatisticsQuant)
{
	int i, j;
	for (i = 0; i < StatisticsQuant - 1; i++)
		for (j = 0; j < StatisticsQuant - i - 1; j++)
			if (Hscore[j].score < Hscore[j + 1].score)
				swap(Hscore[j], Hscore[j + 1]);
}

void Menu::menu()
{
	sf::RenderWindow windowMenu(sf::VideoMode(1900, 1000), "Grim Horizon", sf::Style::Close | sf::Style::Resize);

#ifdef TEST
	int StatisticsQuant = 3;
	StatisticsPlayer* Hscore = new StatisticsPlayer[StatisticsQuant];
	strcpy(Hscore[0].name, "Godlike WhaloStasoRichardo");
	Hscore[0].score = 11111;

	strcpy(Hscore[1].name, "Prostokvashka");
	Hscore[1].score = 696;

	strcpy(Hscore[2].name, "Kasiposha");
	Hscore[2].score = 1;

	SaveInfo(Hscore, StatisticsQuant);
#endif

#ifndef TEST
	int StatisticsQuant = 0;

	int temp;

	ifstream inCol("Quant.txt");
	inCol >> temp;
	inCol.close();

	if (temp > 0)
		StatisticsQuant = temp;

	StatisticsPlayer* Hscore = new StatisticsPlayer[StatisticsQuant];
	LoadInfoFrom(Hscore, StatisticsQuant);
#endif
	sf::Text BeginGame;
	sf::Text Stat;
	sf::Text Exit;
	sf::Text EnterName;

	sf::Music MenuMusicAct;
	MenuMusicAct.openFromFile("MenuMusic.wav");
	MenuMusicAct.play();
	MenuMusicAct.setVolume(75.0f);

	sf::RectangleShape windowTextureMenu;
	windowTextureMenu.setSize(sf::Vector2f(windowWidth, windowHeight));
	sf::Texture windowTextureMenuT;
	windowTextureMenuT.loadFromFile("Menu.jpg");
	windowTextureMenu.setTexture(&windowTextureMenuT);

	sf::SoundBuffer Buf;
	sf::Sound Click;

	sf::String playerInput;
	sf::Text playerText;

	bool Output = 0;

	playerText.setFont(hudMenu.font);
	playerText.setCharacterSize(50);
	playerText.setPosition(400, 500);
	playerText.setFillColor(sf::Color::Blue);
	playerText.setOutlineThickness(5.0f);
	playerText.setOutlineColor(sf::Color::White);
	playerText.setStyle(sf::Text::Bold);

	BeginGame.setFont(hudMenu.font);
	BeginGame.setString("New Game");
	BeginGame.setCharacterSize(100);
	BeginGame.setFillColor(sf::Color::Blue);
	BeginGame.setStyle(sf::Text::Bold);
	BeginGame.setPosition(90, 420);

	Stat.setFont(hudMenu.font);       //90
	Stat.setString("Statistics");
	Stat.setCharacterSize(100);
	Stat.setFillColor(sf::Color::Blue);
	Stat.setStyle(sf::Text::Bold);
	Stat.setPosition(90, 510);

	Exit.setFont(hudMenu.font);
	Exit.setString("Exit");
	Exit.setCharacterSize(100);
	Exit.setFillColor(sf::Color::Blue);
	Exit.setStyle(sf::Text::Bold);
	Exit.setPosition(90, 600);

	//EnterName.setFont(hudMenu.font);
	//EnterName.setString("Enter your name: ");
	//EnterName.setCharacterSize(100);
	//EnterName.setFillColor(sf::Color::Blue);
	//EnterName.setStyle(sf::Text::Bold);
	//EnterName.setPosition(200, 500);

	windowMenu.setPosition(sf::Vector2i(5, 1));


	while (windowMenu.isOpen())
	{
		windowMenu.clear();
		windowMenu.draw(windowTextureMenu);

		BeginGame.setOutlineColor(sf::Color::Transparent);
		Stat.setOutlineColor(sf::Color::Transparent);
		Exit.setOutlineColor(sf::Color::Transparent);
		sf::Vector2i localPosition = sf::Mouse::getPosition(windowMenu);

		sf::Event eventMenu;
		while (windowMenu.pollEvent(eventMenu))
		{
			if (eventMenu.type == sf::Event::Closed)
			{
				SaveInfo(Hscore, StatisticsQuant);
				windowMenu.close();
			}
		}

		if (localPosition.x < 420 && localPosition.x > 90)
			if (localPosition.y > 440 && localPosition.y < 520)
			{
				BeginGame.setOutlineThickness(5.0f);
				BeginGame.setOutlineColor(sf::Color::White);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					MenuMusicAct.stop();
					StatisticsPlayer Stat;
					
					sprintf(Stat.name, "%d", StatisticsQuant);
					Stat.score = campaign.campaignGo(windowMenu);

					AddElemPos(Hscore, StatisticsQuant, Stat, StatisticsQuant);
					MenuMusicAct.play();

					Output = 0;
				}
			}

		if (localPosition.x < 430 && localPosition.x > 90)
			if (localPosition.y > 530 && localPosition.y < 610)
			{
				Stat.setOutlineThickness(5.0f);
				Stat.setOutlineColor(sf::Color::White);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					Output = 1;
				}
			}

		if (localPosition.x < 230 && localPosition.x > 90)
			if (localPosition.y > 620 && localPosition.y < 710)
			{
				Exit.setOutlineThickness(5.0f);
				Exit.setOutlineColor(sf::Color::White);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					Buf.loadFromFile("Click.wav");
					Click.setBuffer(Buf);
					Click.play();
					SaveInfo(Hscore, StatisticsQuant);
					exit(0);
				}
			}

		if (Output == 1)
		{
			BasicSort(Hscore, StatisticsQuant);
			int incr = 0;
			int incr2 = 0;
			for (int i = 0; i < StatisticsQuant; i++)
			{
				incr = 0;

				playerText.setPosition(600, 300+incr2);
				playerText.setString(Hscore[i].name);
				incr = 600;
				windowMenu.draw(playerText);

				std::string out_string;
				std::stringstream ss;
				ss << Hscore[i].score;
				out_string = ss.str();

				playerText.setPosition(600 + incr, 300 + incr2);
				playerText.setString(out_string);
				windowMenu.draw(playerText);

				incr2 += 80;
			}
		}

		//if (Input == 1)
		//{
		//	windowMenu.draw(EnterName);
		//	if (eventMenu.type == sf::Event::TextEntered)
		//	{
		//		Buf.loadFromFile("Click.wav");
		//		Click.setBuffer(Buf);
		//		Click.play();
		//		playerInput += eventMenu.text.unicode;
		//		if (eventMenu.text.unicode < 128)
		//			playerText.setString(playerInput);
		//		windowMenu.draw(playerText);
		//	}
		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		//	{
		//		//MenuMusicAct.stop();
		//		//StatisticsPlayer Stat;
		//		//AddElemPos(Hscore, StatisticsQuant, Stat, StatisticsQuant);
		//		//Hscore[StatisticsQuant - 1].name = playerText;
		//		//Hscore[StatisticsQuant - 1].score = campaign.campaignGo();
		//		//MenuMusicAct.play();
		//	}
		//}
		windowMenu.draw(BeginGame);
		windowMenu.draw(Stat);
		windowMenu.draw(Exit);

		windowMenu.display();
	}
}
