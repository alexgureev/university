#include "stdafx.h"
#include "List.h"

MyList * list;

int _tmain(int argc, _TCHAR* argv[])
{
	MyList *list2, *list3, *list1;
	list1 = new MyList;
	list2 = new MyList;
	list3 = new MyList;

	list1->setValue(1);
	list2->setValue(2);
	list3->setValue(3);

	list1->setNext(list2);
	list2->setNext(list3);
	list2->setPrevious(list1);
	list3->setPrevious(list2);

	system("pause");
	return 0;
}

