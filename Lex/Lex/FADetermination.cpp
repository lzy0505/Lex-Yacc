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
	decltype(endStatesInNFA.find(0)) endStateIt;//Ҫѡ�����̬
	bool find = false;
	for (const auto & nfaState : nfaStatesInDFAState) {//����DFA�����е�NFA״̬
		auto it = endStatesInNFA.find(nfaState.number);//����һ�����NFA״̬�ǲ���һ����̬
		if (it != endStatesInNFA.end()) {//��������̬
			if (find) {//�����λ�ø���ǰ�ģ� ����
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
	bool flag = false;//false��ʾ������û���ӳ�edge�ߵ�״̬
	for (const auto& state : originSet) {
		auto itsPair = state.exEdgesMultiMap.equal_range(edge);
		auto beginIt = itsPair.first, endIt = itsPair.second;
		if (beginIt == endIt) continue;//�ж����״̬��û�з���edge��
		while (beginIt != endIt) {
			constructedSet.insert((*NFAStatesMap.find((*beginIt).second)).second);
			++beginIt;
		}
		flag = true;//����������һ��״̬�о����У�
	}
	return flag;
}



void convert_to_DFA(const NFA &nfa, DFA &dfa) {
	const string edgeSet(ALLSET);//���ñߵ�ȫ��
	queue<int> unExamedDFAStates;//�洢δ�����DFA״̬���
	int counter = 0;//���ڸ�DFA״̬���
	DFAstate state;//I0
	state.number = counter++;
	state.identitySet.insert((*nfa.statesMap.find(nfa.startState)).second);
	epsilon_closure(state.identitySet, nfa.statesMap);
	dfa.statesVec.push_back(state);
	unExamedDFAStates.push(state.number);
	while (!unExamedDFAStates.empty()) {//����û�д������DFA״̬
		int nowStateNum = unExamedDFAStates.front();//ȡ��һ��Ҫ�����״̬�ı��
		unExamedDFAStates.pop();
		cout << "\n\n==============================\n" << "POP a state, remain " << unExamedDFAStates.size() << " states." << endl;
		auto nowStateIt = dfa.statesVec.begin();
		while (nowStateIt != dfa.statesVec.end()) {//��dfa��state���ñ���ҵ����Ҫ�����״̬��
			if (nowStateIt->number == nowStateNum) break;
			++nowStateIt;
		}
		for (const char& c : edgeSet) {
			cout << "CHECK edge " << c << " ." << endl;
			unordered_set<NFAstate> tempSet;
			cout << "SUBSET construct" << endl;
			if (subset_construct(nowStateIt->identitySet, tempSet, c, nfa.statesMap)) {
				int toStateNum;//��ָ���״̬�ı��
				cout << "EPSILON  closure" << endl;
				epsilon_closure(tempSet, nfa.statesMap);//��epsilon�հ�
				bool has = false;//�����ǲ����Ѿ�����һ����
				for (const auto &s : dfa.statesVec) {
					if (s.identitySet == tempSet) {//����һ����
						toStateNum = s.number; //ָ��vect�����е�״̬
						has = true;
						cout << "EXIST state " << s.number << endl;
						break;
					}
				}
				if (!has) {//�����ڣ�Ҫ�½�һ��state
					DFAstate newState;
					newState.number = counter++;//�±��
					toStateNum = newState.number; //ָ���½������״̬
					cout << "CREATE state" << newState.number << endl;
					newState.identitySet = tempSet;
					dfa.statesVec.push_back(newState);
					unExamedDFAStates.push(toStateNum);//��״̬����Ҫ����
					Rules actions;	//�ж��Ƿ�����̬����ÿ����̬��Ӧ����
					cout << "CHECK if terminated state" << endl;
					if (find_actions(newState.identitySet, nfa.endStatesMap, actions)) { //�������һ����̬
						dfa.endStatesMap.insert(pair<int, Rules >(newState.number, actions));//�������dfa��̬��Ӧ�Ķ���
					}
				}
				nowStateIt = dfa.statesVec.begin();
				while (nowStateIt != dfa.statesVec.end()) {//��dfa��state���ñ���ҵ����Ҫ�����״̬��
					if (nowStateIt->number == nowStateNum) break;
					++nowStateIt;
				}
				nowStateIt->exEdgesMap.insert(pair<char, int>(c, toStateNum));//��һ����
			}
		}
	}
}