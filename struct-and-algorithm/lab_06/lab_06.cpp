#include "stdafx.h"
#include "List.h"

MyList * head, * last;

void createList()
{
	MyList *listTmp;
	int value;

	listTmp = new MyList;

	cout << "Please, enter element value:" << endl;
	cin >> value;

	listTmp->setValue(value);

	head = listTmp; // ставим указатель на вершину списка
	last = listTmp; // ставим указатель на конец списка

	cout << "List was succesfully created." << endl;
	system("pause");
}

void pushToTop()
{
	MyList *newList;
	int value;

	newList = new MyList;

	cout << "Please, enter element value:" << endl;
	cin >> value;
	
	newList->setNext(head); // для новго элемента ставим следующим текущую вершину списка
	head->setPrevious(newList); // для вершины списка ставим новыйв эелемент как предыдущий
	head = newList; // ставим новый указатель на вершину

	newList->setValue(value);
}

void pushToEnd()
{
	MyList *newList;
	int value;

	newList = new MyList;

	cout << "Please, enter element value:" << endl;
	cin >> value;

	newList->setPrevious(last); // для нового эелмента ставим указатель на предыдущий
	last->setNext(newList); // для последнего элемента ставим значение следующего
	last = newList;		// ставим указатель на новый элемент

	newList->setValue(value);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Create list" << endl;
		cout << "2. Put element to the head of list" << endl;
		cout << "3. Put element to the end of list" << endl;
		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
			case 1: { createList();  break; }
			case 2: { pushToTop();  break; }
			case 3: { pushToEnd();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}
	return 0;

}

