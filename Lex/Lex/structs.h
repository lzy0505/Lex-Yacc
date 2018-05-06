#pragma once
#ifndef  _STRUCTS_H
#define  _STRUCTS_H

#include "stdafx.h" 
using std::vector;
using std::string;
using std::map;
using std::multimap;


//用于规则的结构体
typedef struct {
	string pattern; //RE
	vector<string> actions;//对应动作（语句）
} Rules;

//用于NFA状态的结构体
struct state {
	int number;//状态编号
	multimap<char, state*> exEdges;//发出边,键为边上的值，值为下一个状态
};

typedef struct {
	state* startState = nullptr;
	map<state*, vector<string>> endStates;
	state* statesArray = nullptr;
	int numOfstates = 0;
}NFA;

typedef struct {
	state* startState = nullptr;
	state* endState=nullptr;
	vector<string> *actions = nullptr;
	state* statesArray = nullptr;
	int numOfstates = 0;
}ReNFA;

#endif 