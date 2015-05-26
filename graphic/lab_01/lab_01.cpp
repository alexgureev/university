#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper * helper = new DrawHelper();
Square rectangle;
Point A, B;

void inputData()
{
	cout << "Please, enter coornidates of Left Top corner (x; y):"
		<< endl
		<< "x: "; 
	cin >> rectangle.xLeftTop;
	cout << "y: "; 
	cin >> rectangle.yLeftTop;

	cout << "Please, enter coornidates of Right Bottom corner (x; y):"
		<< endl
		<< "x: "; 
	cin >> rectangle.xRightBottom;
	cout << "y: "; 
	cin >> rectangle.yRightBottom;

	cout << endl
		<< "Width = " 
		<< rectangle.xRightBottom - rectangle.xLeftTop 
		<< "; Height = " 
		<< rectangle.yRightBottom - rectangle.yLeftTop 
		<< endl;

	cout << "Enter line starting point A(x; y)"
		<< endl
		<< "x: ";
	cin >> A.x;
	cout << "y: ";
	cin >> A.y;

	cout << "Enter line ending point B(x; y)"
		<< endl
		<< "x: ";
	cin >> B.x;
	cout << "y: ";
	cin >> B.y;
}

int _tmain(int argc, _TCHAR* argv[])
{
	helper->setTerminalColor();
	inputData();

	helper->pause();
	helper->clearScreen();
	
	int result;

	helper->drawRectangle(&rectangle);
	helper->drawLine(A.x, A.y, B.x, B.y, helper->getGreenColor());
	result = CohenSutherland(&rectangle, &A, &B);
	if (result != -1)
	{
		helper->drawLine(A.x, A.y, B.x, B.y, helper->getBlackColor());
	}
		
	helper->clearScreen();
	helper->pause();
	return 0;
}

int CohenSutherland(const struct Square *r, struct Point *a, struct Point *b)
{
	int codeA, codeB, code;
	struct Point *c;

	codeA = vcode(r, a);
	codeB = vcode(r, b);

	while (codeA | codeB) {
		if (codeA & codeB)
			return -1;

		if (codeA) {
			code = codeA;
			c = a;
		} else {
			code = codeB;
			c = b;
		}

		if (code & LEFT) {
			c->y += (a->y - b->y) * (r->xLeftTop - c->x) / (a->x - b->x);
			c->x = r->xLeftTop;
		} else if (code & RIGHT) {
			c->y += (a->y - b->y) * (r->xRightBottom - c->x) / (a->x - b->x);
			c->x = r->xRightBottom;
		} else if (code & TOP) {
			c->x += (a->x - b->x) * (r->yLeftTop - c->y) / (a->y - b->y);
			c->y = r->yLeftTop;
		} else if (code & BOT) {
			c->x += (a->x - b->x) * (r->yRightBottom - c->y) / (a->y - b->y);
			c->y = r->yRightBottom;
		}

		if (code == codeA) {
			a = c;
			codeA = vcode(r, a);
		} else {
			b = c;
			codeB = vcode(r, b);
		}
	}

	return 0;
}

