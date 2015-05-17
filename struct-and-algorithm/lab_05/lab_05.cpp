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
	Використовуючи динамічну структуру черги,
	промоделювати процес обслуговування черги покупців в магазині.

	У магазині стоїть черга з n покупців.

	Час обслуговування покупця з черги -
	це випадкове ціле число в діапазоні від 1 до t1.

	Час додавання нового покупця до черги -
	це випадкове ціле число в діапазоні від 1 до t2.

	Промоделювати стан черги (тобто показати час виникнення подій -
	обслуговування та додавання покупця) за період часу T (T>t1, T>t2).

	Вивести на екран залишок черги
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

