#include "stdafx.h"

Item * stack[2];
int element, counter[2];

void createStacks()
{
	for (int i = 0; i <= 1; i++)
	{
		createStack(i);
	}
}

void outputStacks()
{
	for (int i = 0; i <= 1; i++)
	{
		outputStack(i);
	}

	_getch();
}

void createStack(int member)
{
	char answer;
	counter[member] = 0;

	cout << "Creating stack No " << member << endl;

	do
	{
		cout << "Please enter element [" << counter[member] << "]:";
		cin >> element;

		push(stack[member], element);

		cout << "One more element? y/n" << endl;
		answer = _getch();

		counter[member]++;

	} while (answer != 'n');
}


void outputStack(int member)
{
	int output;

	cout << "Outputing stack No " << member << endl;

	for (int i = 0; i < counter[member]; i++)
	{
		if (stack[member] == NULL) {
			continue;
		}

		output = pop(stack[member]);
		cout << output << endl;
	}
}

void push(Item * &head, int value)
{
	Item * newElement = new Item;
	newElement->value = value;
	newElement->next = head;
	head = newElement;
}

int pop(Item * &head)
{
	int value = head->value;
	Item * pointer = head;

	head = head->next;
	delete pointer;
	return value;
}

/*
	Створити два стеки чисел. 
	Передбачити введення чисел з клавіатури та зчитування з текстового файла. 
	Здійснити порівняння стеків. 
	Якщо стеки однакові, здійснити інверсію одного з них, 
	інакше утворити новий стек з від’ємних елементів двох попередніх стеків. 
	Вивести на екран стеки до перетворення та після.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	int flag = 0;

	while (flag == 0)
	{
		system("cls");
		cout << " MENU" << endl;
		cout << "1. Create stacks" << endl;
		cout << "2. Output stacks" << endl;
		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
			case 1: { createStacks();  break; }
			case 2: { outputStacks();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}

	return 0;
}

