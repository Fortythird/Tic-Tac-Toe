//#define DEBUG 1;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;

string transform(string x)
{
	for (int j = 0; j < x.size(); j++)
		switch (x[j])
		{
			case '1':
			{
				x[j] = '3';
				break;
			}
			case '2':
			{
				x[j] = '6';
				break;
			}
			case '3':
			{
				x[j] = '9';
				break;
			}
			case '4':
			{
				x[j] = '2';
				break;
			}
			case '6':
			{
				x[j] = '8';
				break;
			}
			case '7':
			{
				x[j] = '1';
				break;
			}
			case '8':
			{
				x[j] = '4';
				break;
			}
			case '9':
			{
				x[j] = '7';
				break;
			}
			default:
				break;
		}
	return x;
}

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

void debug()
{
	ifstream IN;
	string st;
	vector<string> EXP;
	IN.open("mem.txt");
	while (getline(IN, st))
	{
		EXP.push_back(st);
	}
	IN.close();
	st = "9";
	for (int q = 0; q < EXP.size(); q++)
	{
		for (int r = 0; r < 4; r++)
		{
			if ((EXP[q].find(st) == 0) && (EXP[q][EXP[q].size() - 1] == 'D'))
			{
				cout << EXP[q] << endl;
				string next_step = "";
				next_step = EXP[q][st.size() + 1];
				cout << r << endl;
				cout << next_step << endl;
				if (r != 0) for (int i = 0; i < 4 - r; i++)
				{
					cout << "test" << endl;
					next_step = transform(next_step);
				}
				cout << next_step << endl;

			}
			st = transform(st);
		}
	}
}

void main()
{
#ifdef DEBUG
	debug();
#endif // DEBUG


#ifndef DEBUG
	ifstream IN;
	ofstream OUT;
	string st;
	bool t, joke = false;
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
	while ((END_GAME(field) == false) && (DRAW(field) == false))		// Процесс игры пока не конец игры и не ничья
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
			if (!joke && field[2][0] == field[1][0] && field[1][0] == 'X')
			{
				srand(static_cast<unsigned int>(time(0)));
				random = rand();
				random = random % 10;
				if (random == 5)
				{
					joke = true;
					cout << "X ";
					this_thread::sleep_for(chrono::milliseconds(2000));
					cout << "<";
					cout << "- ";
					this_thread::sleep_for(chrono::milliseconds(350));
					cout << "you lose!";
					this_thread::sleep_for(chrono::milliseconds(5000));
					cout << endl << "Just kiddin' ))0" << endl;
					this_thread::sleep_for(chrono::milliseconds(3000));
				}
			}
			t = false;
			for (int q = 0; q < EXP.size(); q++)
			{
				for (int r = 0; r < 4; r++)
				{
					if ((EXP[q].find(st) == 0) && (EXP[q][EXP[q].size() - 1] == 'D'))
					{
						t = true;
						string next_step = "";
						//cout << "Match with game " << EXP[q] << endl;
						//cout << "Conertved scenario: " << st << endl;
						next_step = EXP[q][st.size() + 1];
						if (r != 0) for (int i = 0; i < 4 - r; i++)
						{
							next_step = transform(next_step);
							st = transform(st);
						}
						for (int i = 0; i <= 2; i++)
							for (int j = 0; j <= 2; j++) if (field[i][j] == next_step[0])
							{
								st = st + field[i][j];
								field[i][j] = 'X';
							}
						//cout << "Solution: " << st << endl;
						//system("pause");
						break;
					}
					st = transform(st);
				}
				if (t) break;
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
	if (END_GAME(field) == true)									// Конец игры, определение победителя
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
	if ((END_GAME(field) == false) && DRAW(field) == true)			// Конец игры, ничья
	{
		st = st + 'N';
		cout << "Draw!" << endl;
	}
	t = false;
	for (int i = 0; i < EXP.size(); i++) if (EXP[i] == st) t = true;	// Проверка сценария на известность
	if (t == false)														// Запись сценария, если он новый
	{
		OUT.open("mem.txt");
		EXP.push_back(st);
		sort(EXP.begin(), EXP.end(), comp);
		for (int i = 0; i < EXP.size(); i++) OUT << EXP[i] << endl;
		OUT.close();
	}
	system("pause");
	main();
#endif
}