#include "Stack.h"

Stack::Stack()
{
	Head = NULL;
}

void Stack::push(int L, string d)
{
	Snode* obj = new Snode;
	obj->Line = L;
	obj->data = d;
	if (Head == NULL)
	{
		Head = obj;
		obj->prev = NULL;
	}
	else
	{
		obj->prev = Head;
		Head = obj;
	}
}

void Stack::pop()
{
	if (Head != NULL)
		Head = Head->prev;
}

int Stack::Topline()
{
	return Head->Line;
}

string Stack::TopData()
{
	return Head->data;
}

bool Stack::isEmpty()
{
	if (Head == NULL)
		return true;
	else
		return false;
}


