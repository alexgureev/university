// lab_02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iomanip>

using namespace std;

struct City
{
	char title[10];
	Institute institutes[10];
};

struct Institute
{
	char title[10];
	Faculty faculties[10];
};

struct Faculty
{
	char title[10];
	Speciality specialities[10];
};

struct Speciality
{
	char title[10];
	int places;
};

int i, j;

FILE * fp;

/*
   �������� ����� ��������. 

   ����� ��������� ���������� � ����� ��������: 
		����, 
		��������, 
		���������. 
		
	��� ��������� �������� ���� ������� �� ������ ����. 
	��� ���������� �������� ������ ��������������.  
	��������� ����� �������� �� �������� �����. 
	����������� ���������: 
		��������� ����, 
		������� ��� � ����, 
		�������� ��� � �����. 
		
	���������� ������, ����������: 
		1) ������ ��������������, �� ������ � ���� ���� 
			����� "����'�������" ��� "���������������"; 
		2) ���������� � ���������, �� � ������ ������������; 
		3) ���������, �������� � ����, �� �� ������� 
		������������ ������������ ������� �������� ����. 
 */

void input();

void input()
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	system("cls");
	cout << " MENU" << endl;
	cout << "1. Input" << endl;
	cout << "2. Read data from file" << endl;
	cout << "3. " << endl;
	cout << "4. " << endl;
	cout << "5. " << endl;
	cout << "6. " << endl;
	cout << "7. " << endl;
	cout << "8. " << endl;
	cout << endl;

	int key;

	cout << "Choose menu:";
	cin >> key;

	system("cls");

	switch (key)
	{
		case 1: { break; }
		case 2: { break; }
		case 3: { break; }
		case 4: { break; }
		case 5: { break; }
		case 6: { break; }
		case 7: { break; }
		case 8: { exit(0); break; }

		default: exit(0); break;
	}

	return 0;
}

