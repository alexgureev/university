// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

void plot(int x1, int y1);
void Bresenham(int x1,
	int y1,
	int const x2,
	int const y2);
