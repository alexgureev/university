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
* ��������� �������� ��������� �����-���������� �
* ������������ ������ ����������� �������
*
* int  V_CSclip (float *x0, float *y0, float *x1, float *y1)
*
* �������� �������, �������� ���������� ��������� ���
* ����� (x0,y0), (x1,y1), �� ���� ���������, ���������
* ����������� ��������� Wxlef, Wybot, Wxrig, Wytop
*
* �������� ������ ������� ������������� ����,
* ��������������� ��� ��������� ������������ ���� ���������
* �� �������:
*
*  1001 | 1000 | 1010
*  -----|------|-----
*       | ���� |
*  0001 | 0000 | 0010
*  -----|------|-----
*  0101 | 0100 | 0110
*
*  ������� ������� ����� ���� ��� ��� ����� ����� ���� 0000
*  ���� ���������� � ����� ������ �� ����� 0, �� �������
*  ������� ��� ���� � �� ������ �������������.
*  ���� �� ��������� ���� �������� = 0, �� �������
*  ��������������. �� ����� ���� � ��� � ���������� ����.
*  ��� �������������� �������� ������������ ���������� ��
*  ����������� � ���� ���������, � �������� ��� ����� ��
*  ���������� � ������������ � ������ ������.
*  ��� ���� ������������ ���������������� � ��������������
*  ������ ����, ��� ��������� ���������� ���� �� ���������
*  ��� ����������.
*  ����� �������, ���������� �� ����� �������������.
*  ���������� ����� ������� ����������� �� ����������� ���
*  �������� ��� ������������ �������. ���� ��� ����������,
*  �� ������� ����������� ��� ������ ������� ����.
*  �� ������ ����� ���������� �������� ����� �������,
*  ���������� �� ����, ���������� �� �����, ������� ��� ��
*  ������� ���� ��� ��� �����������.
*
*  ��������������� ��������� Code ��������� ��� ���������
*  ��� ����� �������.
*
*/
static float  CSxn, CSyn;   /* ���������� ������ ������� */

static int  CScode(void)  /* ���������� ��� ����� xn, yn */
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
	float  CSxk, CSyk;   /* ���������� ����� �������  */
	int    cn, ck,       /* ���� ������ ������� */
		visible,      /* 0/1 - �� �����/�����*/
		ii, s;        /* ������� ����������  */
	float  dx, dy,       /* ���������� ���������*/
		dxdy, dydx,    /* ������� ������� � �������� */
		r;            /* ������� ����������  */

	CSxk = *x1; CSyk = *y1;
	CSxn = *x1; CSyn = *y1; ck = CScode();
	CSxn = *x0; CSyn = *y0; cn = CScode();

	/* ����������� ���������� ��������� � �������� �������
	* � ����. ������ ����� �� ���������� ���������� �������,
	* ��������� �� ������������ �����, �������� � ����
	*/
	dx = CSxk - CSxn;
	dy = CSyk - CSyn;
	if (dx != 0) dydx = dy / dx; else {
		if (dy == 0) {
			if (cn == 0 && ck == 0) goto out; else goto all;
		}
	}
	if (dy != 0) dxdy = dx / dy;

	/* �������� ���� ��������� */
	visible = 0;  ii = 4;
	do {
		if (cn & ck) break;       /* ������� ��� ����    */
		if (cn == 0 && ck == 0) { /* ������� ������ ���� */
			++visible;  break;
		}
		if (!cn) {                /* ���� Pn ������ ����, �� */
			s = cn; cn = ck; ck = s;  /* ��������� ����� Pn,Pk � */
			r = CSxn; CSxn = CSxk; CSxk = r;  /* �� ����, ����� Pn  */
			r = CSyn; CSyn = CSyk; CSyk = r;  /* ��������� ��� ���� */
		}
		/* ������ ������� �����������. Pn ���������� � �����
		* ����������� ������� �� �������� ����.
		*/
		if (cn & 1) {         /* ����������� � ����� �������� */
			CSyn = CSyn + dydx * (Wxlef - CSxn);
			CSxn = Wxlef;
		}
		else if (cn & 2) {  /* ����������� � ������ ��������*/
			CSyn = CSyn + dydx * (Wxrig - CSxn);
			CSxn = Wxrig;
		}
		else if (cn & 4) {  /* ����������� � ������ ��������*/
			CSxn = CSxn + dxdy * (Wybot - CSyn);
			CSyn = Wybot;
		}
		else if (cn & 8) {  /*����������� � ������� ��������*/
			CSxn = CSxn + dxdy * (Wytop - CSyn);
			CSyn = Wytop;
		}
		cn = CScode();        /* �������������� ���� ����� Pn */
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

#define LEFT  1  /* �������� 0001 */
#define RIGHT 2  /* �������� 0010 */
#define BOT   4  /* �������� 0100 */
#define TOP   8  /* �������� 1000 */

/* ���������� ���� �����
r : ��������� �� struct rect; p : ��������� �� struct point */
#define vcode(r, p) \
	((((p)->x < (r)->x_min) ? LEFT : 0) +  /* +1 ���� ����� ����� �������������� */ \
	(((p)->x >(r)->x_max) ? RIGHT : 0) +  /* +2 ���� ����� ������ �������������� */\
	(((p)->y < (r)->y_min) ? BOT : 0) +  /* +4 ���� ����� ���� �������������� */  \
	(((p)->y >(r)->y_max) ? TOP : 0))     /* +8 ���� ����� ���� �������������� */

/* ����� */
struct point {
	double x, y;
};

/* ������������� */
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


/* ���� ������� ab �� ���������� ������������� r, ������� ���������� -1;
���� ������� ab ���������� ������������� r, ������� ���������� 0 � ��������
�� ����� �������, ������� ��������� ��� �������������� */
int cohen_sutherland(const struct rect *r, struct point *a, struct point *b)
{
	int code_a, code_b, code; /* ��� ������ ������� */
	struct point *c; /* ���� �� ����� */

	code_a = vcode(r, a);
	code_b = vcode(r, b);

	/* ���� ���� �� ����� ������� ��� �������������� */
	while (code_a | code_b) {
		/* ���� ��� ����� � ����� ������� ��������������, �� ������� �� ���������� ������������� */
		if (code_a & code_b)
			return -1;

		/* �������� ����� c � ��������� ����� */
		if (code_a) {
			code = code_a;
			c = a;
		}
		else {
			code = code_b;
			c = b;
		}

		/* ���� c ����� r, �� ����������� c �� ������ x = r->x_min
		���� c ������ r, �� ����������� c �� ������ x = r->x_max */
		if (code & LEFT) {
			c->y += (a->y - b->y) * (r->x_min - c->x) / (a->x - b->x);
			c->x = r->x_min;
		}
		else if (code & RIGHT) {
			c->y += (a->y - b->y) * (r->x_max - c->x) / (a->x - b->x);
			c->x = r->x_max;
		}/* ���� c ���� r, �� ����������� c �� ������ y = r->y_min
		 ���� c ���� r, �� ����������� c �� ������ y = r->y_max */
		else if (code & TOP) {
			c->x += (a->x - b->x) * (r->y_min - c->y) / (a->y - b->y);
			c->y = r->y_min;
		}
		else if (code & BOT) {
			c->x += (a->x - b->x) * (r->y_max - c->y) / (a->y - b->y);
			c->y = r->y_max;
		}

		/* ��������� ��� */
		if (code == code_a) {
			a = c;
			code_a = vcode(r, a);
		}
		else {
			b = c;
			code_b = vcode(r, b);
		}
	}
	/* ��� ���� ����� 0, ������������� ��� ����� � �������������� */
	return 0;
}

