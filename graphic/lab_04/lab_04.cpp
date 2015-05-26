#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper * helper = new DrawHelper();
int imageWidth, imageHeight, maxN;
double minR, maxR, minI, maxI;

void inputData()
{
	/* 
	512 512 1000 -1.5 0.7 -1.0 1.0

	Ширина зображення, Висота зображення
	Кількість ітерацій
	Мінімальне Реальне, Максимальне Реальне
	Мінімальне Уявне, Максимальне Уявне.
	*/
	cout << "imageWidth" << endl;
	cin >> imageWidth;

	cout << "imageHeight" << endl;
	cin >> imageHeight;

	cout << "maxN" << endl;
	cin >> maxN;

	cout << "minR" << endl;
	cin >> minR;

	cout << "maxR" << endl;
	cin >> maxR;

	cout << "minI" << endl;
	cin >> minI;

	cout << "maxI" << endl;
	cin >> maxI;
}

int _tmain(int argc, _TCHAR* argv[])
{
	helper->setTerminalColor();
	inputData();

	helper->pause();
	helper->clearScreen();
	drawMandelbrot();
	helper->pause();
	helper->clearScreen();
	drawJulia();
	helper->pause();
	helper->clearScreen();
	return 0;
}


int drawMandelbrot()
{
	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToReal(y, imageHeight, minI, maxI);

			int n = findMandelbrot(cr, ci, maxN);
			int r = (n % 256);
			int g = (n % 256);
			int b = (n % 256);
			helper->drawPixel(x, y, helper->createColor(r, g, b));
		}
	}

	return 0;
}

int drawJulia()
{
	int x, y, k, r, g, b;

	double a = 640 * 0.6;
	double b1 = 480 * 0.6;
	double Xk, Yk, Xk1, Yk1,
        Xmin = -1.7,
        Ymin = -1.8,
        Xmax = 2.1,
        Ymax = 2.3;

	double minR, maxR, minI, maxI;

	double dX = (Xmax - Xmin) / (a - 1);
	double dY = (Ymax - Ymin) / (b1 - 1);

	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			Xk = Xmin + x*dX;
			Yk = Ymin + y*dY;
			k = 0;

			while (k<1000)
			{
				k = k + 1;
				Xk1 = 2 * Xk / 4 + (Xk*Xk - Yk*Yk) / (2 * (Xk*Xk + Yk*Yk)*(Xk*Xk + Yk*Yk));
				Yk1 = 2 * Yk / 4 - (2 * Xk*Yk) / (4 * (Xk*Xk + Yk*Yk)*(Xk*Xk + Yk*Yk));
				Xk = Xk1;
				Yk = Yk1;
			}

			if (sqrt((Xk - 1)*(Xk - 1) + Yk*Yk) < 1) {
				helper->drawPixel(x, y, helper->createColor(0, 0, 255));
			}
			else if (sqrt((Xk + 1 / 2)*(Xk + 1 / 2) + (Yk - 0.866)*(Yk - 0.866)) < 1) {
				helper->drawPixel(x, y, helper->createColor(0, 255, 0));
			}
			else if (sqrt((Xk + 1 / 2)*(Xk + 1 / 2) - (Yk + 0.866)*(Yk + 0.866)) < 1) {
				helper->drawPixel(x, y, helper->createColor(255, 0, 0));
			}
		}
	}

	return 0;
}

int findMandelbrot(double cr, double ci, int max_iterations)
{
	int i = 0;
	double zr = 0.0, zi = 0.0;
	while (i < max_iterations && zr * zr + zi * zi < 4.0)  {
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr  * zi + ci;
		zr = temp;
		i++;
	}
	return i;
}

double mapToReal(int x, int imageWidth, double minR, double maxR)
{
	double range = maxR - minR;
	return x* (range / imageWidth) + minR;

}

double mapToImaginary(int y, int imageHeight, double minI, double maxI)
{
	double range = maxI - minI;

	return y* (range / imageHeight) + minI;
}