// Tic-Tac-Toe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

bool END_GAME(char x[3][3])			// Функция проверки конца игры
{
	bool t = false;
	if (x[0][0] == x[0][1] && x[0][1] == x[0][2]) t = true;
	if (x[1][0] == x[1][1] && x[1][1] == x[1][2]) t = true;
	if (x[2][0] == x[2][1] && x[2][1] == x[2][2]) t = true;

	if (x[0][0] == x[1][0] && x[1][0] == x[2][0]) t = true;
	if (x[0][1] == x[1][1] && x[1][1] == x[2][1]) t = true;
	if (x[0][2] == x[1][2] && x[1][2] == x[2][2]) t = true;

	if (x[0][0] == x[1][1] && x[1][1] == x[2][2]) t = true;
	if (x[2][0] == x[1][1] && x[1][1] == x[0][2]) t = true;

	return t;
}

bool DRAW(char x[3][3])				// Проверка на ничью
{
	bool t;
	bool t1 = END_GAME(x);
	if ((x[0][0] != '7') && (x[0][1] != '8') && (x[0][2] != '9') && (x[1][0] != '4') && (x[1][1] != '5') && (x[1][2] != '6') && (x[2][0] != '1') && (x[2][1] != '2') && (x[2][2] != '3') && (t1 == false)) t = true;
	else t = false;
	return t;
}

bool comp(string a, string b)
{
	return a.length() < b.length();
}

void main()
{
	ifstream IN;
	ofstream OUT;
	string st;
	bool t;
	int k = 0, random;
	char PLAYER_STEP;
	char field[3][3] = { '7', '8', '9',
						 '4', '5', '6',
						 '1', '2', '3' };
	vector<string> EXP;
	IN.open("mem.txt");
	while (getline(IN, st))
	{
		EXP.push_back(st);
	}
	IN.close();
	st = "";
	while ((END_GAME(field) == false) && (DRAW(field) == false))
	{
		system("cls");
		for (int i = 0; i <= 2; i++)									// Вывод поля
		{
			for (int j = 0; j <= 2; j++) cout << field[i][j];
			cout << endl;
		}
		if (fmod(k, 2) == 0)
		{
			t = false;
			while (t == false)
			{
				cin >> PLAYER_STEP;
				for (int i = 0; i <= 2; i++)
					for (int j = 0; j <= 2; j++)
					{
						if (field[i][j] == PLAYER_STEP)
						{
							field[i][j] = 'O';
							st = st + PLAYER_STEP;
							t = true;
						}
					}
				if (t == false) cout << "This position isn't free! Choose another one!" << endl;
			}
		}
		else if (EXP.size() != 0)
		{
			t = false;
			for (int q = 0; q < EXP.size(); q++)
				if ((EXP[q].find(st) == 0) && (EXP[q][EXP[q].size() - 1] == 'D'))
				{
					t = true;
					for (int i = 0; i <= 2; i++)
						for (int j = 0; j <= 2; j++) if (field[i][j] == EXP[q][k + 1])
						{
							st = st + field[i][j];
							field[i][j] = 'X';
						}
					break;
				}
			if (t == false)
			{
				for (int q = 0; q < EXP.size(); q++)
					if ((EXP[q].find(st) == 0) && (EXP[q][EXP[q].size() - 1] == 'V'))
					{
						t = true;
						for (int i = 0; i <= 2; i++)
							for (int j = 0; j <= 2; j++) if (field[i][j] == EXP[q][k])
							{
								st = st + field[i][j];
								field[i][j] = 'X';
							}
						break;
					}
				while (t == false)
				{
					srand(static_cast<unsigned int>(time(0)));
					random = rand();
					random = (random % 9) + 1;
					for (int i = 0; i <= 2; i++)
						for (int j = 0; j <= 2; j++) if (((int)field[i][j] - (int)'0') == random)
						{
							st = st + field[i][j];
							field[i][j] = 'X';
							t = true;
						}
				}
			}
		}
		else
		{
			t = false;
			while (t == false)
			{
				srand(static_cast<unsigned int>(time(0)));
				random = rand();
				random = (random % 9) + 1;
				for (int i = 0; i <= 2; i++)
					for (int j = 0; j <= 2; j++) if (((int)field[i][j] - (int)'0') == random)
					{
						st = st + field[i][j];
						field[i][j] = 'X';
						t = true;
					}
			}
		}
		k++;
	}
	system("cls");
	for (int i = 0; i <= 2; i++)									// Вывод поля
	{
		for (int j = 0; j <= 2; j++) cout << field[i][j];
		cout << endl;
	}
	if (END_GAME(field) == true)
	{
		if (fmod(k, 2) == 1)
		{
			st = st + 'D';
			cout << "You won!" << endl;
		}
		else
		{
			st = st + 'V';
			cout << "You lose!" << endl;
		}
	}
	if ((END_GAME(field) == false) && DRAW(field) == true)
	{
		st = st + 'N';
		cout << "Draw!" << endl;
	}
	t = false;
	for (int i = 0; i < EXP.size(); i++) if (EXP[i] == st) t = true;
	if (t == false)
	{
		OUT.open("mem.txt");
		EXP.push_back(st);
		sort(EXP.begin(), EXP.end(), comp);
		for (int i = 0; i < EXP.size(); i++) OUT << EXP[i] << endl;
		OUT.close();
	}
	system("pause");
	main();
}
