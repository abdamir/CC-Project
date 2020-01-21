#pragma once
#include<iostream>
#include<string>
using namespace std;
class Symbol
{
	string token, datatype;
	bool valid, isKeyword, isOperator,isIdentifier,isDigit;
public:
	void setValues(string token,string datatype,bool valid,bool iskeyword,bool isOperator, bool isIdentifier, bool isDigit);
	bool getIsIdentifier();
	bool getIsDigit();
	bool isKeyWord();
	bool getIsOperator();
	string getDatatype();
	void Show();
};

