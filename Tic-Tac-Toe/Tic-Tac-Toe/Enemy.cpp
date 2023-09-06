#include "Enemy.h"

unsigned long x = 123456789, y = 362436069, z = 521288629;

Enemy::Enemy()
{
	srand(static_cast<unsigned long>(time(0)));
	x = rand();
	y = rand();
	z = rand();
}

char Enemy::Move(char x[3][3])
{
	vector<char> options {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 2; j++) 
			if (x[i][j] == 'X' || x[i][j] == 'O') 
				options.erase(remove(options.begin(), options.end(), (char)((int)'0' + 3 * (2 - i) + j + 1)), options.end());
	unsigned long test = randXoshiro() % options.size();
	return options[test];
}

unsigned long Enemy::randXoshiro()
{  
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}