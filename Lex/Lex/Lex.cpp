// Lex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "structs.h"

using namespace std;
struct MyStruct
{
	MyStruct* my;
	int a;
};


void suffix_To_NFA(vector<Rules>& suffixRules);
void suffixRE(vector<Rules>& rules);
int main()
{
	Rules rule;
	vector<Rules> vecR;
	rule.pattern = "ab|";
	vecR.push_back(rule);
	//suffixRE(vecR);
	//MyStruct ms;
	//MyStruct ms1;
	//ms.a = 1;
	//ms.my = ms1;
	//ms1.a = 2;
	//multimap<char, MyStruct> mmm;
	//mmm.insert(pair<char, MyStruct>('a',ms));
	//auto it = mmm.equal_range('a');
	//cout << it.first->second.my.a;
	/*
	cout << ms.my.a;*/
	suffix_To_NFA(vecR);

	system("pause");
}

