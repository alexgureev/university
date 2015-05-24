#include "stdafx.h"
#include "DrawHelper.h"

#define ITERATION 30

DrawHelper * helper = new DrawHelper();

double      x, y, newx, newy;
int   rand_num;

int _tmain(int argc, _TCHAR* argv[])
{
	helper->setTerminalColor();

	srand(0);
	while (helper->wait())
	{
		x = (double) rand() / 100000.0;
		y = (double) rand() / 100000.0;

		for (int i = 0; i < ITERATION; i++)
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
		}  

		if ((x >= -5.0) && (x <= 5.0) && (y >= 0.0) && (y <= 10.0))
		{
			helper->drawPixel(200 + x * 32, 370 - y * 35, helper->getRedColor());
		}
	}

	if (_getch() == 0)
		_getch();
}


