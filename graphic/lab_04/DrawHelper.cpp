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

COLORREF DrawHelper::createColor(int r, int g, int b)
{
	return RGB(r, g, b);
}

COLORREF DrawHelper::getBlackColor()
{
	return this->black;
}

COLORREF DrawHelper::getWhiteColor()
{
	return this->white;
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

void DrawHelper::drawLine(int x1, int y1, int const x2, int const y2, COLORREF color)
{
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;

	for (;;)
	{
		this->drawPixel(x1, y1, color);

		if (x1 == x2 && y1 == y2)
			break;

		int error2 = error * 2;

		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}

		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}