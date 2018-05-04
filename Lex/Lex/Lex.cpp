// Lex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "structs.h"

using namespace std;

int resolve(string filePath, map<string, string>& m, vector<Rules>& vRules, vector<string>&P1, vector<string>&P4);
void resolve_test();
void suffixRE(vector<Rules>& rules);
int main()
{
	Rules rule;
	vector<Rules> vecR;
	rule.pattern = "(a|b).(a|b|c)*|c.(b|c)*";
	vecR.push_back(rule);
	suffixRE(vecR);
	system("pause");
}

