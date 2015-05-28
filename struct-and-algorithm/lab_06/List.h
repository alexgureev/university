#include "stdafx.h"

class MyList
{
private:
	MyList * next;
	MyList * previous;
	int value;
public:
	MyList();
	void setNext(MyList *list);
	MyList *getNext();
	void setPrevious(MyList *list);
	MyList *getPrevious();
	void setValue(int value);
	int getValue();
	~MyList();
};
