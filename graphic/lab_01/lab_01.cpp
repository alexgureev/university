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
	while (helper->wait())  {
		helper->drawRectangle(&rectangle);
		helper->drawLine(A.x, A.y, B.x, B.y, helper->getGreenColor());
		result = cohen_sutherland(&rectangle, &A, &B);
		helper->drawLine(A.x, A.y, B.x, B.y, helper->getBlackColor());
	}
	
	helper->clearScreen();
	helper->pause();
	return 0;
}


/* Если отрезок ab не пересекает прямоугольник r, функция возвращает -1;
если отрезок ab пересекает прямоугольник r, функция возвращает 0 и отсекает
те части отрезка, которые находятся вне прямоугольника */
int cohen_sutherland(const struct Square *r, struct Point *a, struct Point *b)
{
	int code_a, code_b, code; /* код концов отрезка */
	struct Point *c; /* одна из точек */

	code_a = vcode(r, a);
	code_b = vcode(r, b);

	/* пока одна из точек отрезка вне прямоугольника */
	while (code_a | code_b) {
		/* если обе точки с одной стороны прямоугольника, то отрезок не пересекает прямоугольник */
		if (code_a & code_b)
			return -1;

		/* выбираем точку c с ненулевым кодом */
		if (code_a) {
			code = code_a;
			c = a;
		}
		else {
			code = code_b;
			c = b;
		}

		/* если c левее r, то передвигаем c на прямую x = r->xLeftTop
		если c правее r, то передвигаем c на прямую x = r->xRightBottom */
		if (code & LEFT) {
			c->y += (a->y - b->y) * (r->xLeftTop - c->x) / (a->x - b->x);
			c->x = r->xLeftTop;
		}
		else if (code & RIGHT) {
			c->y += (a->y - b->y) * (r->xRightBottom - c->x) / (a->x - b->x);
			c->x = r->xRightBottom;
		}/* если c ниже r, то передвигаем c на прямую y = r->yLeftTop
		 если c выше r, то передвигаем c на прямую y = r->yRightBottom */
		else if (code & TOP) {
			c->x += (a->x - b->x) * (r->yLeftTop - c->y) / (a->y - b->y);
			c->y = r->yLeftTop;
		}
		else if (code & BOT) {
			c->x += (a->x - b->x) * (r->yRightBottom - c->y) / (a->y - b->y);
			c->y = r->yRightBottom;
		}

		/* обновляем код */
		if (code == code_a) {
			a = c;
			code_a = vcode(r, a);
		}
		else {
			b = c;
			code_b = vcode(r, b);
		}
	}
	/* оба кода равны 0, следовательно обе точки в прямоугольнике */
	return 0;
}

