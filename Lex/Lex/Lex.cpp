// Lex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "structs.h"

using namespace std;

int resolve(string filePath, map<string, string>& m, vector<Rules>& vRules, vector<string>&P1, vector<string>&P4);
void resolve_test();
void translate(vector<Rules>& reVec, map<string, string>& reMap);
void constructSet(set<char> &s, const string &content, bool n);

int main()
{
	//resolve_test(); //run analyzer
	
	vector<Rules> test;
	Rules re;
	re.pattern = "{D}+{E}{FS}\?";
	test.push_back(re);
	map<string, string> m = { {"D","[0-9]"},{"E","([Ee][+-]?{D}+)"},{"FS","(f|F|l|L)"} };
	
	//set<char> s;
	//string ss = "\\\\'\\n";
	//constructSet(s, ss, true);
	//for (auto & e : s) {
	//	cout << e;
	//}

	translate(test, m);
	system("pause");
	return 0;
}

