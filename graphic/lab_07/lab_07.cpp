#include "stdafx.h"

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

int _tmain(int argc, _TCHAR* argv[])
{
	system("color f0");
	point s1;
	s1.x = 300.0; s1.y = 20.0;
	float a1 = 500.0;
	int iter = 8;
	while (!_kbhit()) {
		tri(s1, a1, iter);
	}
	cin.ignore();

	return 0;
}

int tri(point startp, float sidel, int iter) {
	if (iter == 0) return 0;
	else {
		point top_t1, top_t2, midpoint, temp1, temp2;
		top_t1.x = startp.x - sidel / 2;
		top_t2.x = startp.x + sidel / 2;
		top_t1.y = startp.y + sqrt(3.0) / 2 * sidel;
		top_t2.y = top_t1.y;
		drawLine(startp, top_t1);
		drawLine(startp, top_t2);
		drawLine(top_t2, top_t1);

		temp1.x = top_t1.x;
		temp1.y = top_t1.y;
		temp2.x = top_t2.x;
		temp2.y = temp1.y;
		float k = 0;
		for (int i = top_t1.y; i > startp.y; i--) {
			k++;
			temp1.y = i;
			temp2.y = temp1.y;
			temp1.x = top_t1.x + k / 1.74;
			temp2.x = top_t2.x - k / 1.74;
			drawLine(temp1, temp2);
		}

		temp1.x = startp.x - sidel / 4;
		temp1.y = startp.y + sqrt(3.0) / 4 * sidel;
		temp2.x = startp.x + sidel / 4;
		temp2.y = temp1.y;
		k = 0;
		for (int i = temp1.y; i < top_t1.y; i++) {
			k++;
			temp1.y = i;
			temp2.y = temp1.y;
			temp1.x = startp.x - sidel / 4 + k / 1.74;
			temp2.x = startp.x + sidel / 4 - k / 1.74;
			eraseLine(temp1, temp2);
		}

		midpoint = startp;
		tri(midpoint, sidel / 2, iter - 1);

		midpoint.x = startp.x - sidel / 4;
		midpoint.y = startp.y + sqrt(3.0) / 4 * sidel;
		tri(midpoint, sidel / 2, iter - 1);

		midpoint.x = startp.x + sidel / 4;
		midpoint.y = startp.y + sqrt(3.0) / 4 * sidel;
		tri(midpoint, sidel / 2, iter - 1);

	}
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
