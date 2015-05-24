#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper * helper = new DrawHelper();
int x, y, r;

void inputData()
{
	puts("Enter x: ");
	cin >> x;
	puts("Enter y: ");
	cin >> y;
	puts("Enter r: ");
	cin >> r;
}

int _tmain(int argc, _TCHAR* argv[])
{
	helper->setTerminalColor();
	inputData();

	cout << endl
		<< "After your click, we will draw circle"
		<< endl 
		<< " with center in O ("
		<< x
		<< "; "
		<< y
		<< ") and r="
		<< r
		<< endl << endl;

	helper->pause();
	helper->clearScreen();

	while (helper->wait())  {
		helper->drawCircle(x, y, r);
	}
	
	return 0;
}
