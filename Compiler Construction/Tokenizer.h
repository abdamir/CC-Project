#include"DLinkList.h"
using namespace std;
DLinkList Tokenize(string s)
{
	DLinkList obj;
	int Lenght = s.length();
	int i = 0;
	while (i < Lenght)
	{
		string temp="\0";
		while ((i < Lenght) && (isalpha(s[i]) || isdigit(s[i]) || s[i] == '_' || s[i] == '.'))
		{
			temp == "\0" ? temp = s[i] : temp += s[i];
			i++;
		}
		temp == "\0" ? s[i] != ' ' && s[i] != '\t' && s[i] != '\n' ? temp = s[i++] : temp = "\0" : temp = temp;
		if (temp != "\0")
			obj.InsertNode(temp);
		else
			i++;

	}
	return obj;
}
