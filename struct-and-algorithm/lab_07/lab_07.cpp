#include "stdafx.h"
#include "Node.h"

Node * root;
FILE * fp;

bool isChar1BiggerChar2(char * char1, char * char2)
{
	for (int i = 0; i <= 10; i++)
	{
		if (char1[i] == char2[i]) {
			if (i == 10)
			{
				return false;
			}
			else 
			{
				continue;
			}
		}
		else if (char1[i] > char2[i]) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool isChar1EqualChar2(char * char1, char * char2)
{
	for (int i = 0; i <= 10; i++)
	{
		if (char1[i] == char2[i]) {
			if (i == 10)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
}

void findLeafToPush(Node ** node, char * line)
{
	Node * leaf = new Node;
	char nodeValue[100] = (*node)->getValue();

	if (isChar1BiggerChar2(line, nodeValue))
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
	fp = fopen("words.txt", "r");

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

void searchInThreeByKeyword(Node * node, char * keyword)
{
	if (node == NULL) 
	{
		cout << "Dead end" << endl;
		return;
	}

	char nodeValue = node->getValue();
	if (isChar1EqualChar2(&nodeValue, keyword))
	{
		cout << "Matched: " << *keyword << endl;
		return;
	}

	if (isChar1BiggerChar2(&nodeValue, keyword))
	{
		cout << "Go right: " << node->getValue() << "<" <<keyword << endl;
		searchInThreeByKeyword(node->getRight(), keyword);
	}
	else
	{
		cout << "Go left: " << node->getValue() << ">=" << keyword << endl;
		searchInThreeByKeyword(node->getLeft(), keyword);
	}
}

void searchInThree()
{
	char keyword[10];
	cout << "Please, enter subquery:" << endl;
	cin >> keyword;

	searchInThreeByKeyword(root, keyword);
	system("pause");
}

int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Create three from file" << endl;
		cout << "2. Search in three" << endl;

		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{

		case 1: { createThreeFromFile(); break; }
		case 2: { searchInThree(); break; }
		case 9: { flag = 1; break; }

		default: break;
		}

	}
	return 0;

}

