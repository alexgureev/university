#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;
#define MAXIT 20

struct point {
	int x, y;
};

void eraseLine(point p1, point p2);
void drawLine(point p1, point p2);
int tri(point startp, float sidel, int iter);