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
		//替换{X}
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
			if (findIt != reMap.end()) {//找到了，把原来的出栈，找到的入栈
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
		// TODO 替换[asd]
		// TODO 替换?
		// TODO 替换+

		++expressionIt;
	}

	//逆向输出栈的内容
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
	//先处理map里面的
	for (auto & e : reMap) {
		replace(e.second, reMap);
	}

	//再处理vector里面的
	for (auto & e : reVec) {
		replace(e.pattern, reMap);
	}

	//TODO: 转义字符和引号问题如何解决？  
}



void dot(vector<Rules>& reVec) {
	for (auto &re : reVec) {
		string oldExp = re.pattern;
		string dotedExp,suffixedExp;
		for (auto oldExpIt = oldExp.cbegin() ; oldExpIt != oldExp.cend() ; ++oldExpIt) {
			dotedExp += (*oldExpIt);
			if ((*oldExpIt == '\\' && *(oldExpIt-1) != '\\') || *oldExpIt == '(' || *(oldExpIt) == '|' || (*(oldExpIt ) == '.' && *(oldExpIt-1) != '\\')) continue; // 转义字符或操作符或左括号,不加点看下一个
			if ((oldExpIt + 1) == oldExp.cend()) continue; //最后一个字符，不加点
			if (*(oldExpIt + 1) == '|' || *(oldExpIt + 1) == '*' || *(oldExpIt + 1) == '.' || *(oldExpIt + 1) == ')') continue; //下一个字符已经是操作符或右括号，不加点
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