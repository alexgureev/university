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

public:
	DrawHelper();
	~DrawHelper();
	COLORREF getRedColor();
	bool wait();
	void setTerminalColor();
	void pause();
	void clearScreen();
	void drawPixel(int x, int y, COLORREF color);
	void releaseContext();
};

