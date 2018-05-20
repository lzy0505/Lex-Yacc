#pragma once
#ifndef STRUCT_H
#define STRUCT_H

#include "stdafx.h"
using std::vector;
using std::multimap;
using std::string;
using std::pair;
using std::set;
using std::unordered_set;
using std::unordered_map;
using std::unordered_multimap;

typedef vector<pair<string, vector<string> > > ProducerVecStr;//�ַ��汾��������ʾ<����>
//typedef multimap<int, pair<int, vector<int> > > ProducerMuiltiMap;//���ڲ���<����ս��<����ʽ��ţ���>>
typedef vector<pair<int, vector<int> > > ProducerVec;//<����>
//typedef multimap<int, vector<int> > ProducerMuiltiMap;//���ڲ���<����ս��<����ʽ��ţ���>>

typedef struct LRItem {
	int positionInt = 0;
	int gramarInt = -1;
	set<int> predictiveItemSet;
	inline bool operator==(const LRItem& rLRItem) const {
		if (positionInt != rLRItem.positionInt) return false;
		if (gramarInt != rLRItem.gramarInt) return false;
		if (predictiveItemSet != rLRItem.predictiveItemSet) return false;
		else return true;
	}
}LRItem;

namespace std {

	template<>
	struct hash<LRItem> {
		inline size_t operator()(const LRItem& s) const {
			return  hash<int>()(s.gramarInt);
		}
	};
}


typedef struct {
	int numberInt = -1;//״̬��
	unordered_map<int, int> edgesMap;//<�ս����״̬��>
	unordered_set<LRItem> LRItemsSet;
}LRState;


typedef struct {
	int startState = 0;
	unordered_multimap<int, int> reducableStatesMap;//<״̬�ţ�����ʽ���>
	vector<LRState > statesVec;//�洢���е�LRState
}LRDFA;

#endif // !STRUCT_H
