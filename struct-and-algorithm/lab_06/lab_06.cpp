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

MyList * searchByPosition(MyList * searchList, int position)
{
	if (position <= 1) {   // если позиция меньше или равна 1, возвращаем элемент
		return searchList; // возвращаем текущий элемент
	}

	position--; // если значение больше 1, то мы должны идти вглубь
	return searchByPosition(searchList->getNext(), position); // запускаем рекурсивно поиск вглубь
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

	current = searchElement(); // находим текущий элемент на данной позиции
	newList = new MyList; // создаем новый, который будет вставлен в середину списка

	cout << "Please, enter new element value:" << endl;
	cin >> value;

	previous = current->getPrevious(); // берем  указатель на предыдущий эелмент из текущего

	newList->setPrevious(previous); // ставим указатель на предыдущий элемент для нового
	newList->setNext(current); // ставим текущий элемент как следующий для нового
	newList->setValue(value);

	current->setPrevious(newList); // ставим текущему элементу  предыдущим новый элемент
	previous->setNext(newList); // ставим предыдущему следующим элементом новый

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

