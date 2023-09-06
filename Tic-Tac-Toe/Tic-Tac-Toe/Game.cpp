//#define DEBUG_RUN 1
#include "Game.h"

void Game::refreshField()
{
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 2; j++) field[i][j] = (char)((int)'0' + 3 * (2 - i) + j + 1);
}

bool Game::isGameFinished()
{
	bool t = false;
	if (field[0][0] == field[0][1] && field[0][1] == field[0][2]) t = true;
	if (field[1][0] == field[1][1] && field[1][1] == field[1][2]) t = true;
	if (field[2][0] == field[2][1] && field[2][1] == field[2][2]) t = true;

	if (field[0][0] == field[1][0] && field[1][0] == field[2][0]) t = true;
	if (field[0][1] == field[1][1] && field[1][1] == field[2][1]) t = true;
	if (field[0][2] == field[1][2] && field[1][2] == field[2][2]) t = true;

	if (field[0][0] == field[1][1] && field[1][1] == field[2][2]) t = true;
	if (field[2][0] == field[1][1] && field[1][1] == field[0][2]) t = true;

	return t;
}

bool Game::isDraw()
{
	bool t;
	bool t1 = isGameFinished();
	if ((field[0][0] != '7') && (field[0][1] != '8') && (field[0][2] != '9') && (field[1][0] != '4') && (field[1][1] != '5') 
		&& (field[1][2] != '6') && (field[2][0] != '1') && (field[2][1] != '2') && (field[2][2] != '3') && (t1 == false)) t = true;
	else t = false;
	return t;
}

string Game::rotateField(string x)
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

bool Game::strLengthComp(string a, string b)
{
	return a.length() < b.length();
}

void Game::Run()
{
#ifdef DEBUG_RUN

	Enemy enemy;
	int runs_amount, move_num = 0;
	string run = "";

	while ((isGameFinished() == false) && (isDraw() == false))
	{
		char move = enemy.Move(field);
		for (int i = 0; i <= 2; i++)
			for (int j = 0; j <= 2; j++) if (field[i][j] == move)
				if (move_num % 2 == 0) field[i][j] = 'X';
				else field[i][j] = 'O';
		run = run + move;
		move_num++;
	}
	if (isDraw()) run = run + 'N';
	if (move_num % 2 == 1) run = run + 'V';
	else run = run + 'D';

	cout << run << endl;
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++) cout << field[i][j];
		cout << endl;
	}

#endif // DEBUG_RUN

#ifndef DEBUG_RUN

	Enemy enemy;
	int runs_amount;
	vector<string> experience;

	cout << "How many simulations?" << endl;
	cin >> runs_amount;

	system("cls");

	for (int k = 0; k < runs_amount; k++)
	{
		string run = "";
		int move_num = 0;
		while ((isGameFinished() == false) && (isDraw() == false))
		{
			char move = enemy.Move(field);
			for (int i = 0; i <= 2; i++)
				for (int j = 0; j <= 2; j++) if (field[i][j] == move)
					if (move_num % 2 == 0) field[i][j] = 'X';
					else field[i][j] = 'O';
			run = run + move;
			move_num++;
		}
		if (isDraw()) run = run + 'N';
		else
		{
			if (move_num % 2 == 1) run = run + 'D';
			else run = run + 'V';
		}
		experience.push_back(run);

		refreshField();
	}

	system("cls");
	cout << "Analyzing..." << endl;

	sort(experience.begin(), experience.end(), [](const string& a, const string& b) {return a.length() < b.length(); });

	for (int i = 0; i < experience.size(); i++)
	{
		bool match = false;
		for (int j = i; j < experience.size(); j++) 
			if (experience[i].length() == experience[j].length())
			{
				string run_copy = experience[j];
				for (int k = 0; k < 4; k++)
				{
					run_copy = rotateField(run_copy);
					if (run_copy == experience[i])
					{
						if (match) experience.erase(next(experience.begin(), j));
						else match = true;
						break;
					}
				}
			}
	}

	ofstream file;
	file.open("Experience.txt");
	for (int i = 0; i < experience.size(); i++) file << experience[i] << endl;
	file.close();

#endif // !DEBUG_RUN
}