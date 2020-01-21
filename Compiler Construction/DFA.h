#pragma once
#include<iostream>
#include<string>
#include<map>
#include"DLinkList.h"
#include"Symbol.h"
#include"Tokenizer.h"
using namespace std; 
const int KeyWSize = 9;
string keyword[KeyWSize] = { "for","while","do","int","float","double","if","begin","end" };
string Loops[3] = { "for","while","do" };
string datatype[] = { "int","double","float" };
string ArthimeticOperators[4] = { "+","-","/","*" };
string ComaprisonOperator[4] = { "<",">","=","!" };
int FinalStates[3] = { 2,3,4 };
map<string, Symbol> SymbolTable;
DLinkList obj;
bool isKeyword(string s)
{
	for (int i = 0; i < KeyWSize; i++)
		if (keyword[i] == s)
			return true;
	return false;
}
string whKeyword(string s)
{
	for (int i = 0; i < KeyWSize; i++)
		if (keyword[i] == s)
			return keyword[i];
	
}
bool isLoop(string temp)
{
	for (int i = 0; i < 3; i++)
		if (Loops[i] == temp)
			return true;
	return false;
}
bool isDataType(string temp)
{
	for (int i = 0; i < 3; i++)
		if (datatype[i] == temp)
			return true;
	return false;
}
bool isOperator(string s)
{
	if (s.length() == 1 && !isalpha(s[0]) && !isdigit(s[0]))
		return true;
	else
		return false;
}
bool isFinalSate(int State)
{
	for (int i = 0; i < 3; i++)
		if (FinalStates[i] == State)
			return true;
	return false;
}
bool isArithematicOperator(string temp)
{
	for (int i = 0; i < 4; i++)
		if (temp == ArthimeticOperators[i])
			return true;
	return false;
}
bool isComparisonOperator(string temp)
{
	for (int i = 0; i < 4; i++)
		if (ComaprisonOperator[i] == temp)
			return true;
	return false;
}
void dfa(string s,int index,int Lenght,int State=1)
{
	if (index == Lenght)
	{
		if (isFinalSate(State))
		{
			if (State == 2)
			{
				//cout << "Identifier State\n"; system("pause");
				if (SymbolTable.find(s)==SymbolTable.end()) 
				{
					Symbol SymbolObj;
					obj.MvetoPrv();
					if (isDataType(obj.GetCurrent()))
					{
						//cout << "Inserting Identifier\n"; system("pause");
						SymbolObj.setValues(s, obj.GetCurrent(), true, false, false, true, false);
					}
					else
					{
						//cout << "Inserting Identifier\n"; system("pause");
						SymbolObj.setValues(s, "Identifier", true, false, false, true, false);
					}
					obj.MvetoNxt();
					SymbolTable.insert(pair<string, Symbol>(s, SymbolObj));
				}
			}
			else if (State == 3 || State == 4)
			{
				Symbol SymbolObj;
				SymbolObj.setValues(s, "Constant", true, false, false, false, true);
				SymbolTable.insert(pair<string, Symbol>(s, SymbolObj));
			}
		}
		else
		{
			Symbol SymbolObj;
			SymbolObj.setValues(s, "Unknown",false,false,false,false,false);
			SymbolTable.insert(pair<string, Symbol>(s, SymbolObj));
		}
	}
	else
	{
		switch (State)
		{
		case 1:if (s[index] == '_' || isalpha(s[index]))
		{
			State = 2; index++;
			dfa(s, index, Lenght, State);
		}
		else if(isdigit(s[index]))
		{
			State = 3; index++;
			dfa(s, index, Lenght, State);
		}
		else if (s[index] == '.') 
		{
			State = 5; index++;
			dfa(s, index, Lenght, State);
		}	  
		break;
		case 2:if (s[index] == '_' || isalpha(s[index]) || isdigit(s[index]))
		{
			State = 2; index++;
			dfa(s, index, Lenght, State);
		}
			  else if (s[index] == '.')
		{
			State = 5; index++;
			dfa(s, index, Lenght, State);
		}
		break;
		case 3:
			if (isdigit(s[index]))
			{
				State = 3; index++;
				dfa(s, index, Lenght, State);
			}
			else if (s[index] == '.')
			{
				State = 4; index++;
				dfa(s, index, Lenght, State);
			}
			else if (s[index] == '_' || isalpha(s[index]))
			{
				State = 5; index++;
				dfa(s, index, Lenght, State);
			}
			break;
		case 4:
			if (isdigit(s[index]))
			{
				State = 4; index++;
				dfa(s, index, Lenght, State);
			}
			else if (s[index] == '.' || s[index] == '_' || isalpha(s[index]))
			{
				State = 5; index++;
				dfa(s, index, Lenght, State);
			}
			break;
		case 5:
			if (s[index] == '_' || isalpha(s[index]) || isdigit(s[index]) || s[index] == '.')
			{
				State = 5; index++;
				dfa(s, index, Lenght, State);
			}
		}
	}
}
void ProcessToken(string s)
{
	if (!isKeyword(s) && !isOperator(s))
	{
		dfa(s, 0, s.length());
	}
	else if (isKeyword(s))
	{
			Symbol Symbolobj;
			if (isLoop(s))
			{
				Symbolobj.setValues(s, "Loop", true, true, false,false ,false );
			}
			else if (isDataType(s))
			{
				Symbolobj.setValues(s, "DataType", true, true, false, false, false);
			}
			else
			{
				Symbolobj.setValues(s, "Keyword", true, true, false, false, false);
			}
			SymbolTable.insert(pair<string, Symbol>(s, Symbolobj));
	}
	else if (isOperator(s))
	{
		Symbol Symbolobj;
		Symbolobj.setValues(s, "Operator", true, false, true, false, false);
		SymbolTable.insert(pair<string, Symbol>(s, Symbolobj));
	}
	
}