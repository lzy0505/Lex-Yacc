// Lex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "structs.h"

using namespace std;

int resolve(string filePath, map<string, string>& m, vector<Rules>& vRules, vector<string>&P1, vector<string>&P4);
void resolve_test();
//void translate(vector<Rules>& reVec, map<string, string>& reMap);
void translate(string& s);
void replaceQuestionAndAdd(string& exp);


void suffix_To_NFA(vector<Rules>& suffixRules);
void suffixRE(vector<Rules>& rules);
int main()
//{	
//	map<string, string> terms;
//	vector<Rules> rules;
//	vector<string>part1, part4;
//	resolve("lex.l", terms, rules, part1, part4);
//	translate(rules,terms);
//	for (const auto &p : terms) {
//		cout << "NAME:" <<p.first << "\n" << "EXPRESSION:" << p.second << endl;
//	}
//	cout<<"\n\n===================================\n\n";
//	for (const auto &e : rules) {
//		cout << "PATTERN:" << e.pattern<< endl;
//	}
//
	
{
	string s = "L\?'(\\\\.|[^\\\\'\\n])+'";
	translate(s);
	cout << "pre:" << s<<endl;
	Rules rule;
	vector<Rules> vecR;
	rule.pattern = s;
	vecR.push_back(rule);
	suffixRE(vecR);
	suffix_To_NFA(vecR);

	system("pause");
	return 0;
}

