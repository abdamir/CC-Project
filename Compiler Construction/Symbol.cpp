#include "Symbol.h"

void Symbol::setValues(string token, string datatype, bool valid, bool iskeyword, bool isOperator, bool isIdentifier, bool isDigit)
{
	this->token = token;
	this->datatype = datatype;
	this->valid = valid;
	this->isKeyword = iskeyword;
	this->isOperator = isOperator;
	this->isIdentifier = isIdentifier;
	this->isDigit = isDigit;
}

bool Symbol::getIsIdentifier()
{
	return isIdentifier;
}

bool Symbol::getIsDigit()
{
	return isDigit;
}

bool Symbol::isKeyWord()
{
	return isKeyword;
}

bool Symbol::getIsOperator()
{
	return isOperator;
}

string Symbol::getDatatype()
{
	return datatype;
}

void Symbol::Show()
{
	cout << "Token: " << token << endl;
	cout << "DataType: " << datatype << endl;
	cout << "Valid: " << valid << endl;
	cout << "Keyword: " << isKeyword << endl;
	cout << "Operator: " << isOperator << endl;
}
