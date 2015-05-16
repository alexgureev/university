#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct Item
{
	int value;
	Item * next;
};

void createStacks();
void outputStacks();
void createStack(int member);
void outputStack(int member);
void push(Item * &head, int value);
void revert(Item * &head, int size);
int pop(Item * &head);
void saveStacks();
void saveStack(int number);
void loadStacks();
void loadStack(int number);