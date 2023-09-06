#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Enemy
{
private:
	unsigned long randXoshiro();
public:
	Enemy();
	char Move(char x[3][3]);
};

