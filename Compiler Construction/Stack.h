#pragma once
#include<iostream>
#include<string>
using namespace std;
struct Snode
{
	int Line; string data;
	Snode* prev;
	Snode() { prev = NULL; }
};
class Stack
{
	Snode* Head;
public:
	Stack();
	void push(int L,string data);
	void pop();
	int Topline();
	string TopData();
	bool isEmpty();
};

