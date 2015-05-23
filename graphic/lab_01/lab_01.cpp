#include "stdafx.h"

int Wxlef = 0;
int Wxrig = 200;
int Wybot = 200;
int Wytop = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	float x0, y0, x1, y1;
	int result;

	cout << "A (x, y)" << endl;
	cin >> x0;
	cin >> y0;

	cout << "B (x, y)" << endl;
	cin >> x1;
	cin >> y1;

	result = V_CSclip(&x0, &y0, &x1, &y1);

	cout << x0 << endl;
	cout << y0 << endl;
	cout << x1 << endl;
	cout << y1 << endl;

	cout << result << endl;
	_getch();
	return 0;
}

/*--------------------------------------------------- V_CSclip
* Реализует алгоритм отсечения Коэна-Сазерленда с
* кодированием концов отсекаемого отрезка
*
* int  V_CSclip (float *x0, float *y0, float *x1, float *y1)
*
* Отсекает отрезок, заданный значениями координат его
* точек (x0,y0), (x1,y1), по окну отсечения, заданному
* глобальными скалярами Wxlef, Wybot, Wxrig, Wytop
*
* Конечным точкам отрезка приписываются коды,
* характеризующие его положение относительно окна отсечения
* по правилу:
*
*  1001 | 1000 | 1010
*  -----|------|-----
*       | Окно |
*  0001 | 0000 | 0010
*  -----|------|-----
*  0101 | 0100 | 0110
*
*  Отрезок целиком видим если оба его конца имеют коды 0000
*  Если логическое И кодов концов не равно 0, то отрезок
*  целиком вне окна и он просто отбрасывается.
*  Если же результат этой операции = 0, то отрезок
*  подозрительный. Он может быть и вне и пересекать окно.
*  Для подозрительных отрезков определяются координаты их
*  пересечений с теми сторонами, с которыми они могли бы
*  пересечься в соответствии с кодами концов.
*  При этом используется горизонтальность и вертикальность
*  сторон окна, что позволяет определить одну из координат
*  без вычислений.
*  Часть отрезка, оставшаяся за окном отбрасывается.
*  Оставшаяся часть отрезка проверяется на возможность его
*  принятия или отбрасывания целиком. Если это невозможно,
*  то процесс повторяется для другой стороны окна.
*  На каждом цикле вычислений конечная точка отрезка,
*  выходившая за окно, заменяется на точку, лежащую или на
*  стороне окна или его продолжении.
*
*  Вспомогательная процедура Code вычисляет код положения
*  для конца отрезка.
*
*/
static float  CSxn, CSyn;   /* Координаты начала отрезка */

static int  CScode(void)  /* Определяет код точки xn, yn */
{
	register int  i;
	i = 0;
	if (CSxn < Wxlef) ++i; else
	if (CSxn > Wxrig) i += 2;
	if (CSyn < Wybot) i += 4; else
	if (CSyn > Wytop) i += 8;
	return (i);
}  /* CScode */

int  V_CSclip(float *x0, float *y0, float *x1, float *y1)
{
	float  CSxk, CSyk;   /* Координаты конца отрезка  */
	int    cn, ck,       /* Коды концов отрезка */
		visible,      /* 0/1 - не видим/видим*/
		ii, s;        /* Рабочие переменные  */
	float  dx, dy,       /* Приращения координат*/
		dxdy, dydx,    /* Наклоны отрезка к сторонам */
		r;            /* Рабочая переменная  */

	CSxk = *x1; CSyk = *y1;
	CSxn = *x1; CSyn = *y1; ck = CScode();
	CSxn = *x0; CSyn = *y0; cn = CScode();

	/* Определение приращений координат и наклонов отрезка
	* к осям. Заодно сразу на построение передается отрезок,
	* состоящий из единственной точки, попавшей в окно
	*/
	dx = CSxk - CSxn;
	dy = CSyk - CSyn;
	if (dx != 0) dydx = dy / dx; else {
		if (dy == 0) {
			if (cn == 0 && ck == 0) goto out; else goto all;
		}
	}
	if (dy != 0) dxdy = dx / dy;

	/* Основной цикл отсечения */
	visible = 0;  ii = 4;
	do {
		if (cn & ck) break;       /* Целиком вне окна    */
		if (cn == 0 && ck == 0) { /* Целиком внутри окна */
			++visible;  break;
		}
		if (!cn) {                /* Если Pn внутри окна, то */
			s = cn; cn = ck; ck = s;  /* перестить точки Pn,Pk и */
			r = CSxn; CSxn = CSxk; CSxk = r;  /* их коды, чтобы Pn  */
			r = CSyn; CSyn = CSyk; CSyk = r;  /* оказалась вне окна */
		}
		/* Теперь отрезок разделяется. Pn помещается в точку
		* пересечения отрезка со стороной окна.
		*/
		if (cn & 1) {         /* Пересечение с левой стороной */
			CSyn = CSyn + dydx * (Wxlef - CSxn);
			CSxn = Wxlef;
		}
		else if (cn & 2) {  /* Пересечение с правой стороной*/
			CSyn = CSyn + dydx * (Wxrig - CSxn);
			CSxn = Wxrig;
		}
		else if (cn & 4) {  /* Пересечение в нижней стороной*/
			CSxn = CSxn + dxdy * (Wybot - CSyn);
			CSyn = Wybot;
		}
		else if (cn & 8) {  /*Пересечение с верхней стороной*/
			CSxn = CSxn + dxdy * (Wytop - CSyn);
			CSyn = Wytop;
		}
		cn = CScode();        /* Перевычисление кода точки Pn */
	} while (--ii >= 0);
	if (visible) {
	out:  *x0 = CSxn;  *y0 = CSyn;
		*x1 = CSxk;  *y1 = CSyk;
	}
all:
	return (visible);
}  /* V_CSclip */

#include<windows.h>
#include<iostream>
#include <cmath>
#include <conio.h>
#include <cstdlib>

using namespace std;

#define LEFT  1  /* двоичное 0001 */
#define RIGHT 2  /* двоичное 0010 */
#define BOT   4  /* двоичное 0100 */
#define TOP   8  /* двоичное 1000 */

/* Вычисление кода точки
r : указатель на struct rect; p : указатель на struct point */
#define vcode(r, p) \
	((((p)->x < (r)->x_min) ? LEFT : 0) +  /* +1 если точка левее прямоугольника */ \
	(((p)->x >(r)->x_max) ? RIGHT : 0) +  /* +2 если точка правее прямоугольника */\
	(((p)->y < (r)->y_min) ? BOT : 0) +  /* +4 если точка ниже прямоугольника */  \
	(((p)->y >(r)->y_max) ? TOP : 0))     /* +8 если точка выше прямоугольника */

/* точка */
struct point {
	double x, y;
};

/* прямоугольник */
struct rect {
	double x_min, y_min, x_max, y_max;
};



int cohen_sutherland(const struct rect *r, struct point *a, struct point *b);


void main() {
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

