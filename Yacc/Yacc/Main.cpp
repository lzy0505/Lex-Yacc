// Yacc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"structs.h"

using std::map;
using std::vector;




int open_and_read_yacc_file(const string& fileName, vector<string> &tokensVec, vector<unordered_set<string>>&left, string& start, ProducerVecStr &producerVecStr, vector<string>& funcVec);
void translate_expression(const string &startItemStr,const vector<string> &token, const ProducerVecStr & producerVecStr, const vector<unordered_set<string>>&left);
void first_operation();
void cfg_to_lrdfa(LRDFA & lrdfa);
void lrdfa_to_table(const LRDFA &lrdfa);
void generate_files();
void lrdfa_to_lalrdfa(LRDFA & lrdfa);

/*公元2018年5月4日，中国冒险家赵千锋第一次登上Yacc大陆，这是他的一小步，却是人类的一大步*/

int boundTInt, boundNInt, startInt;
map<int, pair<int, int> > indexMap;
ProducerVec producerVec;//用于编号下表寻址
ProducerVecStr producerVecStr;
map<int, unordered_set<int> > firstMap;
vector<unordered_set<int> > precedenceRulesVec;

extern map<string, int> tokensMap;
vector<string> tokensVec;
void generate_files();
int main()
{
	string fileNameStr("yacc.y");
	
	vector<unordered_set<string>> leftAssociativeVec;
	string startItemStr;
	vector<string> funcVec;
	open_and_read_yacc_file(fileNameStr, tokensVec, leftAssociativeVec, startItemStr, producerVecStr, funcVec);
	//<token编号，从下标m 开始，共n个>
	translate_expression(startItemStr,tokensVec, producerVecStr, leftAssociativeVec);
	first_operation();
	LRDFA lrdfa;
	cfg_to_lrdfa(lrdfa);
	lrdfa_to_table(lrdfa);
	lrdfa_to_lalrdfa(lrdfa);
	generate_files();
	//system("pause");
    return 0;
}