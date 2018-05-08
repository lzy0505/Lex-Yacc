#include "stdafx.h"
#include "structs.h"
#include"globalData.hpp"
using std::stack;
using std::vector;
using std::map;
using std::string;
using std::isalnum;
using std::isalpha;
using std::isdigit;
using std::cout;
using std::queue;
using std::stack;
using std::endl;
using std::multimap;
using std::pair;



void DFAtoArray(const DFA& dfa) {
	const int set_size=ALLSET.size();
	cout << set_size<<endl;
	//建立四个表：1、ec表：索引char的ascii码，值是对应的列数
	int ec[256] = {};
	//从下标为1开始给char标值，0代表非法字符
	for (int i = 0; i < set_size; ++i) {
		ec[int(ALLSET[i])] = i + 1;
	}
	//2、base表：索引是状态序列，值是行数*宽度。
	const int DFA_size = dfa.statesVec.size();
	int* base = new int[DFA_size];
	//3、next表：索引是base+ec。值是下一个跳转状态。大小是base*ec
	int* next = new int[DFA_size*(set_size + 1)];//set从1开始计数
	for (int i = 0; i < dfa.statesVec.size(); i++) {
		base[dfa.statesVec[i].number] = i * (set_size+1);
		for (auto it = dfa.statesVec[i].exEdgesMap.begin(); it != dfa.statesVec[i].exEdgesMap.end(); it++) {
			next[base[dfa.statesVec[i].number] + ec[int(it->first)]] = it->second;
		}	
	}


	//4、accept表：索引是终态状态号，值是对应的序列号。
	int* accept = new int[DFA_size];
	for (int i = 0; i < DFA_size; ++i) {
		accept[i] = 0;
	}
	vector<Rules> endVec;
	int numOfend = 0;
	for (auto it = dfa.endStatesMap.begin(); it != dfa.endStatesMap.end(); ++it) {
		accept[it->first] = numOfend;
		endVec.push_back(it->second);
		++numOfend;
	}


}