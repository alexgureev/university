#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>
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
int pop(Item * &head);