#pragma once
#include<stack>
#include"CFG.h"
#include"Stack.h"
DLinkList threeadrs;
Stack Brackets;
int LineCount = 0, TempCount = 0;
bool IF = false, WHILE = false, FOR = false, DO = false;
Stack IFs,Fors;
int AssignLineCount() 
{
	return ++LineCount;
}
int AssignTempCount()
{
	return ++TempCount;
}
void Expression()
{
	obj.MvetoPrv();
	threeadrs.InsertNode("temp" + to_string(AssignTempCount())+"="+obj.GetCurrent(), AssignLineCount());
	int backupCount = TempCount;
	while (obj.GetCurrent() != "=")
	obj.MvetoNxt();
	
	int count = 0;
	while (obj.GetCurrent() != ";")
	{
		count++;
		obj.MvetoNxt();
	}
	if (count <= 2)
	{
		obj.MvetoPrv();
		threeadrs.InsertNode("temp" + to_string(TempCount)+"="+obj.GetCurrent(), AssignLineCount());
		return;
	}
	while (obj.GetCurrent() != "=")
		obj.MvetoPrv();
	//getting over =
	obj.MvetoNxt();
	//Changing Expression
	stack<string> Operators, Identifiers;
	while (obj.GetCurrent() != ";")
	{
		cout << "In Expression Loop\n";
		if (isArithematicOperator(obj.GetCurrent()))
		{
			Operators.push(obj.GetCurrent());
			cout << obj.GetCurrent() << endl;
		}
		else if (obj.GetCurrent() == ")")
		{
			string backup="\0";
			while (Identifiers.top() != "(")
			{
				if (backup != "\0"&&backup!="(")
					Identifiers.push(backup);
				string parameter1 = Identifiers.top();
				Identifiers.pop();
				string op = Operators.top();
				Operators.pop();
				string parameter2 = "\0";
				if (!Identifiers.empty()&&Identifiers.top()!="(")
				{
					parameter2 = Identifiers.top();
					Identifiers.pop();
				}
				if (parameter2 != "\0")
				{
					threeadrs.InsertNode("temp" + to_string(AssignTempCount()) + "=" + parameter2 + op + parameter1, AssignLineCount());
					Identifiers.push("temp" + to_string(TempCount));
					cout << "temp being stored: " << Identifiers.top() << endl;
				}
				else
				{
					cout << "Solo detected: \n";
					threeadrs.InsertNode("temp" + to_string(AssignTempCount()) + "=" +op+ parameter1, AssignLineCount());
					Identifiers.push("temp" + to_string(TempCount));
				}
				backup = Identifiers.top();
				cout << backup << endl;
				Identifiers.pop();
			}
			Identifiers.pop();
			Identifiers.push(backup);
			
		}
		else
		{
			Identifiers.push(obj.GetCurrent());
			cout << "Identifiers: " << endl;
			cout << obj.GetCurrent() << endl;
		}
		obj.MvetoNxt();
	}

	//string backup = "\0";
	while (!Operators.empty())
	{
		/*if (backup != "\0")
			Identifiers.push(backup);*/
		string parameter1 = Identifiers.top();
		Identifiers.pop();
		string op = Operators.top();
		Operators.pop();
		string parameter2 = "\0";
		cout << "ParaMeter 1: "<<parameter1 << endl; system("pause");
		if (!Identifiers.empty())
		{

			cout << "Parameter 2 Found in Outer Most Loop\n"; system("pause");
			parameter2 = Identifiers.top();
			Identifiers.pop();
		}
		if (parameter2 != "\0")
		{
			threeadrs.InsertNode("temp" + to_string(AssignTempCount()) + "=" + parameter2 + op + parameter1, AssignLineCount());
			Identifiers.push("temp" + to_string(TempCount));
		}
		else
		{
			threeadrs.InsertNode("temp" + to_string(AssignTempCount()) + "=" + op + parameter1, AssignLineCount());
			Identifiers.push("temp" + to_string(TempCount));
		}
	/*	backup = Identifiers.top();
		Identifiers.pop();*/
	}
	threeadrs.InsertNode("temp" + to_string(backupCount)+"=" + "temp"+to_string(TempCount), AssignLineCount());
}
void handleIF()
{
	cout << "In if\n";
	string TempExpression = "if("; string tempexp2;
	obj.MvetoNxt();
	TempExpression += obj.GetCurrent();
	while (!isComparisonOperator(obj.GetCurrent()))
		obj.MvetoNxt();
	string op = obj.GetCurrent();
	obj.MvetoNxt();
	if (isComparisonOperator(obj.GetCurrent()))
	{
		op += obj.GetCurrent();
		obj.MvetoNxt();
		tempexp2 = obj.GetCurrent();
	}
	else
	{
		tempexp2 = obj.GetCurrent();
	}
	if (op == "<")
		op = ">=";
	else if (op == ">")
		op = "<=";
	else if (op == "<=")
		op = ">";
	else if (op == ">=")
		op = "<";
	else if (op == "==")
		op = "!=";
	else if (op == "!=")
		op = "==";
	TempExpression += op+tempexp2 + ")goto";
	threeadrs.InsertNode(TempExpression, AssignLineCount());
	while (obj.GetCurrent() != "begin")
		obj.MvetoNxt();
	Brackets.push(LineCount, "if");
	IFs.push(LineCount, "if");
}
void changeWhile()
{
	cout << "In While\n";
	string TempExpression = "if("; string tempexp2;
	obj.MvetoNxt();
	TempExpression += obj.GetCurrent();
	while (!isComparisonOperator(obj.GetCurrent()))
		obj.MvetoNxt();
	string op = obj.GetCurrent();
	obj.MvetoNxt();
	if (isComparisonOperator(obj.GetCurrent()))
	{
		op += obj.GetCurrent();
		obj.MvetoNxt();
		tempexp2 = obj.GetCurrent();
	}
	else
	{
		tempexp2 = obj.GetCurrent();
	}
	if (op == "<")
		op = ">=";
	else if (op == ">")
		op = "<=";
	else if (op == "<=")
		op = ">";
	else if (op == ">=")
		op = "<";
	else if (op == "==")
		op = "!=";
	else if (op == "!=")
		op = "==";
	TempExpression += op + tempexp2 + ")goto";
	threeadrs.InsertNode(TempExpression, AssignLineCount());
	while (obj.GetCurrent() != "begin")
		obj.MvetoNxt();
	Brackets.push(LineCount, "while");
}
void changedoWhile(int l)
{
	cout << "In do While\n";
	string TempExpression = "if("; string tempexp2;
	obj.MvetoNxt();
	TempExpression += obj.GetCurrent();
	while (!isComparisonOperator(obj.GetCurrent()))
		obj.MvetoNxt();
	string op = obj.GetCurrent();
	obj.MvetoNxt();
	if (isComparisonOperator(obj.GetCurrent()))
	{
		op += obj.GetCurrent();
		obj.MvetoNxt();
		tempexp2 = obj.GetCurrent();
	}
	else
	{
		tempexp2 = obj.GetCurrent();
	}
	TempExpression += op + tempexp2 + ")goto "+to_string(l);
	threeadrs.InsertNode(TempExpression, AssignLineCount());
	while (obj.GetCurrent() != ";")
		obj.MvetoNxt();
	
}
void changeDo()
{
	threeadrs.InsertNode("\0", AssignLineCount());
	while (obj.GetCurrent() != "begin")
	obj.MvetoNxt();
	Brackets.push(LineCount, "do");
}
void changeElse()
{
	threeadrs.InsertNode("goto", AssignLineCount());
	
	while (obj.GetCurrent() != "begin")
		obj.MvetoNxt();

	Brackets.push(LineCount, "else");
	IFs.push(LineCount, to_string(LineCount + 1));
}
void changeFor()
{
	cout << "In For Mod\n";
	string TempExpression = "if("; string tempexp2;
	obj.MvetoNxt();
	TempExpression += obj.GetCurrent();
	while (!isComparisonOperator(obj.GetCurrent()))
		obj.MvetoNxt();
	string op = obj.GetCurrent();
	obj.MvetoNxt();
	if (isComparisonOperator(obj.GetCurrent()))
	{
		op += obj.GetCurrent();
		obj.MvetoNxt();
		tempexp2 = obj.GetCurrent();
	}
	else
	{
		tempexp2 = obj.GetCurrent();
	}
	
	while (obj.GetCurrent() != "for")
	{
		obj.MvetoPrv();
	}
	Brackets.push(LineCount+1, "for");
	obj.MvetoNxt();
	string FirstP = obj.GetCurrent();
	obj.MvetoNxt();
	int int1 = stoi(obj.GetCurrent());
	obj.MvetoNxt();
	obj.MvetoNxt();
	obj.MvetoNxt();
	int int2 = stoi(obj.GetCurrent());
	if (int1 < int2)
		op = "<=";
	else
		op = ">=";
	TempExpression += op + tempexp2 + ")goto";
	threeadrs.InsertNode(TempExpression, AssignLineCount());
	
	while (obj.GetCurrent() != "begin")
	{
		obj.MvetoNxt();
	}
	Fors.push(int1, FirstP);
	Fors.push(int2, FirstP);
}
void ThreeAddress()
{
	while (!obj.isEmpty())
	{
		
		cout << "Current Token Processing: " << obj.GetCurrent() << endl;
	
		if (obj.GetCurrent() == "=")
		{
			cout << "In Expression\n" << endl;
			Expression();
		}
		if (obj.GetCurrent() == "if")
		{
			cout << "IF\n";
			handleIF();
		}
		if (obj.GetCurrent() == "while")
		{
			cout << "While\n";
			changeWhile();
		}
		if (obj.GetCurrent() == "do")
		{
			cout << "In do\n";
			changeDo();			
		}
		if (obj.GetCurrent() == "else")
		{
			cout << "Else :\n";
			changeElse();
		}
		if (obj.GetCurrent() == "for")
		{
			changeFor();
		}
		if (obj.GetCurrent() == "end")
		{
			int L = Brackets.Topline();
			string Temps = Brackets.TopData();
			if (Temps == "if")
			{
				threeadrs.InsertAtLine(L, to_string(++LineCount));
				threeadrs.InsertNode("\0", LineCount);
			}
			else if (Temps == "while")
			{
				threeadrs.InsertNode("goto "+to_string(L), AssignLineCount());
				threeadrs.InsertAtLine(L, to_string(++LineCount));
				threeadrs.InsertNode("\0", LineCount);
			}
			else if (Temps == "do")
			{
				obj.MvetoNxt();
				changedoWhile(L);
			}
		
			else if (Temps == "else")
			{
				cout << "In else end\n";
				threeadrs.InsertNode("\0", AssignLineCount());
				threeadrs.InsertAtLine(L, to_string(LineCount));
				string L2 = IFs.TopData();
				IFs.pop();
				int L1 = IFs.Topline();
				IFs.pop();
				threeadrs.InsertAtLinev2(L1,L2);
			}
			else if (Temps == "for")
			{
				int no1 = Fors.Topline();
				string tempstring = Fors.TopData();
				Fors.pop();
				int no2 = Fors.Topline();
				Fors.pop();
				if (no1 < no2)
				{
					threeadrs.InsertNode("temp" + to_string(AssignTempCount())+"="+tempstring, AssignLineCount());
					threeadrs.InsertNode("temp" + to_string(TempCount) + "=" + "temp" + to_string(TempCount)+"-1", AssignLineCount());
					threeadrs.InsertNode(tempstring+"="+ "temp " + to_string(TempCount), AssignLineCount());
					threeadrs.InsertNode("goto " + to_string(L), AssignLineCount());
					threeadrs.InsertAtLine(L, to_string(++LineCount));
					threeadrs.InsertNode("\0", LineCount);
				}
				else
				{
					threeadrs.InsertNode("temp" + to_string(AssignTempCount()) + "=" + tempstring, AssignLineCount());
					threeadrs.InsertNode("temp" + to_string(TempCount) + "=" + "temp" + to_string(TempCount) + "+1", AssignLineCount());
					threeadrs.InsertNode(tempstring + "=" + "temp " + to_string(TempCount), AssignLineCount());
					threeadrs.InsertNode("goto " + to_string(L), AssignLineCount());
					threeadrs.InsertAtLine(L, to_string(++LineCount));
					threeadrs.InsertNode("\0", LineCount);
				}

			}
			Brackets.pop();
		}

		obj.MvetoNxt();
	}

}