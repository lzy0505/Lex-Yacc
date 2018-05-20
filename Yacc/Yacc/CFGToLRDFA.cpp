#include "stdafx.h"
#include "structs.h"
using std::map;
using std::stack;

//TODO ：刘
static void epsilon_clousure(const int boundTInt, const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, unordered_set<LRItem> &lrStateSet);
static void subset_construct(const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, const unordered_set<LRItem> &lrStateSet, map<int, unordered_set<LRItem> >& newStateMap);
static void first_operation(set<int> &predictiveItemSet, int nextItem);

void cfg_to_lrdfa(const int boundTInt, const string &start, const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, LRDFA & lrdfa) {
	
}

void epsilon_clousure(const int boundTInt, const ProducerVec &producerVec, const map<int, pair<int, int> > &indexMap, unordered_set<LRItem> &lrStateSet) {
	stack<LRItem> stack;
	for (const auto &lrItem : lrStateSet) {//产生式先都入栈
		stack.push(lrItem);
	}
	pair<int, vector<int> > producer;
	int position, item;
	set<int> predictiveItemSet;
	while (!stack.empty()) {//栈不为空时
		producer = producerVec[stack.top().gramarInt];
		position = stack.top().positionInt;
		if (producer.second.size() == position) {//点在末尾，处理下一个产生式
			stack.pop();
			continue;
		}
		else {
			item = producer.second[position];
			if (item <= boundTInt) {//是终结符，没有闭包，处理下一个
				stack.pop();
				continue;
			}
			//先找到所有对应的产生式
			auto index = indexMap.find(item)->second;
			int nextItem = (position == producer.second.size() - 1) ? -1: producer.second[position+1];//-1 for epsilon
			for (int i = 0; i < index.second; ++i) {//对于所有产生式，新建LRItem
				LRItem newItem;
				newItem.gramarInt = index.first + i;
				// TODO
				//if (first_operation(newItem.predictiveItemSet, nextItem)) {//有epsilon
				//	newItem.predictiveItemSet.insert(stack.top().predictiveItemSet.cbegin(), stack.top().predictiveItemSet.cend());//把原来的加进去
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
	for (const auto &lrItem : lrStateSet) {//对于每一个产生式
		producer = producerVec[lrItem.gramarInt];
		if (producer.second.size() == lrItem.positionInt)//点在末尾，处理下一个产生式
			continue;
		edge = producer.second[lrItem.positionInt];
		newItem = lrItem;
		newItem.positionInt++;
		auto findIt = newStateMap.find(edge);
		if (findIt == newStateMap.end()) {//没有遍历过该边，新建一个集合先
			unordered_set<LRItem> newState;
			newState.insert(newItem);//把这个新的加到集合里
			newStateMap.emplace(edge, newState);
		}else {//如果遍历过该边，把新的lritem加到已有的集合中
			findIt->second.insert(newItem);
		}
	}

}