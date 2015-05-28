#include "stdafx.h"
#include "List.h"

MyList::MyList()
{
}

MyList::~MyList()
{
}

void MyList::setNext(MyList *list)
{
	this->next = list;
}

MyList *MyList::getNext()
{
	return this->next;
}

void MyList::setPrevious(MyList *list)
{
	this->previous = list;
}

MyList *MyList::getPrevious()
{
	return this->previous;
}

void MyList::setValue(int value)
{
	this->value = value;
}

int MyList::getValue()
{
	return this->value;
}
