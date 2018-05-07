#include "stdafx.h"
#include "structs.h"
#include "globalData.hpp"
using std::cout;
using std::endl;
using std::unordered_map;
using std::map;
using std::unordered_set;
using std::pair;
using std::queue;


bool find_actions(const unordered_set<NFAstate> &nfaStatesInDFAState, map<int, Rules > endStatesInNFA,Rules& actions) {
	decltype(endStatesInNFA.find(0)) endStateIt;//要选择的终态
	bool find = false;
	for (const auto & nfaState : nfaStatesInDFAState) {//遍历DFA中所有的NFA状态
		auto it = endStatesInNFA.find(nfaState.number);//查找一下这个NFA状态是不是一个终态
		if (it != endStatesInNFA.end()) {//发现是终态
			if (find) {//如果有位置更靠前的， 更新
				if(endStateIt->first > it->first)
					endStateIt = it;
			}
			else {
				endStateIt = it;
				find = true;
			}
		}
	}
	if (find) {
		actions = endStateIt->second;
		return true;
	}
	else return false;

}



void epsilon_closure(unordered_set<NFAstate> &initStatesSet, const unordered_map<int , NFAstate> NFAStatesMap) {
	unordered_set<NFAstate> tempSet1;
	unordered_set<NFAstate> tempSet2(initStatesSet);
	do {
		tempSet1 = tempSet2;
		for (const auto& state : tempSet1) {
			auto itsPair = state.exEdgesMultiMap.equal_range('@');
			auto beginIt = itsPair.first, endIt = itsPair.second;
			while (beginIt != endIt) {
				tempSet2.insert((*NFAStatesMap.find((*beginIt).second)).second);
				++beginIt;
			}
		}
	} while (tempSet1 != tempSet2);
	initStatesSet = tempSet2;
}

bool subset_construct(const unordered_set<NFAstate>& originSet, unordered_set<NFAstate>& constructedSet,const char edge, const unordered_map<int, NFAstate> NFAStatesMap) {
	bool flag = false;//false表示集合中没有延出edge边的状态
	for (const auto& state : originSet) {
		auto itsPair = state.exEdgesMultiMap.equal_range(edge);
		auto beginIt = itsPair.first, endIt = itsPair.second;
		if (beginIt == endIt) continue;//判断这个状态有没有发出edge边
		while (beginIt != endIt) {
			constructedSet.insert((*NFAStatesMap.find((*beginIt).second)).second);
			++beginIt;
		}
		flag = true;//集合里面有一个状态有就是有！
	}
	return flag;
}



void convert_to_DFA(const NFA &nfa, DFA &dfa) {
	const string edgeSet(ALLSET);//设置边的全集
	queue<int> unExamedDFAStates;//存储未处理的DFA状态编号
	int counter = 0;//用于给DFA状态编号
	DFAstate state;//I0
	state.number = counter++;
	state.identitySet.insert((*nfa.statesMap.find(nfa.startState)).second);
	epsilon_closure(state.identitySet, nfa.statesMap);
	dfa.statesVec.push_back(state);
	unExamedDFAStates.push(state.number);
	while (!unExamedDFAStates.empty()) {//还有没有处理的新DFA状态
		int nowStateNum = unExamedDFAStates.front();//取出一个要处理的状态的编号
		unExamedDFAStates.pop();
		cout << "\n\n==============================\n" << "POP a state, remain " << unExamedDFAStates.size() << " states." << endl;
		auto nowStateIt = dfa.statesVec.begin();
		while (nowStateIt != dfa.statesVec.end()) {//在dfa的state中用编号找到这个要处理的状态；
			if (nowStateIt->number == nowStateNum) break;
			++nowStateIt;
		}
		for (const char& c : edgeSet) {
			cout << "CHECK edge " << c << " ." << endl;
			unordered_set<NFAstate> tempSet;
			cout << "SUBSET construct" << endl;
			if (subset_construct(nowStateIt->identitySet, tempSet, c, nfa.statesMap)) {
				int toStateNum;//边指向的状态的编号
				cout << "EPSILON  closure" << endl;
				epsilon_closure(tempSet, nfa.statesMap);//再epsilon闭包
				bool has = false;//看看是不是已经存在一样的
				for (const auto &s : dfa.statesVec) {
					if (s.identitySet == tempSet) {//存在一样的
						toStateNum = s.number; //指向vect中已有的状态
						has = true;
						cout << "EXIST state " << s.number << endl;
						break;
					}
				}
				if (!has) {//不存在，要新建一个state
					DFAstate newState;
					newState.number = counter++;//新标号
					toStateNum = newState.number; //指向新建的这个状态
					cout << "CREATE state" << newState.number << endl;
					newState.identitySet = tempSet;
					dfa.statesVec.push_back(newState);
					unExamedDFAStates.push(toStateNum);//新状态尚需要处理
					Rules actions;	//判断是否是终态并找每个终态对应动作
					cout << "CHECK if terminated state" << endl;
					if (find_actions(newState.identitySet, nfa.endStatesMap, actions)) { //如果包含一个终态
						dfa.endStatesMap.insert(pair<int, Rules >(newState.number, actions));//决定这个dfa终态对应的动作
					}
				}
				nowStateIt = dfa.statesVec.begin();
				while (nowStateIt != dfa.statesVec.end()) {//在dfa的state中用编号找到这个要处理的状态；
					if (nowStateIt->number == nowStateNum) break;
					++nowStateIt;
				}
				nowStateIt->exEdgesMap.insert(pair<char, int>(c, toStateNum));//加一条边
			}
		}
	}
}