#include "stdafx.h"

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);
COLORREF COLOR = RGB(0, 0, 0);

int _tmain(int argc, _TCHAR* argv[])
{
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