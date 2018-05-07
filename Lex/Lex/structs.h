#pragma once
#ifndef  _STRUCTS_H
#define  _STRUCTS_H

#include "stdafx.h" 
using std::vector;
using std::string;
using std::map;
using std::unordered_map;
using std::unordered_set;
using std::unordered_multimap;
using std::set;






//用于规则的结构体
typedef struct {
	string pattern; //RE
	vector<string> actions;//对应动作（语句）
} Rules;

//用于NFA状态的结构体
typedef struct NFAstate{
	int number = 0;//状态标号
	unordered_multimap<char, int> exEdgesMultiMap;//发出边,键为边上的值，值为下一个状态标号
	inline bool operator==(const NFAstate& rNFAState) const {
		if (number == rNFAState.number) return true;
		else return false;
	}
}NFAstate;//NFA内部状态



namespace std {
	template<>
	struct hash<NFAstate> {
		inline size_t operator()(const NFAstate& s) const {
			return  hash<int>()(s.number);
		}
	};
}



typedef struct {
	int startState = 0;//开始状态标号
	map<int, Rules> endStatesMap;//存储终态和对应的动作
	unordered_map<int,NFAstate> statesMap;//存储标号对应状态
}NFA;//NFA

typedef struct  {
	int number = 0;//状态标号
	unordered_set <NFAstate> identitySet;//区分不同状态用的集合
	unordered_map <char, int> exEdgesMap;//发出边,键为边上的值，值为下一个状态标号
}DFAstate;

typedef struct {
	unordered_map<int, Rules > endStatesMap;//存储终态和对应的动作
	int startState = 0;//开始状态标号
	vector<DFAstate> statesVec;//存储标号对应状态
}DFA;


#endif 