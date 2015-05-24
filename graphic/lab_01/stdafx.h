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

#define LEFT  1  /* �������� 0001 */
#define RIGHT 2  /* �������� 0010 */
#define BOT   4  /* �������� 0100 */
#define TOP   8  /* �������� 1000 */

/* ���������� ���� �����
r : ��������� �� struct rect; p : ��������� �� struct point */
#define vcode(r, p) \
	((((p)->x < (r)->x_min) ? LEFT : 0) +  /* +1 ���� ����� ����� �������������� */ \
	(((p)->x >(r)->x_max) ? RIGHT : 0) +  /* +2 ���� ����� ������ �������������� */\
	(((p)->y < (r)->y_min) ? BOT : 0) +  /* +4 ���� ����� ���� �������������� */  \
	(((p)->y >(r)->y_max) ? TOP : 0))     /* +8 ���� ����� ���� �������������� */

/* ����� */
struct point {
	double x, y;
};

/* ������������� */
struct rect {
	double x_min, y_min, x_max, y_max;
};

int cohen_sutherland(const struct rect *r, struct point *a, struct point *b);