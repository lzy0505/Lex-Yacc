#pragma once
#ifndef  _STRUCTS_H
#define  _STRUCTS_H

#include "stdafx.h" 
using std::vector;
using std::string;
using std::map;
using std::multimap;


//���ڹ���Ľṹ��
typedef struct {
	string pattern; //RE
	vector<string> actions;//��Ӧ��������䣩
} Rules;

//����NFA״̬�Ľṹ��
struct state {
	int number;//״̬���
	multimap<char, state*> exEdges;//������,��Ϊ���ϵ�ֵ��ֵΪ��һ��״̬
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