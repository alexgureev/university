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

#define LEFT  1  /* двоичное 0001 */
#define RIGHT 2  /* двоичное 0010 */
#define BOT   4  /* двоичное 0100 */
#define TOP   8  /* двоичное 1000 */

/* ¬ычисление кода точки
r : указатель на struct rect; p : указатель на struct point */
#define vcode(r, p) \
	((((p)->x < (r)->x_min) ? LEFT : 0) +  /* +1 если точка левее пр€моугольника */ \
	(((p)->x >(r)->x_max) ? RIGHT : 0) +  /* +2 если точка правее пр€моугольника */\
	(((p)->y < (r)->y_min) ? BOT : 0) +  /* +4 если точка ниже пр€моугольника */  \
	(((p)->y >(r)->y_max) ? TOP : 0))     /* +8 если точка выше пр€моугольника */

/* точка */
struct point {
	double x, y;
};

/* пр€моугольник */
struct rect {
	double x_min, y_min, x_max, y_max;
};

int cohen_sutherland(const struct rect *r, struct point *a, struct point *b);