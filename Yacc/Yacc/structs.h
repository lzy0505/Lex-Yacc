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

typedef vector<pair<string, vector<string> > > ProducerVecStr;//字符版本，用做显示<左，右>
//typedef multimap<int, pair<int, vector<int> > > ProducerMuiltiMap;//便于查找<左非终结符<产生式编号，右>>
typedef vector<pair<int, vector<int> > > ProducerVec;//<左，右>
//typedef multimap<int, vector<int> > ProducerMuiltiMap;//便于查找<左非终结符<产生式编号，右>>

typedef struct LRItem {
	int positionInt = 0;
	int gramarInt = -1;
	unordered_set<int> predictiveItemSet;
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
	int numberInt = -1;//状态号
	unordered_map<int, int> edgesMap;//<终结符，状态号>
	unordered_set<LRItem> LRItemsSet;
}LRState;


typedef struct {
	int startState = 0;
	unordered_multimap<int, int> reducableStatesMap;//<状态号，产生式编号>
	vector<LRState > statesVec;//存储所有的LRState
}LRDFA;

#endif // !STRUCT_H
