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
