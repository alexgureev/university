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
	Item * temporaryStack = new Item();
	int temporaryValue;

	for (int i = 0; i < size; i++)
	{
		temporaryValue = pop(head);

		if (i == 0)
		{
			temporaryStack->value = temporaryValue;
			temporaryStack->next = NULL;
		}
		else
		{
			push(temporaryStack, temporaryValue);
		}
	}

	head = temporaryStack;
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

void compareStacks()
{
	Item * fillStack = new Item;
	cout << "First stack: " << endl;
	outputStackWithGlue(stack[0], ", ");

	cout << "Second stack: " << endl;
	outputStackWithGlue(stack[1], ", ");

	if (isStacksEqual(stack[0], stack[1]) == true)
	{
		revert(stack[0], counter[0]);
		cout << "Reverted stack: " << endl;
		outputStackWithGlue(stack[0], ", ");
	}
	else 
	{
		comparisonWalkAndFill(stack[0], stack[1], fillStack, true);
		comparisonWalkAndFill(stack[1], stack[0], fillStack, false);
		cout << "Diff stack: " << endl;
		outputStackWithGlue(fillStack, ", ");
	}

	_getch();
}

void outputStackWithGlue(Item * head, char glue[2])
{
	cout << head->value;

	if (head->next != NULL)
	{
		cout << glue;
		outputStackWithGlue(head->next, glue);
	}
	else
	{
		cout << endl;
	}
}

bool isStacksEqual(Item * &firstStack, Item * &secondStack)
{
	if (firstStack->next == NULL && secondStack->next != NULL ||
		firstStack->next != NULL && secondStack->next == NULL)
	{
		return false;
	}

	if (firstStack->value != secondStack->value)
	{
		return false;
	}

	if (firstStack->next == NULL && secondStack->next == NULL)
	{
		return true;
	} 

	return isStacksEqual(firstStack->next, secondStack->next);
}

void comparisonWalkAndFill(Item * walkStack, Item * checkStack, Item * &resultStack, bool first)
{
	if (isValueExist(checkStack, walkStack->value) == false) 
	{
		if (first == true)
		{
			resultStack->value = walkStack->value;
			resultStack->next = NULL;
		}
		else
		{
			push(resultStack, walkStack->value);
		}
		
	}

	if (walkStack->next == NULL)
	{
		return;
	}

	comparisonWalkAndFill(walkStack->next, checkStack, resultStack, false);
}

bool isValueExist(Item * head, int value)
{
	if (head->value == value)
	{
		return true;
	}

	if (head->next == NULL)
	{
		return false;
	}

	return isValueExist(head->next, value);
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
		cout << "5. Compare stacks" << endl;
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
			case 5: { compareStacks();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}

	return 0;
}

