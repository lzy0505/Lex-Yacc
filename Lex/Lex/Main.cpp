// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "structs.h"

using namespace std;

int read_and_parse_lex(string filePath, map<string, string>& m, vector<Rules>& vRules, vector<string>&P1, vector<string>&P4);
void re_standardize(vector<Rules>& reVec, map<string, string>& reMap);
void re_to_suffix(vector<Rules>& rules);
void suffix_to_nfa(vector<Rules>& suffixRules, NFA& finalNfa);
void nfa_to_dfa(const NFA &nfa, DFA &dfa);
void dfa_to_array(const DFA& dfa, vector<pair<int*, int> >& arrays, vector<Rules>& endVec);
int generate_c_code(vector<pair<int*, int>>& arrays, vector<Rules>& endVec,vector<string>& part1, vector<string>& part4);

static void print(string s, bool printterms, map<string, string> terms, vector<Rules> rules);


vector<Rules> rules;

int main()
{	
	map<string, string> terms;
	
	vector<string>part1, part4;

	read_and_parse_lex("fakelex.l", terms, rules, part1, part4);

	re_standardize(rules,terms);
	print("STANDARDIZATION", true,terms, rules);

	re_to_suffix(rules);
	print("SUFFIX", false, terms, rules);

	NFA nfa;
	cout << "\n\n#####################\n" << "GENERATE NFA" << endl;
	suffix_to_nfa(rules,nfa);

	DFA dfa;
	cout << "\n\n#####################\n" << "CONVERT TO DFA" << endl;
	nfa_to_dfa(nfa, dfa);

	vector<pair<int*, int>> arrays;
	vector<Rules>endVec;
	cout << "\n\n#####################\n" << "GENERATE LEX.C" << endl;
	dfa_to_array(dfa,arrays,endVec);

	generate_c_code(arrays, endVec,part1,part4);
	cout << "\n\n#####################\n" << "COMPLETE" <<endl;
	system("pause");
	return 0;
}



void print(string s, bool printterms, map<string, string> terms, vector<Rules> rules) {
	cout << "\n\n#####################\n" << s << endl;
	if (printterms) {
		for (const auto &p : terms) {
			cout << "NAME:" << p.first << "\n" << "EXPRESSION:" << p.second << endl;
		}
		cout << "\n===================================\n";
	}
	for (const auto &e : rules)
		cout << "PATTERN:" << e.pattern << endl;
}