// lab_04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

#include <fstream>
#include <iostream>
#include <windows.h>
#include <math.h>
using namespace std;

int findMandelbrot(double cr, double ci, int max_iterations) {
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

double mapToReal(int x, int imageWidth, double minR, double maxR) {
	double range = maxR - minR;
	return x* (range / imageWidth) + minR;

}

double mapToImaginary(int y, int imageHeight, double minI, double maxI) {
	double range = maxI - minI;

	return y* (range / imageHeight) + minI;
}

int mn();

int main() {
	system("color f0");
	ifstream fin("input.txt");
	int imageWidth, imageHeight, maxN;
	double minR, maxR, minI, maxI;
	if (!fin) {
		cout << "Could not open the file!" << endl;
		cin.ignore();
		return 0;
	}
	fin >> imageWidth >> imageHeight >> maxN;
	fin >> minR >> maxR >> minI >> maxI;
	fin.close();

	ofstream fout("output_image.ppm");
	fout << "P3" << endl;
	fout << imageWidth << " " << imageHeight << endl;
	fout << "256" << endl;

	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToReal(y, imageHeight, minI, maxI);

			int n = findMandelbrot(cr, ci, maxN);
			int r = (n % 256);
			int g = (n % 256);
			int b = (n % 256);

			fout << r << " " << g << " " << b << " ";
		}
		fout << endl;
	}
	fout.close();
	cout << "Finished!" << endl;
	mn();
	return 0;
}

int mn()
{
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	int Nx;
	int Ny;
	int k, r, g, b;
	double a = 640 * 0.6;
	double b1 = 480 * 0.6;
	double Xk;
	double Yk;
	double Xk1;
	double Yk1;
	double Xmin = -2;
	double Ymin = -2;
	double Xmax = 2;
	double Ymax = 2;
	double dX = (Xmax - Xmin) / (a - 1);
	double dY = (Ymax - Ymin) / (b1 - 1);
	int imageWidth = 512;
	int imageHeight = 512;

	ofstream fout("output_image2.ppm");
	fout << "P3" << endl;
	fout << imageWidth << " " << imageHeight << endl;
	fout << "256" << endl;

	for (int Ny = 0; Ny < imageHeight; Ny++) {
		for (int Nx = 0; Nx < imageWidth; Nx++) {
			Xk = Xmin + Nx*dX;
			Yk = Ymin + Ny*dY;
			k = 0;
			while (k<1000)
			{
				k = k + 1;
				Xk1 = 2 * Xk / 4 + (Xk*Xk - Yk*Yk) / (2 * (Xk*Xk + Yk*Yk)*(Xk*Xk + Yk*Yk));
				Yk1 = 2 * Yk / 4 - (2 * Xk*Yk) / (4 * (Xk*Xk + Yk*Yk)*(Xk*Xk + Yk*Yk));
				Xk = Xk1;
				Yk = Yk1;
			}
			int r = (k % 256);
			int g = (k % 256);
			int b = (k % 256);
			if (sqrt((Xk - 1)*(Xk - 1) + Yk*Yk)<1)
				fout << "0" << " " << "0" << " " << "255" << " ";  else
			if (sqrt((Xk + 1 / 2)*(Xk + 1 / 2) + (Yk - 0.866)*(Yk - 0.866))<1)
				fout << "0" << " " << "255" << " " << "0" << " "; else
			if (sqrt((Xk + 1 / 2)*(Xk + 1 / 2) - (Yk + 0.866)*(Yk + 0.866))<1)
				fout << "255" << " " << "0" << " " << "0" << " ";
			//fout << r << " " << g << " " << b << " ";
		}
		fout << endl;
	}
	fout.close();
	cout << "Finished!" << endl;
	return 0;
}