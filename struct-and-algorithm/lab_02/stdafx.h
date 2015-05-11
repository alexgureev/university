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
	�������� ����� ��������.

	����� ��������� ���������� � ����� ��������:
	����,
	��������,
	���������.
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
void searchSubquery(int type);
void searchAndOutputSpecialityInCity(City * city, string query, int type);
string inputSearchQuery();

void outputFirstTask(Speciality speciality);
void outputSecondTask(string instituteResult, string facultyResult, Speciality speciality);
void outputThirdTask(string instituteResult, string facultyResult, Speciality speciality);
