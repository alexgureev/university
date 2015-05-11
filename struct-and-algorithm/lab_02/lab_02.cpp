// lab_02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

FILE * fp;

/*
	��� ��������� �������� ���� ������� �� ������ ����.
	��� ���������� �������� ������ ��������������.
	��������� ����� �������� �� �������� �����.
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
	City * city = new City;
	int i = 1;
	fp = fopen("fp.dat", "rb");
	
	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(city, sizeof(struct City), 1, fp);
	
	system("cls");
	cout << setw(20) << "Cities list:" << endl << endl;

	while (!(feof(fp))) 
	{
		cout.setf(ios::left);
		outputBullet(i);
		cout << (*city).title << endl;

		fread(city, sizeof(struct City), 1, fp);
		i++;
	}

	fclose(fp);
	_getch();
}

/*
	1) ������ ��������������, �� ������ � ���� ����
	����� "����'�������" ��� "���������������";
*/
void searchSubquery()
{
	City * city = new City;
	fp = fopen("fp.dat", "rb");

	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(city, sizeof(struct City), 1, fp);
		
	while (!(feof(fp)))
	{
		searchAndOutputSpecialityInCity(city);
		fread(city, sizeof(struct City), 1, fp);
	}
	
	fclose(fp);
	_getch();
}

void searchAndOutputSpecialityInCity(City * city)
{
	for (int instituteCount = 0; instituteCount <= 9; instituteCount++)
	{
		Institute institute = (*city).institutes[instituteCount];

		if (institute.title.empty()) { return; }
		
		for (int facultyCount = 0; facultyCount <= 9; facultyCount++)
		{
			Faculty faculty = institute.faculties[facultyCount];

			if (faculty.title.empty()) { return; }

			for (int specialityCount = 0; specialityCount <= 9; specialityCount++)
			{
				Speciality speciality = faculty.specialities[specialityCount];

				if (speciality.title.empty()) { return; }

				cout << speciality.title << endl;

			}
		}
	}

	//cout << city.institutes[0].title << endl; // institutes[0].faculties[0].specialities[0].title << endl;
}

/*
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

