#include "stdafx.h"
#include "Node.h"

Node * root;
FILE * fp;

void createThreeFromFile()
{
	char line[100];

	int i = 1;
	fp = fopen("text.txt", "r");

	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fread(line, 100, 1, fp);

	system("cls");
	cout << "Cities list:" << endl << endl;

	while (!(feof(fp)))
	{
		cout << line << endl;

		fread(line, 100, 1, fp);
		i++;
	}

	fclose(fp);
	_getch();
}

int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Create three from file" << endl;

		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{

		case 1: { createThreeFromFile(); break; }
		case 9: { flag = 1; break; }

		default: break;
		}

	}
	return 0;

}

