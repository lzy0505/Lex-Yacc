// Lex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "structs.h"

using namespace std;

int resolve(string filePath, map<string, string>& m, vector<Rules>& vRules, vector<string>&P1, vector<string>&P4);
void resolve_test();
void translate(vector<Rules>& reVec, map<string, string>& reMap);
void replaceQuestionAndAdd(string& exp);


void suffix_To_NFA(vector<Rules>& suffixRules);
void suffixRE(vector<Rules>& rules);
int main()
{	
	map<string, string> terms;
	vector<Rules> rules;
	vector<string>part1, part4;
	resolve("lex.l", terms, rules, part1, part4);
	translate(rules,terms);
	for (const auto &p : terms) {
		cout << "NAME:" <<p.first << "\n" << "EXPRESSION:" << p.second << endl;
	}
	cout<<"\n\n===================================\n\n";
	for (const auto &e : rules) {
		cout << "PATTERN:" << e.pattern<< endl;
	}

	
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
	return 0;
}

