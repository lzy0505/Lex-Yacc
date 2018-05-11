// Lex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "structs.h"

using namespace std;

int resolve(string filePath, map<string, string>& m, vector<Rules>& vRules, vector<string>&P1, vector<string>&P4);
void translate(vector<Rules>& reVec, map<string, string>& reMap);
void DFAtoArray(const DFA& dfa, vector<pair<int*, int> >& arrays, vector<Rules>& endVec);
void suffix_To_NFA(vector<Rules>& suffixRules, NFA& finalNfa);
void suffixRE(vector<Rules>& rules);
void convert_to_DFA(const NFA &nfa, DFA &dfa);

void print(string s, bool printterms,map<string, string> terms, vector<Rules> rules) {
	cout<< "\n\n#####################"<<s<<"#####################\n\n";
	if (printterms) {
		for (const auto &p : terms) {
			cout << "NAME:" << p.first << "\n" << "EXPRESSION:" << p.second << endl;
		}
		cout << "\n===================================\n";
	}
	for (const auto &e : rules)
		cout << "PATTERN:" << e.pattern << endl;
}

int main()
{	
	map<string, string> terms;
	vector<Rules> rules;
	vector<string>part1, part4;
	resolve("fakelex.l", terms, rules, part1, part4);
	/*Rules r;
	r.pattern="(a|b)*a(a|b)(a|b)";
	r.actions.push_back("TEST;");
	rules.push_back(r);*/
	translate(rules,terms);
	print("TRANSLATE", true,terms, rules);
	suffixRE(rules);
	print("SUFFIX", false, terms, rules);
	NFA nfa;
	suffix_To_NFA(rules,nfa);
	//TODO: 把nfa里面状态整成一个vector
	DFA dfa;
	convert_to_DFA(nfa, dfa);
	//DFAtoArray(const DFA& dfa, vector<pair<int*, int> >& arrays, vector<Rules>& endVec);
	
	return 0;
}

