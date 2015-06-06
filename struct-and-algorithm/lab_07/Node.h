#include "stdafx.h"

class Node
{
private:
	Node * next;
	Node * previous;
	int value;
public:
	Node();
	void setNext(Node *list);
	Node *getNext();
	void setPrevious(Node *list);
	Node *getPrevious();
	void setValue(int value);
	int getValue();
	~Node();
};
