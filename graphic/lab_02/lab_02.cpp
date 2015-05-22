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