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

/*
	Створити масив структур.

	Кожна структура складається з таких елементів:
	місто,
	інститут,
	факультет.
*/
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

void setData();
void setCities(FILE * fp, int i = 0);
void setInstitutes(City *city);
void setFaculties(Institute *institute);
void setSpecialities(Faculty *faculty);
void readData();
void outputBullet(int i);
int countCitiesInFile();
void searchSubquery();
void searchAndOutputSpecialityInCity(City city);

/*
	Для інституту задається план прийому на перший курс.
	Для факультету задається список спеціальностей.
	Створений масив записати до бінарного файла.
*/
void setData()
{
	if (fp != NULL) {
		remove("fp.dat");
	}

	fopen_s(&fp, "fp.dat", "wb");

	setCities(fp);
	
	fclose(fp);
}

int countCitiesInFile()
{
	City city;
	int i = 1;

	fp = fopen("fp.dat", "rb");
	fread(&city, sizeof(struct City), 1, fp);

	while (!(feof(fp)))
	{
		fread(&city, sizeof(struct City), 1, fp);
		i++;
	}

	fclose(fp);
	return i;
}

void appendData()
{
	City city;

	fp = fopen("fp.dat", "a+b");
	
	cout << "City title: " << endl;
	cin >> city.title;
	
	setInstitutes(&city);

	fwrite(&city, sizeof(City), 1, fp);
	fclose(fp);
}

void setCities(FILE * fp, int i)
{
	City cities[10];
	char answer;

	do
	{
		cout << "City title: " << endl;
		cin >> cities[i].title;
		setInstitutes(&cities[i]);

		cout << "One more city? y/n" << endl;
		answer = _getch();
		
		fwrite(&cities[i], sizeof(City), 1, fp);
		
		i++;
	} while (answer != 'n' || i >= 10);
}

void setInstitutes(City *city)
{
	char answer;
	int i = 0;

	do
	{
		cout << "Insitute title: " << endl;
		cin >> (*city).institutes[i].title;
		setFaculties(&(*city).institutes[i]);

		cout << "One more institute? y/n" << endl;
		answer = _getch();
		i++;

	} while (answer != 'n' || i >= 10);
}

void setFaculties(Institute *institute)
{
	char answer;
	int i = 0;

	do
	{
		cout << "Faculty title: " << endl;
		cin >> (*institute).faculties[i].title;
		setSpecialities(&(*institute).faculties[i]);

		cout << "One more faculty? y/n" << endl;
		answer = _getch();
		i++;

	} while (answer != 'n' || i >= 10);
}

void setSpecialities(Faculty *faculty)
{
	char answer;
	int i = 0;

	do
	{
		cout << "Speciality title: " << endl;
		cin >> (*faculty).specialities[i].title;

		cout << "Places: " << endl;
		cin >> (*faculty).specialities[i].places;

		cout << "One more speciality? y/n" << endl;
		answer = _getch();
		i++;

	} while (answer != 'n' || i >= 10);
}

void outputBullet(int i)
{
	cout << i << ". " << setw(12);
}

void readData()
{
	City city;
	int i = 1;
	fp = fopen("fp.dat", "rb");
	
	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(&city, sizeof(struct City), 1, fp);
	
	system("cls");
	cout << setw(20) << "Cities list:" << endl << endl;

	while (!(feof(fp))) 
	{
		cout.setf(ios::left);
		outputBullet(i);
		cout << city.title << endl;

		fread(&city, sizeof(struct City), 1, fp);
		i++;
	}

	fclose(fp);
	_getch();
}

/*
	1) список спеціальностей, що містять у своїй назві
	слова "комп'ютерний" або "автоматизований";
*/
void searchSubquery()
{
	City city;
	fp = fopen("fp.dat", "rb");

	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(&city, sizeof(struct City), 1, fp);

	while (!(feof(fp)))
	{
		searchAndOutputSpecialityInCity(city);
		fread(&city, sizeof(struct City), 1, fp);
	}

	fclose(fp);
	_getch();
}

void searchAndOutputSpecialityInCity(City city)
{
	cout << city.institutes[0].title << endl; // institutes[0].faculties[0].specialities[0].title << endl;
}

/*
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

int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Set data" << endl;
		cout << "2. List cities" << endl;
		cout << "3. Append data to file" << endl;
		cout << "4. Search specialities with subquery" << endl;
		cout << "5. " << endl;
		cout << "6. " << endl;
		cout << "7. " << endl;
		cout << "8. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
			case 1: { setData();  break; }
			case 2: { readData();  break; }
			case 3: { appendData();  break; }
			case 4: { searchSubquery();  break; }
			case 5: { break; }
			case 6: { break; }
			case 7: { break; }
			case 8: { flag = 1; break; }

			default: break;
		}

	}
	return 0;
}

