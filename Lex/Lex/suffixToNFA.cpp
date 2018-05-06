#include "stdafx.h"
#include "structs.h"
using std::stack;
using std::vector;
using std::map;
using std::string;
using std::isalnum;
using std::isalpha;
using std::isdigit;
using std::cout;
using std::queue;
using std::stack;
using std::endl;
using std::multimap;
using std::pair;

//函数声明
int number = 0;

//将后缀表达式转化为NFA
//void suffix_To_NFA(vector<Rules>& suffixRules) {
//	vector<ReNFA> reNfaVec;
//	NFA finalNfa;
//	
//	for (auto &rule : suffixRules) {
//		string pattern = rule.pattern; //已经后缀化后的pattern
//		vector<string>* actions = &rule.actions;//获取操作
//		ReNFA *nfaArray = new ReNFA[pattern.size()];//保存所有的ReNFA
//		int lengthOfNfaArray = 0;
//		state *stateArray = new state[4*pattern.size()];//保存所有的状态
//		int lengthOfStateArray = 0;
//		stack<ReNFA *> nfaStack;//用于构建NFA的工具栈
//		
//
//		for (auto it = pattern.cbegin() ; it != pattern.cend(); ++it)
//		{
//			ReNFA*upNFA=nullptr,*downNFA=nullptr;
//			state * stateptr = nullptr;
//			state start, end;
//			char now = *it;
//			cout << *it;
//			switch (now) {
//			case'|':
//				upNFA = nfaStack.top();
//				nfaStack.pop();
//				downNFA = nfaStack.top();
//				nfaStack.pop();
//				start.number = number;
//				++number;
//				end.number = number;
//				stateArray[lengthOfStateArray]=end;
//				stateptr = &stateArray[lengthOfStateArray];
//				++lengthOfStateArray;
//				++number;
//				downNFA->endState->exEdges.insert(pair<char, state*>('@',stateptr));
//				upNFA->endState->exEdges.insert(pair<char, state*>('@', stateptr));
//				downNFA->endState = stateptr;
//				stateArray[lengthOfStateArray] = start;
//				stateptr = downNFA->startState;
//				downNFA->startState = &stateArray[lengthOfStateArray];
//				++lengthOfStateArray;
//				downNFA->startState->exEdges.insert(pair<char,state*>('@', stateptr));
//				downNFA->startState->exEdges.insert(pair<char, state*>('@', upNFA->startState));
//				--lengthOfNfaArray;
//				nfaStack.push(downNFA);
//				upNFA = nullptr;				
//				break;
//			case'*':
//				upNFA = nfaStack.top();
//				nfaStack.pop();
//				start.number = number;
//				++number;
//				end.number = number;
//				stateArray[lengthOfStateArray] = end;
//				upNFA->endState->exEdges.insert(pair<char, state*>('@', upNFA->startState));
//				upNFA->endState->exEdges.insert(pair<char, state*>('@', &stateArray[lengthOfStateArray]));
//				upNFA->endState = &stateArray[lengthOfStateArray];
//				++lengthOfStateArray;
//				stateArray[lengthOfStateArray] = start;
//				stateArray[lengthOfStateArray].exEdges.insert(pair<char, state*>('@', upNFA->startState));
//				upNFA->startState = &stateArray[lengthOfStateArray];
//				++lengthOfStateArray;
//				++number;
//				upNFA->startState->exEdges.insert(pair<char, state*>('@', upNFA->endState));
//				nfaStack.push(upNFA);
//				break;
//			case'.':
//				upNFA = nfaStack.top();
//				nfaStack.pop();
//				downNFA = nfaStack.top();
//				nfaStack.pop();
//				downNFA->endState->exEdges.insert(pair<char, state*>('@',upNFA->startState ));
//				downNFA->endState = upNFA->endState;
//				--lengthOfNfaArray;
//				nfaStack.push(downNFA);
//				upNFA = nullptr;
//				break;
//			default:
//				if (now == '`') {
//					++it;
//					now= *it;
//				}
//				//遇到字符，构造一个NFA，压栈
//				ReNFA pushNFA;//用于压栈的NFA
//				start.number = number;
//				++number;
//				end.number = number;
//				stateArray[lengthOfStateArray] = end;
//				pushNFA.endState = &stateArray[lengthOfStateArray];
//				++number;
//				start.exEdges.insert(pair<char, state*>(now, &stateArray[lengthOfStateArray]));
//				++lengthOfStateArray;
//				stateArray[lengthOfStateArray] = start;
//				pushNFA.startState = &stateArray[lengthOfStateArray];
//				++lengthOfStateArray;
//				nfaArray[lengthOfNfaArray]=pushNFA;
//				nfaStack.push(&nfaArray[lengthOfNfaArray]);
//				++lengthOfNfaArray;
//			}
//		}
//		
//		//TODO 把nfaArray，stateArray的内容拷贝到一个nfaArray.size()，stateArray.size() 大小的数组中，防止浪费
//		//TODO 把新的数组存在reNfaVec中，等待合并
//		delete[] nfaArray;
//		delete[] stateArray;
//		nfaArray = nullptr;
//		stateArray = nullptr;
//		// TODO 合成一个NFA
//	}
//
//}