#include <windows.h>
#include <iostream>
#include <cmath>
#include <cstdlib>

class DrawHelper
{
private:
	HDC deviceContext;
	HWND consoleWindow;
	COLORREF white = RGB(255, 255, 255);
	COLORREF black = RGB(0, 0, 0);
	COLORREF red = RGB(255, 0, 0);
	COLORREF green = RGB(128, 255, 0);
public:
	DrawHelper();
	~DrawHelper();
	COLORREF getRedColor();
	COLORREF getBlackColor();
	COLORREF getGreenColor();
	bool wait();
	void setTerminalColor();
	void pause();
	void clearScreen();
	void drawPixel(int x, int y, COLORREF color);
	void drawLine(int x1, int y1, int const x2, int const y2, COLORREF color);
	void drawRectangle(Square * rectangle);
	void releaseContext();
};

