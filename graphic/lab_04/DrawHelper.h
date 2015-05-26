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

public:
	DrawHelper();
	~DrawHelper();
	COLORREF getBlackColor();
	COLORREF getWhiteColor();
	COLORREF createColor(int r, int g, int b);
	bool wait();
	void setTerminalColor();
	void pause();
	void clearScreen();
	void drawPixel(int x, int y, COLORREF color);
	void drawLine(int x1, int y1, int const x2, int const y2, COLORREF color);
	void releaseContext();
};

