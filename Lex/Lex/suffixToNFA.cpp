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
void suffix_To_NFA(vector<Rules>& suffixRules) {
	vector<NFA> reNfaVec;//���ڴ洢ÿ��REת��������NFA
	NFA finalNfa;//���յ�NFA
	
	for (auto &rule : suffixRules) {
		string pattern = rule.pattern; //�Ѿ���׺�����pattern
		vector<string>* actions = &rule.actions;//��ȡ����
		stack<NFA> nfaStack;//���ڹ���NFA�Ĺ���ջ
		vector<string> tempActionVec;//��ʱ��̬��������

		for (auto it = pattern.cbegin() ; it != pattern.cend(); ++it)
		{
			NFA upNFA,downNFA;
			NFAstate nfaState;
			NFAstate start, end,temp1,temp2;
			char now = *it;
			cout << *it;
			switch (now) {
			case'|':
				//ȡ���������NFA���в���
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
				//��down����̬��up����̬�����ӵ�end
				upNFA.statesMap.find(upNFA.endStatesMap.begin()->first)->
					second.exEdgesMultiMap.insert(pair<char, int>('@', end.number));
				downNFA.statesMap.find(upNFA.endStatesMap.begin()->first)->
					second.exEdgesMultiMap.insert(pair<char, int>('@', end.number));
				//��upNFA��stateMap������down��
				downNFA.statesMap.insert(upNFA.statesMap.begin(), upNFA.statesMap.end());
				//�޸�downNFA����̬
				downNFA.endStatesMap.clear();
				downNFA.endStatesMap.insert(pair<int, vector<string> >(end.number, tempActionVec));			
				nfaStack.push(downNFA);		
				break;
			case'*':
				//ȡ���������NFA���в���
				upNFA = nfaStack.top();
				nfaStack.pop();
				//�½�����״̬
				start.number = number;
				++number;
				end.number = number;
				++number;
				upNFA.statesMap.insert(pair<int, NFAstate>(start.number, start));
				upNFA.statesMap.insert(pair<int, NFAstate>(end.number, end));
				//��start��upNFA��̬����
				start.exEdgesMultiMap.insert(pair<char, int>('@', upNFA.startState));
				//��start��end����
				start.exEdgesMultiMap.insert(pair<char, int>('@', end.number));
				//��upNFA����̬�ͳ�̬����
				upNFA.statesMap.find(upNFA.endStatesMap.begin()->first)->
					second.exEdgesMultiMap.insert(pair<char, int>('@', upNFA.startState));
				//������̬
				upNFA.endStatesMap.clear();
				upNFA.endStatesMap.insert(pair<int, vector<string> >(end.number,tempActionVec));
				nfaStack.push(upNFA);
				break;
			case'.':
				//ȡ��ջ��������NFA
				upNFA = nfaStack.top();
				nfaStack.pop();
				downNFA = nfaStack.top();
				nfaStack.pop();			
				//ȡ��downNFA����̬
				temp1 = downNFA.statesMap.find(downNFA.endStatesMap.begin()->first)->second;//�õ���̬
				//��ѹ������ģ�Ҳ���Ǹ�ǰ��ģ�NFA��@�����Ľ�������
				temp1.exEdgesMultiMap.insert(pair<char, int>('@', upNFA.startState));
				//������̬
				downNFA.endStatesMap.clear();
				downNFA.endStatesMap = upNFA.endStatesMap;
				//��upNFA��״̬map������downNFA�У�
				downNFA.statesMap.insert(upNFA.statesMap.begin(),upNFA.statesMap.end());
				nfaStack.push(downNFA);
				break;
			default:
				if (now == '`') {
					++it;
					now= *it;
				}
				//�����ַ�������һ��NFA��ѹջ
				NFA pushNFA;//����ѹջ��NFA
				//�½�һ����ʼ״̬
				start.number = number;
				pushNFA.statesMap.insert(pair<int, NFAstate>(number, start));
				++number;
				//�½�һ����ֹ״̬
				end.number = number;
				++number;
				pushNFA.statesMap.insert(pair<int, NFAstate>(number, end));
				//����ʼ״̬����ֹ״̬����
				start.exEdgesMultiMap.insert(pair<char, int>(now, end.number));
				//��ʶ��ǰ��̬������ȴ����vector��
				pushNFA.endStatesMap.insert(pair<int, vector<string>>(end.number, tempActionVec));
				//ѹջ
				nfaStack.push(pushNFA);
			}
		}
		
		//TODO ��nfaArray��stateArray�����ݿ�����һ��nfaArray.size()��stateArray.size() ��С�������У���ֹ�˷�
		//TODO ���µ��������reNfaVec�У��ȴ��ϲ�

		// TODO �ϳ�һ��NFA
		// conflict
	}

}