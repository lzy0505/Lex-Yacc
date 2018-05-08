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
	//�����ĸ���1��ec������char��ascii�룬ֵ�Ƕ�Ӧ������
	int ec[256] = {};
	//���±�Ϊ1��ʼ��char��ֵ��0����Ƿ��ַ�
	for (int i = 0; i < set_size; ++i) {
		ec[int(ALLSET[i])] = i + 1;
	}
	//2��base��������״̬���У�ֵ������*��ȡ�
	const int DFA_size = dfa.statesVec.size();
	int* base = new int[DFA_size];
	//3��next��������base+ec��ֵ����һ����ת״̬����С��base*ec
	int* next = new int[DFA_size*(set_size + 1)];//set��1��ʼ����
	for (int i = 0; i < dfa.statesVec.size(); i++) {
		base[dfa.statesVec[i].number] = i * (set_size+1);
		for (auto it = dfa.statesVec[i].exEdgesMap.begin(); it != dfa.statesVec[i].exEdgesMap.end(); it++) {
			next[base[dfa.statesVec[i].number] + ec[int(it->first)]] = it->second;
		}	
	}


	//4��accept����������̬״̬�ţ�ֵ�Ƕ�Ӧ�����кš�
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