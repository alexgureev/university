
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <fstream>
#include <iostream>

using namespace std;

int drawMandelbrot();
int drawJulia();
int findMandelbrot(double cr, double ci, int max_iterations);
double mapToReal(int x, int imageWidth, double minR, double maxR);
double mapToImaginary(int y, int imageHeight, double minI, double maxI);