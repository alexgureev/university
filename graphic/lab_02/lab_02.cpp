#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper * helper = new DrawHelper();
int x1, x2, y1, y2;

void inputData()
{
	cout << "Enter x1: ";
	cin >> x1;
	cout << "Enter y1: ";
	cin >> y1;
	cout << "Enter x2: ";
	cin >> x2;
	cout << "Enter y2: ";
	cin >> y2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	helper->setTerminalColor();
	inputData();

	cout << endl
		<< "Drawing line from A(" 
		<< x1 
		<< "; " 
		<< y1 
		<< ") to B(" 
		<< x2 
		<< "; " 
		<< y2 
		<< ")"
		<< endl << endl;

	helper->pause();
	helper->clearScreen();

	while (helper->wait())  {
		helper->drawLine(x1, y1, x2, y2);
	}

	return 0;
}

