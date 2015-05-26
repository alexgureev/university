#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper * helper = new DrawHelper();
Point center, point1, point2, point3;
int iterations, R;

void inputData()
{
	/* 320 500 600 5 */
	cout << "Enter center (x; y): "
		<< endl
		<< "x= ";
	cin >> center.x;
	cout << "y= ";
	cin >> center.y;

	cout << endl
		<< "Enter radius: ";
	cin >> R;

	cout << endl
		<< "Enter iterations number: ";
	cin >> iterations;
}


int _tmain(int argc, _TCHAR* argv[])
{
	helper->setTerminalColor();
	inputData();

	helper->pause();
	helper->clearScreen();

	while (helper->wait())  {
		point1.x = center.x;
		point1.y = center.y + R / 4;

		point2.x = center.x + sqrt(3.0) / 4 * R;
		point2.y = center.y - R / 2;

		point3.x = center.x - sqrt(3.0) / 4 * R;
		point3.y = center.y - R / 2;
	
		cochLine(point1, point2, iterations);
		cochLine(point2, point3, iterations);
		cochLine(point3, point1, iterations);
	}

	helper->clearScreen();
	helper->pause();
	return 0;
}

int cochLine(Point startPoint1, Point startPoint2, int iteration) {

	helper->drawLine(
		startPoint1.x, 
		startPoint1.y, 
		startPoint2.x, 
		startPoint2.y, 
		helper->getBlackColor()
	);
	
	if (iteration <= 0) {
		return 1;
	}

	Point newPoint1, newPoint2, newPoint3;

	newPoint1.x = (2.0 * startPoint1.x + startPoint2.x) / 3.0;
	newPoint1.y = (2.0 * startPoint1.y + startPoint2.y) / 3.0;
	newPoint2.x = (2.0 * startPoint2.x + startPoint1.x) / 3.0;
	newPoint2.y = (2.0 * startPoint2.y + startPoint1.y) / 3.0;
	newPoint3.x = (newPoint1.x + newPoint2.x + (newPoint1.y - newPoint2.y)*sqrt(3.0)) / 2;
	newPoint3.y = (newPoint1.y + newPoint2.y + (newPoint2.x - newPoint1.x)*sqrt(3.0)) / 2;

	helper->drawLine(
		startPoint1.x, 
		startPoint1.y, 
		startPoint2.x, 
		startPoint2.y, 
		helper->getWhiteColor()
	);

	helper->drawLine(
		startPoint1.x, 
		startPoint1.y, 
		newPoint1.x,
		newPoint1.y, 
		helper->getBlackColor()
	);

	helper->drawLine(
		startPoint2.x, 
		startPoint2.y, 
		newPoint2.x, 
		newPoint2.y, 
		helper->getWhiteColor()
	);

	iteration--;

	if (iteration >= 0) {
		cochLine(startPoint1, newPoint1, iteration);
		cochLine(newPoint2, startPoint2, iteration);
		cochLine(newPoint1, newPoint3, iteration);
		cochLine(newPoint3, newPoint2, iteration);
	} 

	return 0;
}
