#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper * helper = new DrawHelper();
int xA, xB, yA, yB;

void inputData()
{
	cout << "Enter xA: ";
	cin >> xA;
	cout << "Enter yA: ";
	cin >> yA;
	cout << "Enter xB: ";
	cin >> xB;
	cout << "Enter yB: ";
	cin >> yB;
}

int _tmain(int argc, _TCHAR* argv[])
{
	helper->setTerminalColor();
	inputData();

	cout << "Drawing a line from A(" 
		<< xA 
		<< "; " 
		<< yA 
		<< ") to B(" 
		<< xB 
		<< "; " 
		<< yB 
		<< ")"
		<< endl << endl;

	helper->pause();
	helper->clearScreen();

	while (helper->wait())  {
		helper->drawLine(xA, yA, xB, yB);
	}

	return 0;
}

