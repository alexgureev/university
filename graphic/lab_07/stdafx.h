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
int drawTriangle(Point vertex, float length, int nesting);