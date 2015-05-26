#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h>

using namespace std;

struct Point
{
	int x, y;
};

void inputData();

int cochLine(Point p1, Point p2, int iter);