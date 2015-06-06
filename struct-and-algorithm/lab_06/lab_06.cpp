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

MyList * searchByPosition(MyList * searchList, int position)
{
	if (position <= 1) {   // ���� ������� ������ ��� ����� 1, ���������� �������
		return searchList; // ���������� ������� �������
	}

	position--; // ���� �������� ������ 1, �� �� ������ ���� ������
	return searchByPosition(searchList->getNext(), position); // ��������� ���������� ����� ������
}

MyList * searchElement()
{
	int position;

	cout << "Please, enter element position (start from 1):" << endl;
	cin >> position;

	return searchByPosition(head, position);
}

void searchElementAndOutput()
{
	MyList * result;

	result = searchElement();

	cout << "Result:" << endl;
	cout << result->getValue() << endl;

	system("pause");
}

void insertElement()
{
	MyList * current, * newList, * previous;
	int value;

	current = searchElement(); // ������� ������� ������� �� ������ �������
	newList = new MyList; // ������� �����, ������� ����� �������� � �������� ������

	cout << "Please, enter new element value:" << endl;
	cin >> value;

	previous = current->getPrevious(); // �����  ��������� �� ���������� ������� �� ��������

	newList->setPrevious(previous); // ������ ��������� �� ���������� ������� ��� ������
	newList->setNext(current); // ������ ������� ������� ��� ��������� ��� ������
	newList->setValue(value);

	current->setPrevious(newList); // ������ �������� ��������  ���������� ����� �������
	previous->setNext(newList); // ������ ����������� ��������� ��������� �����

}

void outputElementsRecursevly(MyList * output, int position = 1)
{
	if (output == NULL)
	{
		return;
	}

	cout << position << ": " << output->getValue();

	if (output->getNext() == NULL)
	{
		return;
	}
	else 
	{
		cout << ", ";
		position++;
		outputElementsRecursevly(output->getNext(), position);
	}

}

void outputList()
{
	cout << "Current list: [ ";
	outputElementsRecursevly(head);
	cout << " ]" << endl << endl;
}

void deleteElementByPosition(int position)
{
	MyList *  current, * previous, * next;
	current = searchByPosition(head, position);

	previous = current->getPrevious();
	next = current->getNext();

	if (next != NULL)
	{
		next->setPrevious(previous);
	}
	
	if (previous != NULL)
	{
		previous->setNext(next);
	}

	if (previous == NULL)
	{
		head = next;
	}
	
}

void deleteElement()
{
	
	int position;

	outputList();

	cout << "Please, enter element position (start from 1):" << endl;
	cin >> position;

	deleteElementByPosition(position);
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
		cout << "4. Search element from the head" << endl;
		cout << "5. Insert element into list" << endl;
		cout << "6. Delete element from list" << endl;

		cout << "9. Exit" << endl;
		cout << endl;

		outputList();

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
			case 1: { createList();  break; }
			case 2: { pushToTop();  break; }
			case 3: { pushToEnd();  break; }
			case 4: { searchElementAndOutput(); break; }
			case 5: { insertElement(); break; }
			case 6: { deleteElement(); break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}
	return 0;

}

