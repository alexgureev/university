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

COLORREF DrawHelper::getBlackColor()
{
	return this->black;
}

COLORREF DrawHelper::getGreenColor()
{
	return this->green;
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

void DrawHelper::drawRectangle(Square * rectangle)
{
	this->drawLine( // top line
		rectangle->xLeftTop, 
		rectangle->yLeftTop, 
		rectangle->xRightBottom, 
		rectangle->yLeftTop, 
		this->getRedColor()
	);

	this->drawLine( // left to bottom
		rectangle->xLeftTop, 
		rectangle->yLeftTop, 
		rectangle->xLeftTop, 
		rectangle->yRightBottom, 
		this->getRedColor()
	);

	this->drawLine( // right to bottom
		rectangle->xRightBottom, 
		rectangle->yLeftTop, 
		rectangle->xRightBottom, 
		rectangle->yRightBottom, 
		this->getRedColor()
	);

	this->drawLine( // left to bottom
		rectangle->xLeftTop, 
		rectangle->yRightBottom, 
		rectangle->xRightBottom, 
		rectangle->yRightBottom, 
		this->getRedColor()
	);
}

void DrawHelper::drawLine(int x1, int y1, int const x2, int const y2, COLORREF color)
{
	int dX = x2 - x1;
	int dY = y2 - y1;

	signed int const ix = (dX > 0) ? 1 : -1;
	signed int const iy = (dY > 0) ? 1 : -1;

	dX = abs(dX) << 1;
	dY = abs(dY) << 1;

	this->drawPixel(x1, y1, color);

	if (dX >= dY)
	{

		int error(dY - (dX >> 1));

		while (x1 != x2)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= dX;
				y1 += iy;
			}

			error += dY;
			x1 += ix;

			this->drawPixel(x1, y1, color);
		}
	}
	else
	{

		int error(dX - (dY >> 1));

		while (y1 != y2)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= dY;
				x1 += ix;
			}

			error += dX;
			y1 += iy;

			this->drawPixel(x1, y1, color);
		}
	}
}