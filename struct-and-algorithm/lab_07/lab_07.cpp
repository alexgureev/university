#include "stdafx.h"
#include "Node.h"

Node * root;
FILE * fp;

void findLeafToPush(Node ** node, char * line)
{
	Node * leaf = new Node;

	if ((*node)->getValue() < *line)
	{
		// push to right
		if ((*node)->getRight() == NULL)
		{
			leaf->setValue(line);
			(*node)->setRight(leaf);
		}
		else 
		{
			leaf = (*node)->getRight();
			findLeafToPush(&leaf, line);
		}
	}
	else
	{
		// push to left
		if ((*node)->getLeft() == NULL)
		{
			leaf->setValue(line);
			(*node)->setLeft(leaf);
		}
		else
		{
			leaf = (*node)->getLeft();
			findLeafToPush(&leaf, line);
		}
	}
}

void createRootWithValue(char * line)
{
	root = new Node;
	root->setValue(line);
}

void pushValueIntoThree(char * line)
{
	if (root == NULL) 
	{
		createRootWithValue(line);
	}
	else
	{
		findLeafToPush(&root, line);
	}
}

void createThreeFromFile()
{
	char line[100];

	int i = 1;
	fp = fopen("text.txt", "r");

	if (!fp) {
		cerr << "File doesn`t exist";
		return;
	}

	fgets(line, 100, fp);

	system("cls");
	cout << "Words list:" << endl << endl;

	while (!(feof(fp)))
	{
		cout << line;

		pushValueIntoThree(line);

		fgets(line, 100, fp);
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

