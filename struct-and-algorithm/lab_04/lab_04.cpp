#include "stdafx.h"

struct Item
{
	int value;
	Item * next;
};

Item * head, *current;
int element, counter;

void createStacks()
{
	counter = 1;
	int output;
	char answer;

	do
	{
		cout << "Please enter element [" << counter << "]:";
		cin >> element;

		push(&element);

		cout << "One more element? y/n" << endl;
		answer = _getch();

		counter++;
	
	} while (answer != 'n');

	for (int i = 0; i < counter; i++)
	{
		if (head == NULL) {
			continue;
		}

		pop(&output);
		cout << output << endl;
	}
}

void push(int * value)
{
	current = new Item;
	current->value = * value;
	current->next = head;
	head = current;
}

void pop(int * value)
{
	current = head;
	*value = head->value;
	head = current->next;
	delete current;
}

/*
	�������� ��� ����� �����. 
	����������� �������� ����� � ��������� �� ���������� � ���������� �����. 
	�������� ��������� �����. 
	���� ����� �������, �������� ������� ������ � ���, 
	������ �������� ����� ���� � �䒺���� �������� ���� ��������� �����. 
	������� �� ����� ����� �� ������������ �� ����.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Create stacks" << endl;
		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
			case 1: { createStacks();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}

	return 0;
}

