#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper::DrawHelper()
{
	this->consoleWindow = GetConsoleWindow();
	this->deviceContext = GetDC(this->consoleWindow);
}

DrawHelper::~DrawHelper()
{
}

COLORREF DrawHelper::getRedColor()
{
	return this->red;
}

void DrawHelper::setTerminalColor()
{
	system("color f0");
}

void DrawHelper::pause()
{
	system("pause");
}

void DrawHelper::clearScreen()
{
	system("cls");
}

bool DrawHelper::wait()
{
	return !_kbhit();
}

void DrawHelper::drawPixel(int x, int y, COLORREF color)
{
	SetPixel(this->deviceContext, x, y, color);
}

void DrawHelper::releaseContext()
{
	ReleaseDC(this->consoleWindow, this->deviceContext);
}

void DrawHelper::drawLine(int x1, int y1, int const x2, int const y2)
{
	int delta_x(x2 - x1);

	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = std::abs(delta_x) << 1;

	int delta_y(y2 - y1);

	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = std::abs(delta_y) << 1;

	this->drawPixel(x1, y1, this->getRedColor());

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

			this->drawPixel(x1, y1, this->getRedColor());
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

			this->drawPixel(x1, y1, this->getRedColor());
		}
	}
}