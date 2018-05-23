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
			// 检查是否存在相同的状态
			for (const auto &s : lrdfa.statesVec) {
				if (s.LRItemsSet == p.second) {
					edgeToInt = s.numberInt;
					break;
				}
			}
			if (edgeToInt == -1)//不存在要新建状态了
			{
				LRState newState;
				lrdfa.statesVec.push_back(newState);
				edgeToInt = stateNumCounter;
				unhandledStates.push(stateNumCounter);
				lrdfa.statesVec.back().numberInt = stateNumCounter++;
				lrdfa.statesVec.back().LRItemsSet = p.second;
			}
			lrdfa.statesVec[top].edgesMap.emplace(p.first, edgeToInt);//连上边
		}
	}
}

void epsilon_clousure(unordered_set<LRItem> &lrStateSet) {
	// TODO 优化
	stack<LRItem> stack;
	for (const auto &lrItem : lrStateSet) {//产生式先都入栈
		stack.push(lrItem);
	}
	pair<int, vector<int> > producer;
	int position, item;
	unordered_set<int> predictiveItemSet;
	while (!stack.empty()) {//栈不为空时
		producer = producerVec[stack.top().gramarInt];
		position = stack.top().positionInt;
		if (producer.second.size() == position) {//点在末尾，处理下一个产生式
			stack.pop();
			continue;
		}else {
			item = producer.second[position];
			if (item <= boundTInt) {//是终结符，没有闭包，处理下一个
				stack.pop();
				continue;
			}
			//先找到所有对应的产生式
			auto index = indexMap.find(item)->second;
			predictiveItemSet = stack.top().predictiveItemSet;
			stack.pop();
			for (int i = 0; i < index.second; ++i) {//对于所有产生式，新建LRItem
				LRItem newItem;
				stack.push(newItem);
				auto &newItemRef = stack.top();
				newItemRef.gramarInt = index.first + i;
				//求预测符
				vector<int> nextSymbolsVec;
				for (int i = position; i < producer.second.size(); ++i) {
					nextSymbolsVec.push_back(producer.second[i]);
				}
				
				first_string(newItemRef.predictiveItemSet, nextSymbolsVec);
				if (newItemRef.predictiveItemSet.find(-1)!= newItemRef.predictiveItemSet.end()) {//有epsilon
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