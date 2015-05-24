#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	system("color f0");
	rect r1;
	point a1, b1;
	cout << "Enter rectangle's borders' coordinates:\nLeft: "; cin >> r1.x_min;
	cout << "Right: "; cin >> r1.x_max;
	cout << "Top: "; cin >> r1.y_min;
	cout << "Bottom: "; cin >> r1.y_max;
	cout << "\nRectangle width = " << r1.x_max - r1.x_min << "; height" << r1.y_max - r1.y_min << endl;

	cout << "Enter line's starting and ending points:\nx1: "; cin >> a1.x; cout << "y1: "; cin >> a1.y;
	cout << "x2: "; cin >> b1.x; cout << "y2: "; cin >> b1.y;
	cout << "\n============================\n\n";
	cout << "Line: \t\t(" << a1.x << "; " << a1.y << ") - (" << b1.x << "; " << b1.y << ")\n";
	int i = 1;

	cohen_sutherland(&r1, &a1, &b1);

	cout << "Rectangle:\t" << "(" << r1.x_min << "; " << r1.y_min << ") - (" << r1.x_max << "; " << r1.y_min << ")\n";
	cout << "\t\t" << "(" << r1.x_max << "; " << r1.y_min << ") - (" << r1.x_max << "; " << r1.y_max << ")\n\n";
	cout << "\nCropped line: (" << a1.x << "; " << a1.y << ") - (" << b1.x << "; " << b1.y << ")\n";
	cout << "\n============================\n\n";
	system("pause");

	return 0;
}

/* Если отрезок ab не пересекает прямоугольник r, функция возвращает -1;
если отрезок ab пересекает прямоугольник r, функция возвращает 0 и отсекает
те части отрезка, которые находятся вне прямоугольника */
int cohen_sutherland(const struct rect *r, struct point *a, struct point *b)
{
	int code_a, code_b, code; /* код концов отрезка */
	struct point *c; /* одна из точек */

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

		/* если c левее r, то передвигаем c на прямую x = r->x_min
		если c правее r, то передвигаем c на прямую x = r->x_max */
		if (code & LEFT) {
			c->y += (a->y - b->y) * (r->x_min - c->x) / (a->x - b->x);
			c->x = r->x_min;
		}
		else if (code & RIGHT) {
			c->y += (a->y - b->y) * (r->x_max - c->x) / (a->x - b->x);
			c->x = r->x_max;
		}/* если c ниже r, то передвигаем c на прямую y = r->y_min
		 если c выше r, то передвигаем c на прямую y = r->y_max */
		else if (code & TOP) {
			c->x += (a->x - b->x) * (r->y_min - c->y) / (a->y - b->y);
			c->y = r->y_min;
		}
		else if (code & BOT) {
			c->x += (a->x - b->x) * (r->y_max - c->y) / (a->y - b->y);
			c->y = r->y_max;
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

