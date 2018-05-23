#include "stdafx.h"
#include "structs.h"
using std::map;
using std::stack;
using std::queue;


static void epsilon_clousure(unordered_set<LRItem> &lrStateSet);
static void subset_construct(const unordered_set<LRItem> &lrStateSet, map<int, unordered_set<LRItem> >& newStateMap);

void first_string(unordered_set<int>& inputSet, const vector<int>& symbols);

extern map<int, unordered_set<int> > firstMap;
extern int boundTInt, boundNInt;
extern map<int, pair<int, int> > indexMap;
extern ProducerVec producerVec;

void cfg_to_lrdfa(LRDFA & lrdfa) {
	LRState I0;
	LRItem initProducer;
	int stateNumCounter = 0;
	initProducer.predictiveItemSet.insert(-2);//-2 stands for $R
	initProducer.gramarInt = producerVec.size() - 1;
	I0.LRItemsSet.insert(initProducer);
	epsilon_clousure(I0.LRItemsSet);
	I0.numberInt = stateNumCounter++;
	lrdfa.statesVec.push_back(I0);
	queue<int> unhandledStates;
	unhandledStates.push(0);
	map<int, unordered_set<LRItem> > newStateMap;
	while (!unhandledStates.empty()) {
		int top = unhandledStates.front();
		newStateMap.clear();
		subset_construct(lrdfa.statesVec[top].LRItemsSet, newStateMap);
		for (auto & p : newStateMap) {
			epsilon_clousure(p.second);
			int edgeToInt = -1;
			// ����Ƿ������ͬ��״̬
			for (const auto &s : lrdfa.statesVec) {
				if (s.LRItemsSet == p.second) {
					edgeToInt = s.numberInt;
					break;
				}
			}
			if (edgeToInt == -1)//������Ҫ�½�״̬��
			{
				LRState newState;
				lrdfa.statesVec.push_back(newState);
				edgeToInt = stateNumCounter;
				unhandledStates.push(stateNumCounter);
				lrdfa.statesVec.back().numberInt = stateNumCounter++;
				lrdfa.statesVec.back().LRItemsSet = p.second;
			}
			lrdfa.statesVec[top].edgesMap.emplace(p.first, edgeToInt);//���ϱ�
		}
	}
}

void epsilon_clousure(unordered_set<LRItem> &lrStateSet) {
	// TODO �Ż�
	stack<LRItem> stack;
	for (const auto &lrItem : lrStateSet) {//����ʽ�ȶ���ջ
		stack.push(lrItem);
	}
	pair<int, vector<int> > producer;
	int position, item;
	unordered_set<int> predictiveItemSet;
	while (!stack.empty()) {//ջ��Ϊ��ʱ
		producer = producerVec[stack.top().gramarInt];
		position = stack.top().positionInt;
		if (producer.second.size() == position) {//����ĩβ��������һ������ʽ
			stack.pop();
			continue;
		}else {
			item = producer.second[position];
			if (item <= boundTInt) {//���ս����û�бհ���������һ��
				stack.pop();
				continue;
			}
			//���ҵ����ж�Ӧ�Ĳ���ʽ
			auto index = indexMap.find(item)->second;
			predictiveItemSet = stack.top().predictiveItemSet;
			stack.pop();
			for (int i = 0; i < index.second; ++i) {//�������в���ʽ���½�LRItem
				LRItem newItem;
				stack.push(newItem);
				auto &newItemRef = stack.top();
				newItemRef.gramarInt = index.first + i;
				//��Ԥ���
				vector<int> nextSymbolsVec;
				for (int i = position; i < producer.second.size(); ++i) {
					nextSymbolsVec.push_back(producer.second[i]);
				}
				
				first_string(newItemRef.predictiveItemSet, nextSymbolsVec);
				if (newItemRef.predictiveItemSet.find(-1)!= newItemRef.predictiveItemSet.end()) {//��epsilon
					newItemRef.predictiveItemSet.erase(-1);
					newItemRef.predictiveItemSet.insert(predictiveItemSet.cbegin(), predictiveItemSet.cend());
				}
				lrStateSet.insert(newItemRef);
			}
		}
	}
}


void subset_construct(const unordered_set<LRItem> &lrStateSet, map<int, unordered_set<LRItem> >& newStateMap) {
	
	pair<int, vector<int> > producer;
	LRItem newItem;
	int edge;
	for (const auto &lrItem : lrStateSet) {//����ÿһ������ʽ
		producer = producerVec[lrItem.gramarInt];
		if (producer.second.size() == lrItem.positionInt)//����ĩβ��������һ������ʽ
			continue;
		edge = producer.second[lrItem.positionInt];
		newItem = lrItem;
		newItem.positionInt++;
		auto findIt = newStateMap.find(edge);
		if (findIt == newStateMap.end()) {//û�б������ñߣ��½�һ��������
			unordered_set<LRItem> newState;
			newState.insert(newItem);//������µļӵ�������
			newStateMap.emplace(edge, newState);
		}else {//����������ñߣ����µ�lritem�ӵ����еļ�����
			findIt->second.insert(newItem);
		}
	}

}