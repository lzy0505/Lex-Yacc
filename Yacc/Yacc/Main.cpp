// Yacc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"structs.h"

using std::map;
using std::vector;
using std::cout;




int open_and_read_yacc_file(const string& fileName, vector<string> &tokensVec, vector<unordered_set<string>>&left, string& start, ProducerVecStr &producerVecStr);
void translate_expression(const string &startItemStr,const vector<string> &token, const ProducerVecStr & producerVecStr, const vector<unordered_set<string>>&left);
void first_operation();
void cfg_to_lrdfa();
void lrdfa_to_table();
void generate_files();
void lrdfa_to_lalrdfa();

/*公元2018年5月4日，中国冒险家赵千锋第一次登上Yacc大陆，这是他的一小步，却是人类的一大步*/

int boundTInt, boundNInt, startInt;
map<int, pair<int, int> > indexMap;
ProducerVec producerVec;//用于编号下表寻址
ProducerVecStr producerVecStr;
map<int, unordered_set<int> > firstMap;
vector<unordered_set<int> > precedenceRulesVec;

extern map<string, int> tokensMap;
vector<string> tokensVec;
LRDFA lrdfa;
void generate_files();
int main(int argc, char** argv)
{
	string fileNameStr;
	if (argc != 2) {
		cout << "ERROR: invalid arguments number!\n";
		return -1;
	}
	else {
		fileNameStr =string(argv[1]);
	

		vector<unordered_set<string>> leftAssociativeVec;
		string startItemStr;
		vector<string> funcVec;
		cout << "\n\n#############\n"<<"OPENING FILE...\n";
		if (open_and_read_yacc_file(fileNameStr, tokensVec, leftAssociativeVec, startItemStr, producerVecStr)){
			return -1;
		}
	//<token编号，从下标m 开始，共n个>
		translate_expression(startItemStr,tokensVec, producerVecStr, leftAssociativeVec);
		cout << "COMPLETED.";
	}

	cout << "\n\n#############\n" << "GETTING FIRST...\n";
	first_operation();
	cout << "COMPLETED.";

	cout << "\n\n#############\n" << "CONVERTING TO LRDFA...\n";
	cfg_to_lrdfa();
	cout << "COMPLETED.";

	cout << "\n\n#############\n" << "GENERATING LALRDFA...\n";
	lrdfa_to_lalrdfa();
	cout << "COMPLETED.";

	cout << "\n\n#############\n" << "GENERATING Y.TAB.H & Y.TAB.C...\n";
	lrdfa_to_table();
	generate_files();
	cout << "COMPLETED.";
	cout << "\n\n#############\n" << "COMPLETED ALL TASKS!";
    return 0;
}