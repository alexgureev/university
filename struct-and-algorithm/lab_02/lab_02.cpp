#include "stdafx.h"

FILE * fp;
struct City citiesList[10];

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
	
	cout << "City ID: " << endl;
	cin >> city.id;

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
		cout << "City ID: " << endl;
		cin >> cities[i].id;
		
		cout << "City title: " << endl;
		cin >> cities[i].title;

		setInstitutes(&cities[i]);

		cout << "One more city? y/n" << endl;
		answer = _getch();
		
		fwrite(&cities[i], sizeof(City), 1, fp);
		
		i++;
	} while (answer != 'n' || i >= 10);
}

void editData()
{
	int i = 0, index;
	fp = fopen("fp.dat", "rb");

	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(&citiesList[i], sizeof(struct City), 1, fp);

	system("cls");
	cout << setw(20) << "Cities list:" << endl << endl;

	while (!(feof(fp)))
	{
		cout.setf(ios::left);

		cout 
			<< i 
			<< ". " 
			<< setw(12)
			<< citiesList[i].title
			/*<< " ("
			<< (*cities).id
			<< ") "*/
			<< endl;
		i++;
		fread(&citiesList[i], sizeof(struct City), 1, fp);
	}

	cout << setw(20) << "Please, enter city index to start edit:" << endl;
	cin >> index;

	setInstitutes(&citiesList[index]);

	fclose(fp);

}

void setInstitutes(City *city)
{
	char answer;
	string title;
	int i = 0;

	do
	{
		cout << "Institute title";
		
		if ((*city).institutes[i].title.empty() == false) 
		{
			cout << " (" << (*city).institutes[i].title  << ")";
		}

		cout << ": " << endl;
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
	string title;
	int i = 0;

	do
	{
		cout << "Faculty title";

		if ((*institute).faculties[i].title.empty() == false)
		{
			cout << " (" << (*institute).faculties[i].title << ")";
		}

		cout << ": " << endl;
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
	string title;
	int i = 0, places;

	do
	{
		cout << "Speciality title";

		if ((*faculty).specialities[i].title.empty() == false)
		{
			cout << " (" << (*faculty).specialities[i].title << ")";
		}

		cout << ": " << endl;
		cin >> (*faculty).specialities[i].title;

		cout << "Places";

		if ((*faculty).specialities[i].places >= 0)
		{
			cout << " (" << (*faculty).specialities[i].places << ")";
		}

		cout << ": " << endl;

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
		outputBullet((*city).id);
		cout << (*city).title << endl;

		fread(city, sizeof(struct City), 1, fp);
		i++;
	}

	fclose(fp);
	_getch();
}

/*
	1) список спеціальностей, що містять у своїй назві
	слова "комп'ютерний" або "автоматизований";
*/
void searchSubquery(int type)
{
	City * city = new City;

	fp = fopen("fp.dat", "rb");

	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(city, sizeof(struct City), 1, fp);
	string query = inputSearchQuery();

	while (!(feof(fp)))
	{
		searchAndOutputSpecialityInCity(city, query, type);
		fread(city, sizeof(struct City), 1, fp);
	}

	fclose(fp);
	_getch();
}

string inputSearchQuery()
{
	string query;

	cout << "Please input search query: ";
	cin >> query;

	system("cls");

	return query;
}

/*
	Реалізувати запити, визначивши:
		1) список спеціальностей, що містять у своїй назві
			слова "комп'ютерний" або "автоматизований";
		2) факультети й інститути, де є задана спеціальність;
		3) факультет, інститут і місто, де на вказану
		користувачем спеціальність виділено найбільше місць.
*/
void searchAndOutputSpecialityInCity(City * city, string query, int type)
{
	string instituteResult, facultyResult;
	int counter = 0;

	for (int instituteCount = 0; instituteCount <= 9; instituteCount++)
	{
		Institute institute = (*city).institutes[instituteCount];

		if (institute.title.empty()) { break; }
		instituteResult = institute.title;

		for (int facultyCount = 0; facultyCount <= 9; facultyCount++)
		{
			Faculty faculty = institute.faculties[facultyCount];

			if (faculty.title.empty()) { break; }
			facultyResult = faculty.title;

			for (int specialityCount = 0; specialityCount <= 9; specialityCount++)
			{
				Speciality speciality = faculty.specialities[specialityCount];

				if (speciality.title.empty()) { break; }

				if (speciality.title.find(query) != std::string::npos) 
				{
					switch (type)
					{
						case 1: outputFirstTask(speciality); break;
						case 2: outputSecondTask(instituteResult, facultyResult, speciality); break;
					}
				}
			}
		}
	}
}

/*
	3) факультет, інститут і місто, де на вказану
	користувачем спеціальність виділено найбільше місць.
*/
void searchMaxPlaces()
{
	City * city = new City;
	SearchResult maxResult, tmpResult;
	
	fp = fopen("fp.dat", "rb");

	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(city, sizeof(struct City), 1, fp);
	string query = inputSearchQuery();

	while (!(feof(fp)))
	{
		tmpResult = searchAndReturnSpecialityInCity(city, query);

		if (tmpResult.places > maxResult.places) {
			maxResult = tmpResult;
		}

		fread(city, sizeof(struct City), 1, fp);
	}

	outputThirdTask(maxResult);
	fclose(fp);
	_getch();
}

SearchResult searchAndReturnSpecialityInCity(City *city, string query)
{
	SearchResult result;
	string instituteResult, facultyResult;
	int counter = 0;

	for (int instituteCount = 0; instituteCount <= 9; instituteCount++)
	{
		Institute institute = (*city).institutes[instituteCount];

		if (institute.title.empty()) { break; }
		instituteResult = institute.title;

		for (int facultyCount = 0; facultyCount <= 9; facultyCount++)
		{
			Faculty faculty = institute.faculties[facultyCount];

			if (faculty.title.empty()) { break; }
			facultyResult = faculty.title;

			for (int specialityCount = 0; specialityCount <= 9; specialityCount++)
			{
				Speciality speciality = faculty.specialities[specialityCount];

				if (speciality.title.empty()) { break; }

				if (speciality.title.find(query) == std::string::npos ||
					speciality.places <= result.places)
				{
					continue;
				}
				
				result.city = (*city);
				result.institute = institute;
				result.faculty = faculty;
				result.places = speciality.places;
			}
		}
	}

	return result;
}

void outputFirstTask(Speciality speciality)
{
	cout 
	<< speciality.title
	<< endl;
}

void outputSecondTask(string instituteResult, string facultyResult, Speciality speciality)
{
	cout << instituteResult
		<< " > "
		<< facultyResult
		<< " > "
		<< speciality.title
		<< "("
		<< speciality.places
		<< ")"
		<< endl;
}

/*
	3) факультет, інститут і місто, де на вказану
	користувачем спеціальність виділено найбільше місць.
*/
void outputThirdTask(SearchResult result)
{
	cout << result.city.title
		<< " > "
		<< result.institute.title
		<< " > "
		<< result.faculty.title
		<< "("
		<< result.places
		<< ")"
		<< endl;
}

/*
	Передбачити можливість:
		доповнити файл,
		замінити дані в файлі,
		видалити дані з файлу.
*/

void _remove()
{
	int cityId = 0, k;
	int status = 1, i = -1, j = 0;
	
	FILE *p;

	p = fopen("fp.dat", "rb");
	if (!p)
	{
		system("cls");
		cout << "Register file could not be opened!" << endl;
		return;
	}

	while (!feof(p))
	{
		fread(&citiesList[i], sizeof(struct City), 1, p);
		i++;
	}

	cout << "Enter City NO. to delete from the list: " << endl;
	cin >> cityId;

	for (j = 0; j < i; j++)
	{
		if (cityId == citiesList[j].id)
		{
			for (k = j + 1; k < i; k++)
			{
				memcpy(&citiesList[k - 1], &citiesList[k], sizeof (City));
			}
		}
	}

	fclose(p);

	FILE *fp;
	fp = fopen("fp.dat", "wb");

	for (int l = 0; l < i - 2; l++)
	{
		fwrite(&citiesList[l], sizeof(struct City), 1, fp);
	}

	fclose(fp);
	system("cls");
	cout << "City with NO. " << cityId << " has been removed" << endl;
}

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
		cout << "4. Edit data" << endl;
		cout << "5. Search specialities with subquery" << endl;
		cout << "6. Search institutes and facultes" << endl;
		cout << "7. Search max places" << endl;
		cout << "8. Remove data from list by id" << endl;
		cout << "9. Exit" << endl;
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
			case 4: { editData();  break; }
			case 5: { searchSubquery(1);  break; }
			case 6: { searchSubquery(2);  break; }
			case 7: { searchMaxPlaces(); break; }
			case 8: { _remove();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}

	return 0;
}

