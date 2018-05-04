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


void replace(string& exp, const map<string, string>& reMap) {
	string name, expression(exp);
	stack<char> stack, output;
	bool inQuote = false, inBrace = false, inSquareBrackes = false, inParentheses = false;
	auto expressionIt = expression.begin();
	while (expressionIt != expression.end()) {
		//�滻{X}
		stack.push(*expressionIt);
		if ((*expressionIt) == '{') {
			inBrace = true;
			name = "";
			++expressionIt;
			continue;
		}
		else if ((*expressionIt) == '}') {
			inBrace = false;
			auto findIt = reMap.find(name);
			if (findIt != reMap.end()) {//�ҵ��ˣ���ԭ���ĳ�ջ���ҵ�����ջ
				while (stack.top() != '{') {
					stack.pop();
				}
				stack.pop();
				for (const char& c : findIt->second) {
					stack.push(c);
				}
			}
			else {
				throw("");
			}
			++expressionIt;
			continue;
		}
		else if (inBrace) {
			name += *expressionIt;
			++expressionIt;
			continue;
		}
		// TODO �滻[asd]
		// TODO �滻?
		// TODO �滻+

		++expressionIt;
	}

	//�������ջ������
	while (!stack.empty()) {
		output.push(stack.top());
		stack.pop();
	}
	exp = "";
	while (!output.empty()) {
		cout << output.top();
		exp += output.top();
		output.pop();
	}
}


void translate(vector<Rules>& reVec, map<string, string>& reMap) {
	//�ȴ���map�����
	for (auto & e : reMap) {
		replace(e.second, reMap);
	}

	//�ٴ���vector�����
	for (auto & e : reVec) {
		replace(e.pattern, reMap);
	}

	//TODO: ת���ַ�������������ν����  
}



void dot(vector<Rules>& reVec) {
	for (auto &re : reVec) {
		string oldExp = re.pattern;
		string dotedExp,suffixedExp;
		for (auto oldExpIt = oldExp.cbegin() ; oldExpIt != oldExp.cend() ; ++oldExpIt) {
			dotedExp += (*oldExpIt);
			if ((*oldExpIt == '\\' && *(oldExpIt-1) != '\\') || *oldExpIt == '(' || *(oldExpIt) == '|' || (*(oldExpIt ) == '.' && *(oldExpIt-1) != '\\')) continue; // ת���ַ����������������,���ӵ㿴��һ��
			if ((oldExpIt + 1) == oldExp.cend()) continue; //���һ���ַ������ӵ�
			if (*(oldExpIt + 1) == '|' || *(oldExpIt + 1) == '*' || *(oldExpIt + 1) == '.' || *(oldExpIt + 1) == ')') continue; //��һ���ַ��Ѿ��ǲ������������ţ����ӵ�
			dotedExp += '@';//as dot
		}
		cout <<"formal:"<<oldExp<<"\tdoted:"<< dotedExp << "\n";
	}
}



//int main()
//{
//	vector<Rules> test;
//	Rules re;
//	re.pattern = "{D}+{E}{FS}\?";
//	test.push_back(re);
//	map<string, string> m = { {"D","[0-9]"},{"E","([Ee][+-]?{D}+)"},{"FS","(f|F|l|L)"} };
//	translate(test, m);
//	system("pause");
//	return 0;
//}