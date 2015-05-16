#include "stdafx.h"

Item * stack[3];
FILE * fp;
int element, counter[3];
char filePattern[2][20] = { "0-data.txt", "1-data.txt" };

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

void revert(Item * &head, int size)
{
	Item * temporaryStack = new Item;
	int temporaryValue;

	for (int i = 0; i < size; i++)
	{
		temporaryValue = pop(head);
		push(temporaryStack, temporaryValue);
	}

	head = temporaryStack;
	_getch();
}

void saveStacks()
{
	for (int i = 0; i <= 1; i++)
	{
		saveStack(i);
	}
}

void saveStack(int number)
{
	int output;
	fopen_s(&fp, filePattern[number], "w");

	for (int i = 0; i < counter[number]; i++)
	{
		if (stack[number] == NULL) {
			continue;
		}

		output = pop(stack[number]);
		fprintf(fp, "%d", output);

		fputc('\n', fp);
	}

	fclose(fp);
}

void loadStacks()
{
	for (int i = 0; i <= 1; i++)
	{
		loadStack(i);
	}
}

void loadStack(int number)
{
	char * input = new char;
	long int element;
	counter[number] = 0;

	fopen_s(&fp, filePattern[number], "r");

	while (!feof(fp)) {
		fgets(input, 100, fp);

		if (feof(fp)) {
			break;
		}

		counter[number]++;
		element = atol(input);
		push(stack[number], element);
		
	}

	revert(stack[number], counter[number]);

	fclose(fp);
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
		cout << "3. Save stacks to file" << endl;
		cout << "4. Read stacks from file" << endl;
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
			case 3: { saveStacks();  break; }
			case 4: { loadStacks();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}

	return 0;
}

