#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int x2, y2, x1, y1;

	cout << "A (x, y)" << endl;
	cin >> x1;
	cin >> y1;

	cout << "B (x, y)" << endl;
	cin >> x2;
	cin >> y2;

	Bresenham(x1, y1, x2, y2);
	
	_getch();

	return 0;
}

void plot(int x1, int y1)
{
	cout << x1 << ':' << y1 << endl;
}

void Bresenham(int x1,
	int y1,
	int const x2,
	int const y2)
{
	int delta_x(x2 - x1);
	// if x1 == x2, then it does not matter what we set here
	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = std::abs(delta_x) << 1;

	int delta_y(y2 - y1);
	// if y1 == y2, then it does not matter what we set here
	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = std::abs(delta_y) << 1;

	plot(x1, y1);

	if (delta_x >= delta_y)
	{
		// error may go below zero
		int error(delta_y - (delta_x >> 1));

		while (x1 != x2)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= delta_x;
				y1 += iy;
			}
			// else do nothing

			error += delta_y;
			x1 += ix;

			plot(x1, y1);
		}
	}
	else
	{
		// error may go below zero
		int error(delta_x - (delta_y >> 1));

		while (y1 != y2)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= delta_y;
				x1 += ix;
			}
			// else do nothing

			error += delta_x;
			y1 += iy;

			plot(x1, y1);
		}
	}
}

#include<windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

void DrawCircle(int xc, int yc, int radius);
HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);
COLORREF COLOR = RGB(0, 0, 0);

int main() {
	system("color f0");
	int ix1, iy1, ir1;
	puts("Enter x1: ");
	cin >> ix1;
	puts("Enter y1: ");
	cin >> iy1;
	puts("Enter r: ");
	cin >> ir1;
	cout << "\nPlotting a circle with the center at (" << ix1 << "; " << iy1 << ") and radius of " << ir1 << "\n\n";
	system("pause");
	system("cls");
	while (!_kbhit())  {
		DrawCircle(ix1, iy1, ir1);
	}
	ReleaseDC(myconsole, mydc);
	cin.ignore();

	return 0;
}

void DrawCircle(int xc, int yc, int radius) {
	int x = 0;
	int y = radius;
	int delta = 2 - 2 * radius;
	int error = 0;
	while (y >= 0)
	{
		SetPixel(mydc, xc + x, yc + y, COLOR);
		SetPixel(mydc, xc - x, yc + y, COLOR);
		SetPixel(mydc, xc + x, yc - y, COLOR);
		SetPixel(mydc, xc - x, yc - y, COLOR);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}