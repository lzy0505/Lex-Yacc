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

//��׺ת�ɺ�׺
void suffixRE(vector<Rules>& rules) {
	for (auto &rule :rules ) {
		string pattern = rule.pattern;//��pattern���в���
		string temp="";//������ʱװ����ȷpattern
		queue<char> q;	//������ȷ�Ķ���
		stack<char> s;	//������ջ
		for (int i = 0; i < pattern.size();++i) {
			char now = pattern[i];
			//(���ȼ���ͣ�ѹ��������
			if (now == '(') {
				s.push(now);
			}else if (now == ')') { //)��������
				while (s.top() != '(') {
					q.push(s.top());
					s.pop();
				}
				s.pop();
			}else if (now == '|') {
				if (s.empty()) {
					s.push(now);
				}else if (s.top() == '.' || s.top() == '|'||s.top()=='*') {
					//����Լ��Ǹ�С�ϵܣ��������ȼ��ߵģ�����ǡ����
					do {
						q.push(s.top());
						s.pop();
					} while (!s.empty() && (s.top() == '.' || s.top() == '|'||s.top()=='*'));
					s.push(now);
				}
				else {
					s.push(now);
				}
			}else if (now == '.') { 
				if (s.empty()) {
					s.push(now);
				}else if (s.top() == '.' || s.top() == '*') {
					//����Լ��Ǹ�С�ϵܣ��������ȼ��ߵģ�����ǡ����
					do {
						q.push(s.top());
						s.pop();
					} while (!s.empty() && (s.top() == '.'  || s.top() == '*'));
					s.push(now);
				}else {
					s.push(now);
				}
			}else if (now == '*') {
					q.push(now);
			}//��ֹ����Խ�����֭
			else if (now == '\\' && (i + 1 == pattern.size())) {
				q.push(now);
			}
			//������Լ������һЩ����ת���ַ���ֱ�Ӵ�����ȷ���о�������
			else if (now == '\\' && (pattern[i + 1] == '(' || pattern[i + 1] == ')'
				|| pattern[i + 1] == '|' || pattern[i + 1] == '.')) {
				q.push(now);
				q.push(pattern[i + 1]);
				++i;
			}//�����Ķ����ַ�������ֱ�ӷŽ���ȷ����
			else {
				q.push(now);
			}
		}
		//ջ�ﻹ�У��ͳ�ˢ����
		while (!s.empty()) {
			q.push(s.top());
			s.pop();
		}
		//����ȷ����ת��Ϊ�ַ���
		while (!q.empty()) {
			char abb = q.front();
			string a{abb};
			temp.append(a);
			q.pop();		
		}
		rule.pattern = temp;
		cout <<"temp:" <<temp<<endl;
	}


}
//int main() {
//	Rules rule;
//	vector<Rules> vecR;
//	rule.pattern = "a.b.c";
//	vecR.push_back(rule);
//}