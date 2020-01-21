#include"ThreeAddress.h"
int main()
{
	/*do begin a = a - b; if a < b begin a = 9; end end while i < 5; while a < b begin a = a - b; end"*/
	string s = "do begin a = a - b; if a < b begin a = 9; end end while i < 5; while a < b begin a = a - b; end";
	obj=Tokenize(s);
	obj.Show();
	while (obj.GetCurrent() != "\0")
	{
		ProcessToken(obj.GetCurrent());
		obj.MvetoNxt();
	}
	obj.ResetITR();
	//map<string, Symbol>::iterator i;
	//for (i = SymbolTable.begin(); i != SymbolTable.end(); ++i)
	//{
	//	i->second.Show();
	//	cout << endl;
	//}
	//Cfg("S", "\0", "\0", obj.GetFirst());
	//obj.ResetITR();
	//if (ERROR_LIST != " ")
	//	cout << ERROR_LIST << endl;
	ThreeAddress();
	threeadrs.showThreeAddress();
	cout << "Line count: " << LineCount << endl;
	system("pause");
	return 0;
}