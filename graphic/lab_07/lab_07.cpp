#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper * helper = new DrawHelper();
Point vertext;
float sideLength;
int iterations;

void inputData()
{
	/* 300 20 500 8 */
	cout << "Enter Vertex (x; y): "
		 << endl
		 << "x= ";
	cin >> vertext.x;
	cout << "y= ";
	cin >> vertext.y;

	cout << endl
		<< "Enter side length: ";
	cin >> sideLength;

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

	drawTriangle(vertext, sideLength, iterations);

	helper->clearScreen();
	helper->pause();
	return 0;
}

int drawTriangle(Point vertex, float length, int nesting) {
	if (nesting == 0) {
		return 0;
	}

	float	lengthHalf = length / 2,
			lengthQuater = lengthHalf / 2,
			k;

	Point left, right, middle, newPoint1, newPoint2;
	left.x = vertex.x - lengthHalf;
	right.x = vertex.x + lengthHalf;
	left.y = vertex.y + sqrt(3.0) / 2 * length;
	right.y = left.y;

	helper->drawLine(vertex.x, vertex.y, left.x, left.y, helper->getBlackColor());
	helper->drawLine(vertex.x, vertex.y, right.x, right.y, helper->getBlackColor());
	helper->drawLine(right.x, right.y, left.x, left.y, helper->getBlackColor());

	newPoint1.x = left.x;
	newPoint1.y = left.y;
	newPoint2.x = right.x;
	newPoint2.y = newPoint1.y;

	for (int i = left.y, k = 0; i > vertex.y; i--, k++)
	{
		newPoint1.y = i;
		newPoint2.y = newPoint1.y;
		newPoint1.x = left.x + k / 1.74;
		newPoint2.x = right.x - k / 1.74;
		helper->drawLine(newPoint1.x, newPoint1.y, newPoint2.x, newPoint2.y, helper->getBlackColor());
	}

	newPoint1.x = vertex.x - lengthQuater;
	newPoint1.y = vertex.y + sqrt(3.0) / 4 * length;
	newPoint2.x = vertex.x + lengthQuater;
	newPoint2.y = newPoint1.y;

	for (int i = newPoint1.y, k = 0; i < left.y; i++, k++)
	{
		newPoint1.y = i;
		newPoint2.y = newPoint1.y;
		newPoint1.x = vertex.x - lengthQuater + k / 1.74;
		newPoint2.x = vertex.x + lengthQuater - k / 1.74;
		helper->drawLine(newPoint1.x, newPoint1.y, newPoint2.x, newPoint2.y, helper->getWhiteColor());
	}
		
	nesting--;

	middle = vertex;
	drawTriangle(middle, lengthHalf, nesting);

	middle.x = vertex.x - lengthQuater;
	middle.y = vertex.y + sqrt(3.0) / 4 * length;
	drawTriangle(middle, lengthHalf, nesting);

	middle.x = vertex.x + lengthQuater;
	middle.y = vertex.y + sqrt(3.0) / 4 * length;
	drawTriangle(middle, lengthHalf, nesting);

	return 1;
}
