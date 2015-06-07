#include "stdafx.h"
#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::setLeft(Node *node)
{
	this->left = node;
}

Node *Node::getLeft()
{
	return this->left;
}

void Node::setRight(Node *node)
{
	this->right = node;
}

Node *Node::getRight()
{
	return this->right;
}

void Node::setValue(char * value)
{
	this->value = *value;
}

char Node::getValue()
{
	return this->value;
}
