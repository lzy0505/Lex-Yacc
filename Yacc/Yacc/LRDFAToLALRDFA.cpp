#include "stdafx.h"
#include "structs.h"
using std::map;
using std::stack;
using std::queue;
using std::cout;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::map;
using std::pair;
using std::make_pair;

namespace std {

	template<>
	struct hash<pair<int, int> > {
		inline size_t operator()(const pair<int, int>& s) const {
			return  hash<int>()(s.first+s.second);
		}
	};
	struct {
		bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const {
			if (p1.first != p2.first) return false;
			if (p1.second != p2.second) return false;
			else return true;
		}
	};

}

//合并同心项
void lrdfa_to_lalrdfa(LRDFA & lrdfa) {
	vector<pair<unordered_set<pair<int, int>>, unordered_set<int>>> core_vec;//同心集合，pair前项是core，后项是心为前项的同心集（存着状态号）
	//对每个状态求core，然后比较core，将core相同的装到一起
	for (auto& state:lrdfa.statesVec) {
		//把状态的core弄出来
		unordered_set<pair<int, int>> state_core;
		for (auto lritem : state.LRItemsSet) {
			state_core.insert(make_pair(lritem.gramarInt, lritem.positionInt));
		}
		bool isHad = false;//是否已存在于core_vec中
		for (auto& core : core_vec) {
			//如果已经存在了，直接加入同心集，把状态标号传入
			if (core.first == state_core) {
				isHad = true;
				core.second.insert(state.numberInt);
			}
		}
		//如果不存在该类型的core，则加入队列
		if (!isHad) {
			unordered_set<int> new_type;
			new_type.insert(state.numberInt);
			core_vec.push_back(make_pair(state_core, new_type));
		}
	}
	int a;

}