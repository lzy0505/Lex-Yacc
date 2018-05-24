#include"stdafx.h"
#include"structs.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;
// TODO : 李某
// next_state[] 跳转的下一个状态
// reduce_state[] 是否需要规约,注意特殊处理$-r0
extern int boundNInt;
extern int boundTInt;
extern ProducerVec producerVec;//用于编号下表寻址
extern vector<string> &leftAssociativeVec;//移进规约表

void lrdfa_to_table(const LRDFA &lrdfa ,int *& next_state, int *& reduce_state) {
//	//base表通过状态号得到对应一维数组的索引位置。
//	int* base = new int[boundNInt+2];
//	memset(base,0, (boundNInt + 2) * sizeof(int));
//	//next通过base表的值+终结或者非终结符取值得到下一状态
//	int* next = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
//	memset(next, -1, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-1表示出错
//	int* shift_reduce = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
//	memset(shift_reduce, -2, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-2表示出错，-1表示规约，0表示啥都没有，1表示移进
//
//
//	//遍历所有状态操作
//	for (int i = 0; i < lrdfa.statesVec.size(); ++i) {
//		base[lrdfa.statesVec[i].numberInt] = i * (boundNInt + 1);//相当于行号
//		//对每个状态处理，相当于对每一行处理
//
//		//先把移进和非终结符的情况安排了
//		for (auto j = lrdfa.statesVec[i].edgesMap.begin(); j != lrdfa.statesVec[i].edgesMap.end();j++) {
//			if (j->first <= boundTInt) {//终结符
//					next[base[lrdfa.statesVec[i].numberInt] + j->first] = j->second;//赋值给下一个状态
//					//移进
//					shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first] = 1;
//			}
//			else if (j->first == -2) {//存$
//				next[base[lrdfa.statesVec[i].numberInt] + boundTInt+1] = j->second;//赋值给下一个状态
//				//终结符铁规约咯
//				shift_reduce[base[lrdfa.statesVec[i].numberInt] + boundTInt + 1] = -1;
//			}
//			else {//非终结符
//				next[base[lrdfa.statesVec[i].numberInt] + j->first] = j->second;//赋值给下一个状态
//				shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first] = 0;
//			}
//		}
//
//		//再来安排规约情况,对状态中的每一产生式进行操作
//		for (auto it = lrdfa.statesVec[i].LRItemsSet.begin(); it != lrdfa.statesVec[i].LRItemsSet.end();it++) {
//			//如果是最后一项
//			if (it->positionInt == producerVec[it->gramarInt].second.size()) {
//				//取出预测分析符
//				for (auto pre = it->predictiveItemSet.begin(); pre != it->predictiveItemSet.end(); pre++) {
//					//TODO:解决移进规约冲突
//					if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + *pre] == 1) {
//
//					}
//					else if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + *pre] == -1) {//TODO:解决规约规约冲突
//
//					}
//					else {
//						//只有规约，则把产生式对应的编号赋值。
//						next[base[lrdfa.statesVec[i].numberInt] + *pre] = it->gramarInt;
//						shift_reduce[base[lrdfa.statesVec[i].numberInt] + *pre] == -1;//规约
//					}
//					
//				}
//			}
//		}
//		
//
//	}
//
	
}


//void resolve_conflicts(const vector<string> &leftAssociativeVec) {
//
//}