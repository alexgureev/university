#include "stdafx.h"

FILE * fp;
int n, m;
int distanceArray[100][3];

void loadGraphFromFile()
{
	fp = fopen("input.txt", "r");

	fscanf(fp, "%d %d", &n, &m);
	int i = 0;

	while (!feof(fp))
	{
		fscanf(fp,
			"%d %d %d",
			&distanceArray[i][0],
			&distanceArray[i][1],
			&distanceArray[i][2]);

		i++;
	}

	fclose(fp);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Load graph from file" << endl;

		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
		case 1: { loadGraphFromFile(); break; }
		case 9: { flag = 1; break; }

		default: break;
		}

	}
	return 0;

}

