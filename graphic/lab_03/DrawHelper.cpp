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

void DrawHelper::drawCircle(int x, int y, int r)
{
	int xCounter = 0;
	int yCounter = r;
	int delta = 2 - (2 * r);
	int error = 0;

	while (yCounter >= 0)
	{
		this->drawPixel(
		    x + xCounter,
		    y + yCounter,
		    this->getRedColor());

		this->drawPixel(
		    x - xCounter,
		    y + yCounter,
		    this->getRedColor());

		this->drawPixel(
		    x + xCounter,
		    y - yCounter,
		    this->getRedColor());

		this->drawPixel(
		    x - xCounter,
		    y - yCounter,
		    this->getRedColor());

		error = 2 * (delta + yCounter) - 1;
		if (delta < 0 && error <= 0) {
			++xCounter;
			delta += 2 * xCounter + 1;
			continue;
		}

		error = 2 * (delta - xCounter) - 1;
		if (delta > 0 && error > 0) {
			--yCounter;
			delta += 1 - 2 * yCounter;
			continue;
		}

		++xCounter;
		delta += 2 * (xCounter - yCounter);
		--yCounter;
	}
}
