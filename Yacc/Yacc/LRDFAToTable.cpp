#include"stdafx.h"
#include"structs.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;
// TODO : 李某

extern int boundNInt;
extern int boundTInt;
extern ProducerVec producerVec;//用于编号下表寻址
extern vector<unordered_set<int> > precedenceRulesVec;//移进规约表

void lrdfa_to_table(const LRDFA &lrdfa) {
	//base表通过状态号得到对应一维数组的索引位置。
	int* base = new int[lrdfa.statesVec.size()];
	memset(base,0, lrdfa.statesVec.size() * sizeof(int));
	//next通过base表的值+终结或者非终结符取值得到下一状态
	int* next = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
	memset(next, -1, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-1表示出错
	int* shift_reduce = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
	memset(shift_reduce, -2, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-2表示出错，-1表示规约，0表示啥都没有，1表示移进


	//遍历所有状态操作
	for (int i = 0; i < lrdfa.statesVec.size(); ++i) {
		base[lrdfa.statesVec[i].numberInt] = i * (boundNInt + 2);//相当于行号
		//对每个状态处理，相当于对每一行处理

		//先把移进和非终结符的情况安排了，先填入表中
		for (auto j = lrdfa.statesVec[i].edgesMap.begin(); j != lrdfa.statesVec[i].edgesMap.end();++j) {
			if (j->first <= boundTInt) {//终结符
					next[base[lrdfa.statesVec[i].numberInt] + j->first] = j->second;//赋值下一个状态
					//移进
					shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first] = 1;
			}
			else {//非终结符
				next[base[lrdfa.statesVec[i].numberInt] + j->first+1] = j->second;//赋值下一个状态
				shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first+1] = 0;
			}
		}

		//再来安排规约情况,对状态中的每一产生式进行操作
		for (auto it = lrdfa.statesVec[i].LRItemsSet.begin(); it != lrdfa.statesVec[i].LRItemsSet.end();++it) {
			//如果是点在最后的项，则会有规约
			if (it->positionInt == producerVec[it->gramarInt].second.size()) {
				//取出预测分析符，预测分析符都是终结符，因此没有shift_reduce[i]=0的情况
				//解决移进规约冲突
				if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == 1) {
					int preLine = -1,lastLine=-1;//preLine记录预测符的行数，lastLine记录每项最后一个终结符的行数。行数越大优先级越高，同一行按照左结合来解决冲突
					//找到产生式中最后一个终结符
					int last;
					for (int k = producerVec[it->gramarInt].second.size() - 1; k >= 0; k--) {
						//小于这个数就是终结符
						if (producerVec[it->gramarInt].second[k] <= boundTInt) {
							last = producerVec[it->gramarInt].second[k];
							break;
						}
					}
						
					//在规则表中定位预测符和last终结符
					for (int k = 0; k < precedenceRulesVec.size(); ++k) {
						for (auto j = precedenceRulesVec[k].begin(); j != precedenceRulesVec[k].end(); ++j) {
							//找到预测符
							if (*j == it->predictiveSymbol) {
								preLine = k;//记录优先级
							}//找到最后一个终结符
							if(last==*j){
								lastLine = k;//记录优先级
							}
						}
					}
					//如果有规则，按照规则来,没有就做移近（啥都不做）
					if (preLine!=-1&&lastLine!=-1) {
						//最后一个的终结符优先级高,改为规约，反之，做移进（做已经什么都不用做）
						if (preLine <= lastLine) {
							next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] = it->gramarInt;
							shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == -1;//规约
						}
					}
				}//解决规约规约冲突
				else if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == -1) {
					//比较产生式优先级，选择优先级高（号码比较小的）的做规约
					if (next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] > it->gramarInt) {
						next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] = it->gramarInt;
					}
				}
				else {//没有冲突，则把产生式对应的编号赋值。
					if (it->predictiveSymbol == -2) { //处理$的情况
						next[base[lrdfa.statesVec[i].numberInt] + boundTInt + 1] = it->gramarInt;
						shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == -1;//规约
						continue;
					}
					next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] = it->gramarInt;
					shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == -1;//规约
				}		
			}
		}
	}

	int i = 0;
}