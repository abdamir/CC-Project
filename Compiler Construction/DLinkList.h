#pragma once
#include<iostream>
#include<string>
using namespace std;
struct Node
{
	string data;
	int LineNo;
	Node* next, * prev;
	Node()
	{
		this->next = this->prev = NULL;
		LineNo = 0;
	}
};
class DLinkList
{
	Node* First, * Last, * ITR;
public:
	DLinkList();
	void InsertNode(string data,int line=0);
	void Show();
	void ResetITR();
	void MvetoNxt();
	void MvetoPrv();
	string GetCurrent();
	Node* GetFirst();
	void showThreeAddress();
	bool isEmpty();
	void InsertAtLine(int Line, string data);
	void InsertAtLinev2(int Line, string data);
};

