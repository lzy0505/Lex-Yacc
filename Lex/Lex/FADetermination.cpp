#include "stdafx.h"
#include "structs.h"
#include "globalData.hpp"
using std::cout;
using std::endl;
using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::queue;


bool find_actions(const unordered_set<NFAstate> &nfaStatesInDFAState, unordered_map<int, vector<string> > endStatesInNFA,vector<string>& actions) {
	for (const auto & nfaState : nfaStatesInDFAState) {
		auto it = endStatesInNFA.find(nfaState.number);
		if (it == endStatesInNFA.end()) {
			actions = (*it).second;
			return true;
		}
	}
	return false;
}



void epsilon_closure(unordered_set<NFAstate> &initStatesSet, const unordered_map<int , NFAstate> NFAStatesMap) {
	const unordered_set<NFAstate> tempSet(initStatesSet);
	for (const auto& state : tempSet) {
		auto itsPair = state.exEdgesMultiMap.equal_range('@');
		auto beginIt = itsPair.first, endIt = itsPair.second;
		while (beginIt != endIt) {
			initStatesSet.insert((*NFAStatesMap.find((*beginIt).second)).second);
		}
	}
}

bool subset_construct(const unordered_set<NFAstate>& originSet, unordered_set<NFAstate>& constructedSet,const char edge, const unordered_map<int, NFAstate> NFAStatesMap) {
	bool flag = false;//false表示集合中没有延出edge边的状态
	for (const auto& state : originSet) {
		auto itsPair = state.exEdgesMultiMap.equal_range(edge);
		auto beginIt = itsPair.first, endIt = itsPair.second;
		if (beginIt == endIt) continue;//判断这个状态有没有
		while (beginIt != endIt) {
			constructedSet.insert((*NFAStatesMap.find((*beginIt).second)).second);
		}
		flag = true;//集合里面有一个状态有就是有！
	}
	return flag;
}



void convert_to_DFA(const NFA &nfa,DFA &dfa) {
	const string edgeSet(ALLSET);//设置边的全集
	queue<DFAstate> unExamedDFAStates;//存储未处理的DFA状态
	int counter = 0;//用于给DFA状态编号
	DFAstate initDFAState;//I0
	initDFAState.number = counter++;
	initDFAState.identitySet.insert((*nfa.statesMap.find(nfa.startState)).second);
	epsilon_closure(initDFAState.identitySet, nfa.statesMap);
	dfa.statesVec.push_back(initDFAState);
	unExamedDFAStates.push(initDFAState);
	while(!unExamedDFAStates.empty()){//还有没有处理的新DFA状态
		auto state = unExamedDFAStates.front();//取出一个
		unExamedDFAStates.pop();
		for (const char& c : edgeSet) {
			unordered_set<NFAstate> tempSet;
			if (subset_construct(state.identitySet, tempSet, c, nfa.statesMap)) {
				epsilon_closure(tempSet, nfa.statesMap);//再epsilon闭包
				bool has = false;//看看是不是已经存在一样的
				for (const auto &s : dfa.statesVec) {
					if (s.identitySet == tempSet) {//存在一样的,直接写它的标号
						state.exEdgesMap.insert(pair<char, int>(c,s.number));
						has = true;
						break;
					}
				}
				if (!has) {//不存在，要新建一个state
					DFAstate newState;
					cout << counter << endl;
					newState.number = counter++;//新标号
					newState.identitySet = tempSet;
					dfa.statesVec.push_back(newState);
					unExamedDFAStates.push(newState);
					vector<string> actions;	//判断是否是终态并找每个终态对应动作
					if (find_actions(newState.identitySet, nfa.endStatesMap, actions)) { //如果包含一个终态
						dfa.endStatesMap.insert(pair<int, vector<string> >(newState.number, actions));
					}
				}
			}
		}
	}
}