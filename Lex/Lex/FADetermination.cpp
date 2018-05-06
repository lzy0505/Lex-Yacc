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
	bool flag = false;//false��ʾ������û���ӳ�edge�ߵ�״̬
	for (const auto& state : originSet) {
		auto itsPair = state.exEdgesMultiMap.equal_range(edge);
		auto beginIt = itsPair.first, endIt = itsPair.second;
		if (beginIt == endIt) continue;//�ж����״̬��û��
		while (beginIt != endIt) {
			constructedSet.insert((*NFAStatesMap.find((*beginIt).second)).second);
		}
		flag = true;//����������һ��״̬�о����У�
	}
	return flag;
}



void convert_to_DFA(const NFA &nfa,DFA &dfa) {
	const string edgeSet(ALLSET);//���ñߵ�ȫ��
	queue<DFAstate> unExamedDFAStates;//�洢δ�����DFA״̬
	int counter = 0;//���ڸ�DFA״̬���
	DFAstate initDFAState;//I0
	initDFAState.number = counter++;
	initDFAState.identitySet.insert((*nfa.statesMap.find(nfa.startState)).second);
	epsilon_closure(initDFAState.identitySet, nfa.statesMap);
	dfa.statesVec.push_back(initDFAState);
	unExamedDFAStates.push(initDFAState);
	while(!unExamedDFAStates.empty()){//����û�д������DFA״̬
		auto state = unExamedDFAStates.front();//ȡ��һ��
		unExamedDFAStates.pop();
		for (const char& c : edgeSet) {
			unordered_set<NFAstate> tempSet;
			if (subset_construct(state.identitySet, tempSet, c, nfa.statesMap)) {
				epsilon_closure(tempSet, nfa.statesMap);//��epsilon�հ�
				bool has = false;//�����ǲ����Ѿ�����һ����
				for (const auto &s : dfa.statesVec) {
					if (s.identitySet == tempSet) {//����һ����,ֱ��д���ı��
						state.exEdgesMap.insert(pair<char, int>(c,s.number));
						has = true;
						break;
					}
				}
				if (!has) {//�����ڣ�Ҫ�½�һ��state
					DFAstate newState;
					cout << counter << endl;
					newState.number = counter++;//�±��
					newState.identitySet = tempSet;
					dfa.statesVec.push_back(newState);
					unExamedDFAStates.push(newState);
					vector<string> actions;	//�ж��Ƿ�����̬����ÿ����̬��Ӧ����
					if (find_actions(newState.identitySet, nfa.endStatesMap, actions)) { //�������һ����̬
						dfa.endStatesMap.insert(pair<int, vector<string> >(newState.number, actions));
					}
				}
			}
		}
	}
}