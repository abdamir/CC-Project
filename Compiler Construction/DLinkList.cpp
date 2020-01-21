#include "DLinkList.h"

DLinkList::DLinkList()
{
	First = Last = ITR = NULL;
}

void DLinkList::InsertNode(string dta, int line)
{
	Node* node = new Node();
	node->data = dta;
	node->LineNo = line;
	if (First == NULL)
		First = Last = ITR = node;
	else
	{
		Last->next = node;
		node->prev = Last;
		Last = node;
	}
}

void DLinkList::Show()
{
	Node* temp = First;
	while (temp!=NULL)
	{
		cout << temp->data << endl;
		temp = temp->next;
	}
}

void DLinkList::ResetITR()
{
	ITR = First;
}

void DLinkList::MvetoNxt()
{
	if (ITR != NULL)
		ITR = ITR->next;
}

void DLinkList::MvetoPrv()
{
	if (ITR != NULL)
		ITR = ITR->prev;
}

string DLinkList::GetCurrent()
{
	if (ITR != NULL)
		return ITR->data;
	else
		return "\0";
}

Node* DLinkList::GetFirst()
{
	return First;
}

void DLinkList::showThreeAddress()
{
	Node *temp = First;
	while (temp != NULL)
	{
		cout << temp->LineNo << ") " << temp->data << endl;
		temp = temp->next;
	}
}

bool DLinkList::isEmpty()
{
	if (ITR == NULL)
		return true;
	else 
		return false;
}

void DLinkList::InsertAtLine(int Line, string d)
{
	Node* temp = First;
	while (temp != NULL)
	{
		if (temp->LineNo == Line)
		{
			temp->data += " " + d;

		}
		temp = temp->next;
	}
}

void DLinkList::InsertAtLinev2(int Line, string d)
{
	Node* temp = First;
	while (temp != NULL)
	{
		if (temp->LineNo == Line)
		{
			int i = temp->data.length()-1;
			while (temp->data[i] != 'o')
			{
				i--;
			}
			i++;
			temp->data.replace(i, temp->data.length() - i," "+ d);
		}
		temp = temp->next;
	}
}
