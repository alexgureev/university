#include "stdafx.h"

Item *head, *current, *last;

void enqueue(int time)
{
	current = new Item;
	current->serveTime = time;
	current->next = NULL;

	if (last == NULL)
	{
		head = current;
	}
	else
	{
		last->next = current;
	}

	last = current;
}

int dequeue()
{
	int result;
	current = head;
	result = head->serveTime;
	head = current->next;

	if (head == NULL)
	{
		last = NULL;
	}

	delete current;

	return result;
}

void inputData()
{

}

/*
	�������������� �������� ��������� �����,
	������������� ������ �������������� ����� �������� � �������.

	� ������� ����� ����� � n ��������.

	��� �������������� ������� � ����� -
	�� ��������� ���� ����� � ������� �� 1 �� t1.

	��� ��������� ������ ������� �� ����� -
	�� ��������� ���� ����� � ������� �� 1 �� t2.

	������������� ���� ����� (����� �������� ��� ���������� ���� -
	�������������� �� ��������� �������) �� ����� ���� T (T>t1, T>t2).

	������� �� ����� ������� �����
*/
int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Input data for modeling" << endl;
		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
			case 1: { inputData();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}
	return 0;
}

