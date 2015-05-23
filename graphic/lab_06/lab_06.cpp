// lab_06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

#include <stdio.h>
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
int cochLine(point p1, point p2, int iter);

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

int globit = 6;

void main()
{
	system("color  f0");
	point center, t1, t2, t3;
	center.x = 320; center.y = 500;
	int R = 600;
	int iter = 5;

	while (!_kbhit()) {
		t1.x = center.x; t1.y = center.y + R / 4;
		t2.x = center.x + sqrt(3.0) / 4 * R; t2.y = center.y - R / 2;
		t3.x = center.x - sqrt(3.0) / 4 * R; t3.y = center.y - R / 2;

		cochLine(t1, t2, iter);
		cochLine(t2, t3, iter);
		cochLine(t3, t1, iter);
	}
	cin.ignore();
	cin.ignore();
}

int cochLine(point p1, point p2, int iter) {
	drawLine(p1, p2);
	point p_t1, p_t2, p_t3;
	p_t1.x = (2.0 * p1.x + p2.x) / 3.0;
	p_t1.y = (2.0 * p1.y + p2.y) / 3.0;
	p_t2.x = (2.0 * p2.x + p1.x) / 3.0;
	p_t2.y = (2.0 * p2.y + p1.y) / 3.0;
	if (iter > 0) {
		eraseLine(p1, p2);
		drawLine(p1, p_t1);
		drawLine(p2, p_t2);

		p_t3.x = (p_t1.x + p_t2.x + (p_t1.y - p_t2.y)*sqrt(3.0)) / 2;
		p_t3.y = (p_t1.y + p_t2.y + (p_t2.x - p_t1.x)*sqrt(3.0)) / 2;


		cochLine(p1, p_t1, iter - 1);
		cochLine(p_t2, p2, iter - 1);
		cochLine(p_t1, p_t3, iter - 1);
		cochLine(p_t3, p_t2, iter - 1);
		return 0;
	}
	else
		return 1;
}

void drawLine(point p1, point p2)
{
	int deltaX = abs(p2.x - p1.x);
	int deltaY = abs(p2.y - p1.y);
	int signX = p1.x < p2.x ? 1 : -1;
	int signY = p1.y < p2.y ? 1 : -1;
	int error = deltaX - deltaY;

	for (;;)
	{
		SetPixel(mydc, p1.x, p1.y, RGB(0, 0, 0));

		if (p1.x == p2.x && p1.y == p2.y)
			break;

		int error2 = error * 2;

		if (error2 > -deltaY)
		{
			error -= deltaY;
			p1.x += signX;
		}

		if (error2 < deltaX)
		{
			error += deltaX;
			p1.y += signY;
		}
	}
}

void eraseLine(point p1, point p2)
{
	int deltaX = abs(p2.x - p1.x);
	int deltaY = abs(p2.y - p1.y);
	int signX = p1.x < p2.x ? 1 : -1;
	int signY = p1.y < p2.y ? 1 : -1;
	int error = deltaX - deltaY;

	for (;;)
	{
		SetPixel(mydc, p1.x, p1.y, RGB(255, 255, 255));

		if (p1.x == p2.x && p1.y == p2.y)
			break;

		int error2 = error * 2;

		if (error2 > -deltaY)
		{
			error -= deltaY;
			p1.x += signX;
		}

		if (error2 < deltaX)
		{
			error += deltaX;
			p1.y += signY;
		}
	}
}
