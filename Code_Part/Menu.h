#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Campaign.h"
#include <fstream>
#include <stdio.h>
#include <algorithm>

struct StatisticsPlayer
{
	char* name = new char[100];
	int score = 0;
};

struct Menu
{
	Campaign campaign;
	HUD hudMenu;
	void menu();
};