#include "stdafx.h"

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);
COLORREF COLOR = RGB(0, 0, 0);

int _tmain(int argc, _TCHAR* argv[])
{

	system("color f0");
	int ix1, ix2, iy1, iy2;
	puts("Enter x1: ");
	cin >> ix1;
	puts("Enter y1: ");
	cin >> iy1;
	puts("Enter x2: ");
	cin >> ix2;
	puts("Enter y2: ");
	cin >> iy2;
	cout << "\nPlotting a line from (" << ix1 << "; " << iy1 << ") to (" << ix2 << "; " << iy2 << ")\n\n";
	system("pause");
	system("cls");
	while (!_kbhit())  {
		Bresenham(ix1, iy1, ix2, iy2);
	}
	cin.ignore();
	ReleaseDC(myconsole, mydc);
	return 0;
}

void Bresenham(int x1, int y1, int const x2, int const y2) {
	int delta_x(x2 - x1);

	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = std::abs(delta_x) << 1;

	int delta_y(y2 - y1);

	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = std::abs(delta_y) << 1;

	SetPixel(mydc, x1, y1, COLOR);

	if (delta_x >= delta_y)
	{

		int error(delta_y - (delta_x >> 1));

		while (x1 != x2)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= delta_x;
				y1 += iy;
			}

			error += delta_y;
			x1 += ix;

			SetPixel(mydc, x1, y1, COLOR);
		}
	}
	else
	{

		int error(delta_x - (delta_y >> 1));

		while (y1 != y2)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= delta_y;
				x1 += ix;
			}

			error += delta_x;
			y1 += iy;

			SetPixel(mydc, x1, y1, COLOR);
		}
	}
}