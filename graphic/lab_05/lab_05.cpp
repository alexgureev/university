#include "stdafx.h"

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

int _tmain(int argc, _TCHAR* argv[])
{
	system("color f0");
	double      x, y, newx, newy;
	unsigned i; /* counter variable */
	int   rand_num;

	srand(0);
	while (!_kbhit())
	{
		x = (double)rand() / 50000.0;
		y = (double)rand() / 50000.0;
		for (i = 0; i < MAXIT; i++)
		{
			rand_num = rand();
			if (rand_num < 0.01 * RAND_MAX)
			{
				newx = 0;
				newy = 0.16 * y;
				x = newx;
				y = newy;
			}
			else
			if (rand_num < 0.86 * RAND_MAX)
			{
				newx = (0.85 * x) + (0.04 * y);
				newy = (-0.04 * x) + (0.85 * y) + 1.6;
				x = newx;
				y = newy;
			}
			else
			if (rand_num < 0.93 * RAND_MAX)
			{
				newx = (0.2 * x) - (0.26 * y);
				newy = (0.23 * x) + (0.22 * y) + 1.6;
				x = newx;
				y = newy;
			}
			else
			{
				newx = (-0.15 * x) + (0.28 * y);
				newy = (0.26 * x) + (0.24 * y) + 0.44;
				x = newx;
				y = newy;
			}
		}  /* for loop */
		if ((x >= -5.0) && (x <= 5.0) && (y >= 0.0) && (y <= 10.0))
			SetPixel(mydc, 200 + x * 23, 280 - y * 25, RGB(0, 225, 0));
	}  /* while (!kbhit()) */
	if (_getch() == 0)
		_getch();
}


