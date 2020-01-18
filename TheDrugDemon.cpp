#include "pch.h"
#include "Intro.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <random>

#pragma region Переменные

//int init_EXIT = 0;
int BACK = 0;
unsigned long CurID = 0;
std::random_device randomizer;
std::mt19937 gen(randomizer());
std::uniform_int_distribution<int> dice(1, 6);

#pragma endregion

#pragma region Штуки

struct Attributes
{
	short HT = 0; 
	short DX = 0;
	short IT = 0;
	short ST = 0;
}; 

enum Quality
{
	q_common,
	q_uncommon,
	q_rare,
	q_epic,
	q_legendary
};

enum Type
{
	t_weapon,
	t_armor,
	t_other
};

enum State
{
	s_clear = 0x0000,
	s_stackable = 0x0001,
	s_equipable = 0x0002,
	s_usable = 0x0004,
	s_quest = 0x0008
};

struct Description
{

	unsigned long ID = CurID++;
	std::string name = "NO_NAME";
	std::string description = "NO_DESCRIPTION";

	Attributes attributes;
	Quality quality = q_legendary;
	int cost = 0;

	Type type = t_weapon;
	State state = s_equipable;
	int textureID = 0;
};

//struct gendesc
//{
//	std::string name = "NO_NAME";
//	Quality quality;
//	Type type;
//	Attributes attributes;
//	short cost = 0;
//};

int QualityToNum(Quality quality)
{
	switch (quality)
	{
	case q_common: return -2;
	case q_uncommon: return -1;
	case q_rare: return 0;
	case q_epic: return 1;
	case q_legendary: return 2;
	}
}

std::string QualityToName(Quality quality)
{
	switch (quality)
	{
	case q_common: return std::string("Common");
	case q_uncommon: return std::string("Uncommon");
	case q_rare: return std::string("Rare");
	case q_epic: return std::string("Epic");
	case q_legendary: return std::string("Legendary");
	}
}

Description Generate(const Description desc)
{
	Description description;

	//description.ID = CurID++;
	//description.description = desc.name;
	//description.description = "NiBBa";

	description.quality = desc.quality;
	description.attributes = desc.attributes;
	description.cost = desc.cost;

	description.type = desc.type;

	if (description.type == t_weapon)
	{
		description.name = QualityToName(desc.quality) + " " + desc.name;
		description.attributes.ST += dice(gen) + QualityToNum(desc.quality);
		description.state = s_equipable;
	}
	else 
		if (description.type == t_armor)
		{
			description.name = QualityToName(desc.quality) + " " + desc.name;
			description.attributes.HT += dice(gen) + QualityToNum(desc.quality);
			description.state = s_equipable;
		}

	description.textureID = CurID++;
	return description;
}

void ShowDescription(Description desc)
{
	std::cout << "ID - " << desc.ID << std::endl;
	std::cout << "Name: " << desc.name << std::endl;
	std::cout << "Description: " << desc.description << std::endl;

	std::cout << "DX = " << desc.attributes.DX << std::endl;
	std::cout << "HT = " << desc.attributes.HT << std::endl;
	std::cout << "IT = " << desc.attributes.IT << std::endl;
	std::cout << "ST = " << desc.attributes.ST << std::endl;
	std::cout << "Quality is " << desc.quality << std::endl;
	std::cout << "Cost -  " << desc.cost << std::endl;

	std::cout << "Type: " << desc.type << std::endl;
	std::cout << "State: " << desc.state << std::endl;
	std::cout << "TextureID: " << desc.textureID << std::endl;
}

#pragma endregion

void Game()
{
	Description x;
	x.attributes.ST = 1;
	//x.cost = 100;
	x.name = std::string("BuzzLightyear");
	x.description = std::string("Ara ara ara");
	x.quality = q_legendary;
	x.type = t_weapon;
	ShowDescription(Generate(x));
	_getch();
}

void GameMenu(int switcher)
{
	if (BACK == 1)
		exit;
	else {
		system("cls");
		switch (switcher)
		{
		case 1:
			std::cout << "\n";
			std::cout << "	>NewGame\n\n\n";
			std::cout << "	Continue\n\n\n";
			std::cout << "	Back\n\n\n";
			break;
		case 2:
			std::cout << "\n";
			std::cout << "	NewGame\n\n\n";
			std::cout << "	>Continue\n\n\n";
			std::cout << "	Back\n\n\n";
			break;
		case 3:
			std::cout << "\n";
			std::cout << "	NewGame\n\n\n";
			std::cout << "	Continue\n\n\n";
			std::cout << "	>Back\n\n\n";
			break;
		}
		int choice = _getch();
		if (choice == 0x48)
			if (switcher != 1)
				GameMenu(switcher - 1);
			else
				GameMenu(3);
		if (choice == 0x50)
			if (switcher != 3)
				GameMenu(switcher + 1);
			else
				GameMenu(1);
		if (choice == 13 || choice == 32)
		{
			if (switcher == 1)
				Game();
			//if (switcher == 2)
				//Save(0);
			if (switcher == 3)
				BACK = 1;
		}
		else
			GameMenu(switcher);
	}
}

void StartMenu(int switcher)
{
	BACK = 0;
	system("cls");
	switch (switcher)
	{
	case 1:
		std::cout << "\n";
		std::cout << "	>GameMenu\n\n\n";
		std::cout << "	Help\n\n\n";
		std::cout << "	TopChart\n\n\n";
		std::cout << "	Exit\n\n\n";
		break;
	case 2:
		std::cout << "\n";
		std::cout << "	GameMenu\n\n\n";
		std::cout << "	>Help\n\n\n";
		std::cout << "	TopChart\n\n\n";
		std::cout << "	Exit\n\n\n";
		break;
	case 3:
		std::cout << "\n";
		std::cout << "	GameMenu\n\n\n";
		std::cout << "	Help\n\n\n";
		std::cout << "	>TopChart\n\n\n";
		std::cout << "	Exit\n\n\n";
		break;
	case 4:
		std::cout << "\n";
		std::cout << "	GameMenu\n\n\n";
		std::cout << "	Help\n\n\n";
		std::cout << "	TopChart\n\n\n";
		std::cout << "	>Exit\n\n\n";
		break;
	}
	int choice = _getch();
	if (choice == 0x48)
		if (switcher != 1)
			StartMenu(switcher - 1);
		else
			StartMenu(4);
	if (choice == 0x50)
		if (switcher != 4)
			StartMenu(switcher + 1);
		else
			StartMenu(1);
	if (choice == 13 || choice == 32)
	{
		if (switcher == 1)
			GameMenu(1);
		//if (switcher == 2)
			//Help(0);
		//if (switcher == 3)
			//TopChart();
		if (switcher == 4)
			_exit(0);
	}
	else
		StartMenu(switcher);
}

int main()
{
	system("mode con cols=60 lines=25");
	for (int i = 0; intro[i] != "Stop"; i++)
	{
		for (int j = 0; j < strlen(intro[i].c_str()); j++)
		{
			std::cout << intro[i][j];
			Sleep(500/(j+12));
		}
		std::cout << std::endl;
	}
	_getch();
	//while(init_EXIT == 0)
		StartMenu(1);
}