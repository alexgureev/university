// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <iomanip>

using namespace std;

/*
	Створити масив структур.

	Кожна структура складається з таких елементів:
	місто,
	інститут,
	факультет.
*/
struct Speciality
{
	string title;
	int places;
};

struct Faculty
{
	string title;
	Speciality specialities[10];
};

struct Institute
{
	string title;
	Faculty faculties[10];
};

struct City
{
	string title;
	Institute institutes[10];
};

void setData();
void setCities(FILE * fp, int i = 0);
void setInstitutes(City *city);
void setFaculties(Institute *institute);
void setSpecialities(Faculty *faculty);
void readData();
void outputBullet(int i);
int countCitiesInFile();
void searchSubquery();
void searchAndOutputSpecialityInCity(City * city, string query);
string inputSearchQuery();
void searchInstitutes();
void searchAndOutputInstitutes(City * city, string query);

// TODO: reference additional headers your program requires here
