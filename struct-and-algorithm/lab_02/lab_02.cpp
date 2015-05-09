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

struct Speciality
{
	char title[10];
	int places;
};

struct Faculty
{
	char title[10];
	Speciality specialities[10];
};

struct Institute
{
	char title[10];
	Faculty faculties[10];
};

struct City
{
	char title[10];
	Institute institutes[10];
};

FILE * fp;

/*
   Створити масив структур. 

   Кожна структура складається з таких елементів: 
		місто, 
		інститут, 
		факультет. 
		
	Для інституту задається план прийому на перший курс. 
	Для факультету задається список спеціальностей.  
	Створений масив записати до бінарного файла. 

	Передбачити можливість: 
		доповнити файл, 
		замінити дані в файлі, 
		видалити дані з файлу. 
		
	Реалізувати запити, визначивши: 
		1) список спеціальностей, що містять у своїй назві 
			слова "комп'ютерний" або "автоматизований"; 
		2) факультети й інститути, де є задана спеціальність; 
		3) факультет, інститут і місто, де на вказану 
		користувачем спеціальність виділено найбільше місць. 
 */

void setData();
void setCities(FILE * fp);
void setInstitutes(City city);
void setFaculties(Institute institute);
void setSpecialities(Faculty faculty);
void readData();

void setData()
{
	if (fp != NULL) {
		remove("fp.dat");
	}

	fopen_s(&fp, "fp.dat", "wb");

	setCities(fp);
	
	fclose(fp);
}

void setCities(FILE * fp)

{
	City cities[10];
	int i = 0;
	char answer;

	do
	{
		cout << "City title: " << endl;
		cin >> cities[i].title;
		setInstitutes(cities[i]);

		cout << "One more city? y/n" << endl;
		answer = _getch();
		
		fwrite(&cities[i], sizeof(struct City), 1, fp);
		
		i++;
	} while (answer != 'n' || i >= 10);
}

void setInstitutes(City city)
{
	char answer;
	int i = 0;

	do
	{
		cout << "Insitute title: " << endl;
		cin >> city.institutes[i].title;
		setFaculties(city.institutes[i]);

		cout << "One more institute? y/n" << endl;
		answer = _getch();
		i++;

	} while (answer != 'n' || i >= 10);
}

void setFaculties(Institute institute)
{
	char answer;
	int i = 0;

	do
	{
		cout << "Faculty title: " << endl;
		cin >> institute.faculties[i].title;
		setSpecialities(institute.faculties[i]);

		cout << "One more faculty? y/n" << endl;
		answer = _getch();
		i++;

	} while (answer != 'n' || i >= 10);
}

void setSpecialities(Faculty faculty)
{
	char answer;
	int i = 0;

	do
	{
		cout << "Speciality title: " << endl;
		cin >> faculty.specialities[i].title;

		cout << "Places: " << endl;
		cin >> faculty.specialities[i].places;

		cout << "One more speciality? y/n" << endl;
		answer = _getch();
		i++;

	} while (answer != 'n' || i >= 10);
}

void readData()
{
	City city;
	int i = 0;
	fp = fopen("fp.dat", "rb");
	
	/*if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}*/

	fread(&city, sizeof(struct City), 1, fp);

	while (!(feof(fp))) 
	{
		cout.setf(ios::left);
		cout << setw(12) <<  city.title << endl;

		fread(&city, sizeof(struct City), 1, fp);
	}

	fclose(fp);
	_getch();
}

int _tmain(int argc, _TCHAR* argv[])
{
	system("cls");
	cout << " MENU" << endl;
	cout << "1. Set data" << endl;
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
		case 1: { setData();  break; }
		case 2: { readData();  break; }
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

