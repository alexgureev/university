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

	head = listTmp; // ������ ��������� �� ������� ������
	last = listTmp; // ������ ��������� �� ����� ������

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
	
	newList->setNext(head); // ��� ����� �������� ������ ��������� ������� ������� ������
	head->setPrevious(newList); // ��� ������� ������ ������ ������ �������� ��� ����������
	head = newList; // ������ ����� ��������� �� �������

	newList->setValue(value);
}

void pushToEnd()
{
	MyList *newList;
	int value;

	newList = new MyList;

	cout << "Please, enter element value:" << endl;
	cin >> value;

	newList->setPrevious(last); // ��� ������ �������� ������ ��������� �� ����������
	last->setNext(newList); // ��� ���������� �������� ������ �������� ����������
	last = newList;		// ������ ��������� �� ����� �������

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

