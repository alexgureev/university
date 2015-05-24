#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <conio.h>
#include <cstdlib>

using namespace std;

#define LEFT  1  /* 0001 */
#define RIGHT 2  /* 0010 */
#define BOT   4  /* 0100 */
#define TOP   8  /* 1000 */

#define vcode(r, p) \
	((((p)->x < (r)->xLeftTop) ? LEFT : 0) +      /* +1 если точка левее прямоугольника */ \
	(((p)->x > (r)->xRightBottom) ? RIGHT : 0) +  /* +2 если точка правее прямоугольника */ \
	(((p)->y < (r)->yLeftTop) ? BOT : 0) +		  /* +4 если точка ниже прямоугольника */  \
	(((p)->y > (r)->yRightBottom) ? TOP : 0))     /* +8 если точка выше прямоугольника */

struct Point 
{
	int x;
	int y;
};

struct Square
{
	int xLeftTop;
	int yLeftTop; 
	int xRightBottom;
	int yRightBottom;
};

int cohen_sutherland(const struct Square *r, struct Point *a, struct Point *b);