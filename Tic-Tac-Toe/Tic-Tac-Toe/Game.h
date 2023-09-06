#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Enemy.h"
using namespace std;

class Game
{
private:
	char field[3][3] = { '7', '8', '9',
						 '4', '5', '6',
						 '1', '2', '3' };

	string rotateField(string x);
	bool isGameFinished();
	bool isDraw(); 
	bool strLengthComp(string a, string b);
	void refreshField();

public:
	void Run();
};

