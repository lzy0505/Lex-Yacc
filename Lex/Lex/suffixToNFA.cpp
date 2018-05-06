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
	vector<NFA> reNfaVec;//用于存储每个RE转换出来的NFA
	NFA finalNfa;//最终的NFA
	
	for (auto &rule : suffixRules) {
		string pattern = rule.pattern; //已经后缀化后的pattern
		vector<string>* actions = &rule.actions;//获取操作
		stack<NFA> nfaStack;//用于构建NFA的工具栈
		vector<string> tempActionVec;//临时终态动作数组

		for (auto it = pattern.cbegin() ; it != pattern.cend(); ++it)
		{
			NFA upNFA,downNFA;
			NFAstate nfaState;
			NFAstate start, end,temp1,temp2;
			char now = *it;
			cout << *it;
			switch (now) {
			case'|':
				//取出最上面的NFA进行操作
				upNFA = nfaStack.top();
				nfaStack.pop();
				downNFA = nfaStack.top();
				nfaStack.pop();
				start.number = number;
				++number;
				end.number = number;
				++number;
				downNFA.statesMap.insert(pair<int, NFAstate>(start.number, start));
				downNFA.statesMap.insert(pair<int, NFAstate>(end.number, end));
				//将down的终态和up的终态都连接到end
				upNFA.statesMap.find(upNFA.endStatesMap.begin()->first)->
					second.exEdgesMultiMap.insert(pair<char, int>('@', end.number));
				downNFA.statesMap.find(upNFA.endStatesMap.begin()->first)->
					second.exEdgesMultiMap.insert(pair<char, int>('@', end.number));
				//将upNFA的stateMap拷贝到down中
				downNFA.statesMap.insert(upNFA.statesMap.begin(), upNFA.statesMap.end());
				//修改downNFA的终态
				downNFA.endStatesMap.clear();
				downNFA.endStatesMap.insert(pair<int, vector<string> >(end.number, tempActionVec));			
				nfaStack.push(downNFA);		
				break;
			case'*':
				//取出最上面的NFA进行操作
				upNFA = nfaStack.top();
				nfaStack.pop();
				//新建两个状态
				start.number = number;
				++number;
				end.number = number;
				++number;
				upNFA.statesMap.insert(pair<int, NFAstate>(start.number, start));
				upNFA.statesMap.insert(pair<int, NFAstate>(end.number, end));
				//将start和upNFA初态连接
				start.exEdgesMultiMap.insert(pair<char, int>('@', upNFA.startState));
				//将start和end连接
				start.exEdgesMultiMap.insert(pair<char, int>('@', end.number));
				//将upNFA的终态和初态连接
				upNFA.statesMap.find(upNFA.endStatesMap.begin()->first)->
					second.exEdgesMultiMap.insert(pair<char, int>('@', upNFA.startState));
				//更改终态
				upNFA.endStatesMap.clear();
				upNFA.endStatesMap.insert(pair<int, vector<string> >(end.number,tempActionVec));
				nfaStack.push(upNFA);
				break;
			case'.':
				//取出栈顶的两个NFA
				upNFA = nfaStack.top();
				nfaStack.pop();
				downNFA = nfaStack.top();
				nfaStack.pop();			
				//取出downNFA的终态
				temp1 = downNFA.statesMap.find(downNFA.endStatesMap.begin()->first)->second;//得到终态
				//将压在下面的（也就是更前面的）NFA用@与后面的进行连接
				temp1.exEdgesMultiMap.insert(pair<char, int>('@', upNFA.startState));
				//更改终态
				downNFA.endStatesMap.clear();
				downNFA.endStatesMap = upNFA.endStatesMap;
				//把upNFA的状态map拷贝到downNFA中，
				downNFA.statesMap.insert(upNFA.statesMap.begin(),upNFA.statesMap.end());
				nfaStack.push(downNFA);
				break;
			default:
				if (now == '`') {
					++it;
					now= *it;
				}
				//遇到字符，构造一个NFA，压栈
				NFA pushNFA;//用于压栈的NFA
				//新建一个起始状态
				start.number = number;
				pushNFA.statesMap.insert(pair<int, NFAstate>(number, start));
				++number;
				//新建一个终止状态
				end.number = number;
				++number;
				pushNFA.statesMap.insert(pair<int, NFAstate>(number, end));
				//将起始状态和终止状态连接
				start.exEdgesMultiMap.insert(pair<char, int>(now, end.number));
				//标识当前终态，因此先传入空vector。
				pushNFA.endStatesMap.insert(pair<int, vector<string>>(end.number, tempActionVec));
				//压栈
				nfaStack.push(pushNFA);
			}
		}
		
		//TODO 把nfaArray，stateArray的内容拷贝到一个nfaArray.size()，stateArray.size() 大小的数组中，防止浪费
		//TODO 把新的数组存在reNfaVec中，等待合并

		// TODO 合成一个NFA
		// conflict
	}

}