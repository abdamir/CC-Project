#pragma once
#include"DFA.h"
#include<Windows.h>
/*
S->if condition begin S end S| while condition begin S end S| NULL
condition->identifier op identifier
condition->identifier op constant
op-> <|<=
op-> >|>=
op-> ==|!=

*/

string ERROR_LIST = " ";
string removeSpaces(string s)
{
	string temp = "\0";
	int i = s.length();
	int k = 0;
	while (k < i)
	{
		if (s[k] != ' ') { temp == "\0" ? temp = s[k] : temp += s[k]; }
		k++;
	}
	return temp;
}
bool Cfg(string cfg, string temp,string inaction,Node *node)
{
	cout << "CFG Progress: " << cfg << endl; 
	if(node!=NULL)
	cout << "Current Token: " << node->data << endl;
	system("pause");
	if ( node==NULL)
	{
		cout << "Null Found\n";
		int s = cfg.find("S");
		while (s != -1)
		{
			cfg.replace(s, strlen("S"), "");
			s = cfg.find("S");
		}
		cout << cfg << endl;
		cout << "Temp: " << temp << endl;
		cfg=removeSpaces(cfg);
		temp = removeSpaces(temp);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		cout << "CFG After Spaces Removed: " << cfg << endl;
		SetConsoleTextAttribute(hConsole, 7);
		if (temp == cfg)
		{
			cout << "Language Accepted\n";
			return true;
		}
		else
		{
			cout << "Language Rejected\n";
			return false;
		}

	}
	else
	{
		if (inaction != "\0")
		{
			if (inaction == "if")
			{
				if (cfg.find("condition") != -1)
				{
					int s = cfg.find("condition");
					string temp1 = cfg, temp2 = cfg;
					temp1.replace(s, strlen("condition"), "identifier op identifier");
					return Cfg(temp1, temp, "if", node->next);

				}
				else
				{
					bool DualOperator=false;
					Node* ntemp = node->next;
					Node* ntemp2 = node->next->next;
					string Identifier=SymbolTable.find(node->data)->second.getDatatype();
					string Operator= SymbolTable.find(ntemp->data)->second.getDatatype();
					string Identifier2= SymbolTable.find(ntemp2->data)->second.getDatatype();
					if (Identifier2 == "Operator")
						DualOperator = true;
					//Changing terminals
					int s = cfg.find("identifier");
					if (Identifier == "Constant"||Identifier=="Operator"||Identifier=="KeyWord")
					{
						ERROR_LIST = "InComplete IF statement after: " + temp +"\n";
					}
					else if (Operator != "Operator")
					{
						ERROR_LIST = "InComplete IF statement after: " + temp + "\n";
						
					}
					else {
						cfg.replace(s, strlen("identifier"), node->data);
						s= cfg.find("identifier");
						if (DualOperator)
							ntemp2 = ntemp2->next;
						cfg.replace(s, strlen("identifier"), ntemp2->data);
						s = cfg.find("op");
						if (DualOperator)
						{
							cfg.replace(s, strlen("op"), ntemp->data + ntemp2->prev->data);
							return Cfg(cfg, temp + node->data + " " + ntemp->data+ ntemp2->prev->data + " " + ntemp2->data + " ", "\0", ntemp2->next);
						}
						else
						{
							cfg.replace(s, strlen("op"), ntemp->data);
							return Cfg(cfg, temp + node->data + " " + ntemp->data + " " + ntemp2->data + " ", "\0", ntemp2->next);
						}
						
					}
				}
			}
			else if (inaction == "while")
			{
				if (cfg.find("condition") != -1)
				{
					int s = cfg.find("condition");
					string temp1 = cfg, temp2 = cfg;
					temp1.replace(s, strlen("condition"), "identifier op identifier");
					return Cfg(temp1, temp, "while", node->next);

				}
				else
				{
					bool DualOperator = false;
					Node* ntemp = node->next;
					Node* ntemp2 = node->next->next;
					string Identifier = SymbolTable.find(node->data)->second.getDatatype();
					string Operator = SymbolTable.find(ntemp->data)->second.getDatatype();
					string Identifier2 = SymbolTable.find(ntemp2->data)->second.getDatatype();
					if (Identifier2 == "Operator")
						DualOperator = true;
					//Changing terminals
					int s = cfg.find("identifier");
					if (Identifier == "Constant" || Identifier == "Operator" || Identifier == "KeyWord")
					{
						ERROR_LIST = "InComplete While condition after: " + temp + "\n";
					}
					else if (Operator != "Operator")
					{
						ERROR_LIST = "InComplete While condition after: " + temp + "\n";

					}
					else {
						cfg.replace(s, strlen("identifier"), node->data);
						s = cfg.find("identifier");
						if (DualOperator)
							ntemp2 = ntemp2->next;
						cfg.replace(s, strlen("identifier"), ntemp2->data);
						s = cfg.find("op");
						if (DualOperator)
						{
							cfg.replace(s, strlen("op"), ntemp->data + ntemp2->prev->data);
							return	Cfg(cfg, temp + node->data + " " + ntemp->data + ntemp2->prev->data + " " + ntemp2->data + " ", "\0", ntemp2->next);
						}
						else
						{
							cfg.replace(s, strlen("op"), ntemp->data);
							return Cfg(cfg, temp + node->data + " " + ntemp->data + " " + ntemp2->data + " ", "\0", ntemp2->next);
						}
					}
				}
			}
		}
		else
		{
			if (node->data == "if")
			{
				cout << "IF TRIGGERED\n";
				system("pause");
				string tempCFG = cfg;
				int s = tempCFG.find("S");
				tempCFG.replace(s, strlen("S"), "if condition begin S end S");
				cfg.replace(s, strlen("S"), "");
				while (!Cfg(tempCFG, temp == "\0" ? node->data + " " : temp + " " + node->data + " ", "if", node))
				{
					tempCFG = cfg;
					s = tempCFG.find("S");
					tempCFG.replace(s, strlen("S"), "if condition begin S end S");
					cfg.replace(s, strlen("S"), "");
				}
			}
			else if (node->data == "begin")
			{
				return Cfg(cfg, temp == "\0" ? node->data + " " : temp + " " + node->data + " ", inaction, node->next);
			}
			else if(node->data=="S")
				return Cfg(cfg, temp == "\0" ? node->data + " " : temp + " " + node->data + " ", inaction, node->next);
			else if(node->data=="end")
				return Cfg(cfg, temp == "\0" ? node->data + " " : temp + " " + node->data + " ", inaction, node->next);
			else if (node->data == "while")
			{
				string tempCFG = cfg;
				int s = tempCFG.find("S");
				tempCFG.replace(s, strlen("S"), "while condition begin S end S");
				cfg.replace(s, strlen("S"), "");
				while (!Cfg(tempCFG, temp == "\0" ? node->data + " " : temp + " " + node->data + " ", "while", node))
				{
					tempCFG = cfg;
					s = tempCFG.find("S");
					tempCFG.replace(s, strlen("S"), "while condition begin S end S");
					cfg.replace(s, strlen("S"), "");
				}
			}
			else
			{

			}
		}
	}
}

