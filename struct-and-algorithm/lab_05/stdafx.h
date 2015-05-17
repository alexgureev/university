#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;

struct Item
{
	int serveTime;
	Item * next;
};

int T, t1, t2, n;

void inputData();
int dequeue();
void enqueue(int time);