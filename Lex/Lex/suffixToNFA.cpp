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

//��������
int number = 0;

//����׺���ʽת��ΪNFA
//void suffix_To_NFA(vector<Rules>& suffixRules) {
//	vector<ReNFA> reNfaVec;
//	NFA finalNfa;
//	
//	for (auto &rule : suffixRules) {
//		string pattern = rule.pattern; //�Ѿ���׺�����pattern
//		vector<string>* actions = &rule.actions;//��ȡ����
//		ReNFA *nfaArray = new ReNFA[pattern.size()];//�������е�ReNFA
//		int lengthOfNfaArray = 0;
//		state *stateArray = new state[4*pattern.size()];//�������е�״̬
//		int lengthOfStateArray = 0;
//		stack<ReNFA *> nfaStack;//���ڹ���NFA�Ĺ���ջ
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
//				//�����ַ�������һ��NFA��ѹջ
//				ReNFA pushNFA;//����ѹջ��NFA
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
//		//TODO ��nfaArray��stateArray�����ݿ�����һ��nfaArray.size()��stateArray.size() ��С�������У���ֹ�˷�
//		//TODO ���µ��������reNfaVec�У��ȴ��ϲ�
//		delete[] nfaArray;
//		delete[] stateArray;
//		nfaArray = nullptr;
//		stateArray = nullptr;
//		// TODO �ϳ�һ��NFA
//	}
//
//}