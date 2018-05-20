#include "stdafx.h"
#include "structs.h"
using std::map;
using std::stack;

//TODO ����
static void epsilon_clousure(const int boundTInt, const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, unordered_set<LRItem> &lrStateSet);
static void subset_construct(const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, const unordered_set<LRItem> &lrStateSet, map<int, unordered_set<LRItem> >& newStateMap);
static void first_operation(set<int> &predictiveItemSet, int nextItem);

void cfg_to_lrdfa(const int boundTInt, const string &start, const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, LRDFA & lrdfa) {
	
}

void epsilon_clousure(const int boundTInt, const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, unordered_set<LRItem> &lrStateSet) {
	stack<LRItem> stack;
	for (const auto &lrItem : lrStateSet) {//����ʽ�ȶ���ջ
		stack.push(lrItem);
	}
	pair<int, vector<int> > producer;
	int position, item;
	set<int> predictiveItemSet;
	while (!stack.empty()) {//ջ��Ϊ��ʱ
		producer = producerVec[stack.top().gramarInt];
		position = stack.top().positionInt;
		if (producer.second.size() == position) {//����ĩβ��������һ������ʽ
			stack.pop();
			continue;
		}
		else {
			item = producer.second[position];
			if (item <= boundTInt) {//���ս����û�бհ���������һ��
				stack.pop();
				continue;
			}
			//���ҵ����ж�Ӧ�Ĳ���ʽ
			auto index = indexMap.find(item)->second;
			int nextItem = (position == producer.second.size() - 1) ? -1: producer.second[position+1];//-1 for epsilon
			for (int i = 0; i < index.second; ++i) {//�������в���ʽ���½�LRItem
				LRItem newItem;
				newItem.gramarInt = index.first + i;
				// TODO
				//if (first_operation(newItem.predictiveItemSet, nextItem)) {//��epsilon
				//	newItem.predictiveItemSet.insert(stack.top().predictiveItemSet.cbegin(), stack.top().predictiveItemSet.cend());//��ԭ���ļӽ�ȥ
				//} 
			}
			stack.pop();
		}
	}
}


void first_operation(set<int> &predictiveItemSet, int nextItem) {

}




void subset_construct(const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, const unordered_set<LRItem> &lrStateSet, map<int, unordered_set<LRItem> >& newStateMap) {
	
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