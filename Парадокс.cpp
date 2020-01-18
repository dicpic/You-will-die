#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    std::cout << "Количество людей: "; 
	int amount;
	double x[365], achance = 1;
	std::cin >> amount;
	if (amount < 365 && amount > 0)
		for (int i = 0; i < 365; i++)
		{
			achance *= 1 - (double(i) / 365);
			x[i] = (1 - achance) * 100;
		}
	for (int i = 0; i < 365; i++)
		if (i + 1 == amount)
			std::cout << "\n f(" << i + 1 << ") = " << x[i] << "%";
		else
			std::cout << "\nf(" << i + 1 << ") = " << x[i] << "%";
	_getch();
}
