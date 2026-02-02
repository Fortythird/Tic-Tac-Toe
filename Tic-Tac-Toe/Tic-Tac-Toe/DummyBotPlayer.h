#pragma once
#include <vector>
#include <iostream>
using namespace std;

class DummyBotPlayer
{
private:
	unsigned long randXoshiro();
public:
	DummyBotPlayer();
	char Move(char x[3][3]);
};

