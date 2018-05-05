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
void suffix_To_NFA(vector<Rules>& suffixRules) {
	vector<ReNFA> nfas;
	NFA finalNfa;
	
	for (auto &rule : suffixRules) {
		string pattern = rule.pattern; //已经后缀化后的pattern
		vector<string>* actions = &rule.actions;//获取操作
		vector<ReNFA> NFAvec;//保存所有的ReNFA
		vector<state> stateVec;//保存所有的状态
		stack<ReNFA*> NFAstack;//用于构建ReNFA的工具栈
		

		for (auto it = pattern.cbegin() ; it != pattern.cend(); ++it)
		{
			ReNFA*upNFA=nullptr,*downNFA=nullptr;
			state * stateptr = nullptr;
			state start, end;
			char now = *it;
			switch (now) {
			case'|':
				upNFA = NFAstack.top();
				NFAstack.pop();
				downNFA = NFAstack.top();
				NFAstack.pop();
				start.number = number;
				++number;
				end.number = number;
				stateVec.push_back(end);			
				stateptr = &stateVec.back();
				++number;
				downNFA->endState->exEdges.insert(pair<char, state*>('@',stateptr));
				upNFA->endState->exEdges.insert(pair<char, state*>('@', stateptr));
				downNFA->endState = stateptr;
				stateVec.push_back(start);
				stateptr = downNFA->startState;
				downNFA->startState = &stateVec.back();
				downNFA->startState->exEdges.insert(pair<char,state*>('@', stateptr));
				downNFA->startState->exEdges.insert(pair<char, state*>('@', upNFA->startState));
				NFAvec.pop_back();
				NFAstack.push(downNFA);
				upNFA = nullptr;				
				break;
			case'*':
				upNFA = NFAstack.top();
				NFAstack.pop();
				start.number = number;
				++number;
				end.number = number;
				stateVec.push_back(end);
				upNFA->endState->exEdges.insert(pair<char, state*>('@', upNFA->startState));
				upNFA->endState->exEdges.insert(pair<char, state*>('@', &stateVec.back()));
				upNFA->endState = &stateVec.back();
				stateVec.push_back(start);
				stateVec.back().exEdges.insert(pair<char, state*>('@', upNFA->startState));
				upNFA->startState = &stateVec.back();
				++number;
				upNFA->startState->exEdges.insert(pair<char, state*>('@', upNFA->endState));
				NFAstack.push(downNFA);
				break;
			case'.':
				upNFA = NFAstack.top();
				NFAstack.pop();
				 downNFA=NFAstack.top();
				NFAstack.pop();
				downNFA->endState->exEdges.insert(pair<char, state*>('@',upNFA->startState ));
				downNFA->endState = upNFA->endState;
				NFAvec.pop_back();
				NFAstack.push(downNFA);
				upNFA = nullptr;
				break;
			default:
				if (now == '`') {
					++it;
					now= *it;
				}
				//遇到字符，构造一个NFA，压栈
				ReNFA pushNFA;//用于压栈的NFA
				start.number = number;
				++number;
				end.number = number;
				stateVec.push_back(end);
				pushNFA.endState = &stateVec.back();
				++number;
				start.exEdges.insert(pair<char, state*>(now, &stateVec.back()));
				stateVec.push_back(start);
				pushNFA.startState = &stateVec.back();

				NFAvec.push_back(pushNFA);
				NFAstack.push(&NFAvec.back());
				
			}
		}
		
	}

}