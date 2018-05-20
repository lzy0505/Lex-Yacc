// Yacc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"structs.h"

using std::map;
using std::vector;




int open_and_read_yacc_file(const string& fileName, vector<string> &tokensVec, vector<string>&left, string& start, ProducerVecStr &producerVecStr, vector<string>& funcVec);
void translate_expression(const string &startItemStr,const vector<string> &token, const ProducerVecStr & producerVecStr,int & boundTInt, int & boundNInt, int &startInt,ProducerVec &producerVec, map<int, pair<int, int> > &indexMap); 
void cfg_to_lrdfa(const int boundTInt, const string &start, const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, LRDFA & lrdfa);
void lrdfa_to_table(const int boundTInt, const int boundNInt, const LRDFA &lrdfa, int *& next_state, int *& reduce_state, int & size);
void generate_files(int *&next_state, int *&reduce_state, int & size);

/*公元2018年5月4日，中国冒险家赵千锋第一次登上Yacc大陆，这是他的一小步，却是人类的一大步*/

int main()
{
	string fileNameStr("yacc.y");
	vector<string> tokensVec;
	vector<string> leftAssociativeVec;
	string startItemStr;
	ProducerVecStr producerVecStr;
	vector<string> funcVec;
	open_and_read_yacc_file(fileNameStr, tokensVec, leftAssociativeVec, startItemStr, producerVecStr, funcVec);
	ProducerVec producerVec;//用于编号下表寻址
	int boundTInt, boundNInt,startInt;
	map<int, pair<int, int> > indexMap;//<token编号，从下标m 开始，共n个>
	translate_expression(startItemStr,tokensVec, producerVecStr, boundTInt, boundNInt, startInt, producerVec, indexMap);
	LRDFA lrdfa;
	cfg_to_lrdfa(boundTInt,startItemStr, producerVec, indexMap, lrdfa);

	system("pause");
    return 0;
}