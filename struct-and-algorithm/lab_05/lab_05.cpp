#include "stdafx.h"

Item *head, *current, *last;
int T, t1, t2, n;

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
	head = NULL;
	current = NULL;
	last = NULL;

	// @todo data validation
	cout << "Enter number of customers:" << endl;
	cin >> n;

	cout << "Enter max time of serving:" << endl;
	cin >> t1;

	cout << "Enter the max period of new customer appear:" << endl;
	cin >> t2;

	cout << "Enter time for modeling:" << endl;
	cin >> T;

}

void modelateQueue()
{
	createQueue();

	cout << "Starting with queue:" << endl;

	outputQueueWithGlue(head, ", ");

	int currentCustomer = 0;
	int currentServing = 0;
	int currentEnqueue = 0;
	int waiting = 0;

	for (int i = 1; i <= T; i++)										// начинаем цикл моделирования
	{
		if (waiting == 1)												// если очередь пустая, выводим пропуск
		{
			cout << " ";
		}
		else if(currentCustomer > 0)									// если в этом ходу обслуживается клиент, выводим .
		{
			cout << ".";
		}

		if (currentEnqueue == t2)										// пришло время добавить нового клиента в очередь
		{
			currentEnqueue = 0;											// сбрасываем счетчик

			int newCustomer = getRandomTime(t1);						// генерируем новому клиенту время обслуживания

			//cout << "+" << newCustomer;									// выводим событие о том что добавился клиент в конец очереди

			if (waiting == 1)											// если очередь была пуста, то начинаем обслуживать этого клиента
			{
				currentCustomer = newCustomer;							// начинаем обслуживать с этого тика
				waiting = currentServing = 0;							// сбрасываем счетчик обслуживания и убираем флаг ожидания
			}
			else														// если уже обслуживается клиент, то добавляем текущего в очередь
			{
				enqueue(newCustomer);									// добавляем клиента в очередь 
			}
		}

		if (currentServing == currentCustomer)							// пришло время убрать из очереди клиента
		{ 

			if (currentCustomer != 0)
			{
				currentCustomer = 0;
				cout << "|";// << currentCustomer;							// выводим событие исключения из очереди
			}
			
			if (head == NULL)											// если очередь пустая
			{
				waiting = 1;											// выставляем флаг ожидания
			}
			else														// если в очереди есть клиенты, начинаем обслуживать нового
			{
				currentServing = 0;										// обнуляем счетчик обслуживания
				currentCustomer = dequeue();							// берем время обслуживания из очереди
			}
		}

		currentServing++;
		currentEnqueue++;
	}

	cout << endl << endl << "Resulting queue: " << endl;

	outputQueueWithGlue(head, ", ");
	cout << "Current progress:" << endl;

	cout << currentServing << "/" << currentCustomer;

	_getch();
}

void processTick(int tick)
{

}

void createQueue()
{
	for (int i = 0; i < n; i++)
	{
		enqueue(getRandomTime(t1));
	}
}

void outputQueueWithGlue(Item * head, char glue[2])
{
	if (head == NULL)
	{
		cout << "(empty)" << endl;
		return;
	}

	cout << head->serveTime;

	if (head->next != NULL)
	{
		cout << glue;
		outputQueueWithGlue(head->next, glue);
	}
	else
	{
		cout << endl;
	}
}

int getRandomTime(int max)
{
	return rand() % (max) + 1;
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
		cout << "2. Modelate queue" << endl;
		cout << "9. Exit" << endl;
		cout << endl;

		int key;

		cout << "Choose menu:";
		cin >> key;

		system("cls");

		switch (key)
		{
			case 1: { inputData();  break; }
			case 2: { modelateQueue();  break; }
			case 9: { flag = 1; break; }

			default: break;
		}

	}
	return 0;
}

