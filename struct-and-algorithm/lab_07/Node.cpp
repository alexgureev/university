#include "stdafx.h"
#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::setNext(Node *list)
{
	this->next = list;
}

Node *Node::getNext()
{
	return this->next;
}

void Node::setPrevious(Node *list)
{
	this->previous = list;
}

Node *Node::getPrevious()
{
	return this->previous;
}

void Node::setValue(int value)
{
	this->value = value;
}

int Node::getValue()
{
	return this->value;
}
