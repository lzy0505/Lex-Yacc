#include "stdafx.h"
#include "structs.h"
using std::stack;
using std::vector;
using std::map;
using std::set;
using std::string;
using std::isalnum;
using std::isalpha;
using std::isdigit;
using std::cout;

const string ALLSET("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#%'()*+,-./:;<=>\?[\\]^{|}_ \n\t\v\f~&");
const set<char> ESCAPEDCHARS{'.','|','*','(',')'};



//替换{X}
void replaceBrace(string& exp, const map<string, string>& reMap) {
	string rename;
	vector<char> charVec;
	bool inBrace = false;
	auto expIt = exp.begin();
	while (expIt != exp.end()) {
		if ((*expIt) == '{') {
			inBrace = true;
			rename = "";
			++expIt;
			continue;
		}
		else if ((*expIt) == '}') {
			inBrace = false;
			auto findIt = reMap.find(rename);
			if (findIt != reMap.end()) {//找到了，把原来的出栈，找到的入栈
				for (const char& c : findIt->second) {
					charVec.push_back(c);
				}
			}
			else {
				throw(""); //UNDONE: 报错，找不到前面的name
			}
			++expIt;
			continue;
		}
		else if (inBrace) {
			rename += *expIt;
			++expIt;
			continue;
		}
		charVec.push_back(*expIt);
		++expIt;
	}

	//输出vector的内容
	exp = "";
	for (const auto &e : charVec) {
		exp += e;
	}
}



// 替换[X]
void constructCharSet(set<char> &s, const string &content, bool n) {
	bool flag = false;
	string stemp;
	for (auto &c : content) {//先把[]里的转义
		if (flag) {
			switch (c) {
			case 'n':
				stemp += '\n';
				break;
			case 't':
				stemp += '\t';
				break;
			case 'v':
				stemp += '\v';
				break;
			case 'f':
				stemp += '\f';
				break;
			case '\\':
				stemp += '\\';
				break;
			}
			flag = false;
			continue;
		}
		if (c == '\\') {
			flag = true;
			continue;
		}
		stemp += c;
	}
	//处理[a-z]
	auto it = stemp.cbegin();
	set<char> temp;
	while (it != stemp.cend()) {
		if (*it == '-' && ((it) != stemp.cbegin()) && ((it + 1) != stemp.cend()) && isalnum(*(it - 1)) && isalnum(*(it + 1))) {
			//当前字符是-，前后都有字符，且都是字母或数字
			auto sit = ALLSET.find(*(it - 1)) + 1;
			auto eit = ALLSET.find(*(it + 1));
			if (eit >= sit) {
				// UNDONE: 报错：[]内部格式不对
			}
			while (sit != eit) {
				temp.insert(ALLSET[sit]);
				++sit;
			}
			++it;
		}
		else {
			temp.insert(*it);//插入就完事了
			++it;
		}
	}
	if (n) {//集合取反
		for (const char &c : ALLSET) {
			if (temp.find(c) == temp.end()) {
				s.insert(c);
			}
		}
	}
	else {
		s = temp;
	}
}

void replaceSquareBrace(string& exp) {
	string sbcontent;
	vector<char> charVec;
	bool inSquareBrackes = false;
	auto expIt = exp.begin();
	while (expIt != exp.end()) {
		if ((*expIt) == '[') {
			inSquareBrackes = true;
			sbcontent = "";
			++expIt;
			continue;
		}
		else if ((*expIt) == ']') {
			inSquareBrackes = false;
			charVec.push_back('(');
			set<char> s;//保存转换过的字符
			if (sbcontent[0] == '^') { // 非操作
				constructCharSet(s, sbcontent.substr(1, sbcontent.size() - 1), true);
			}
			else {
				constructCharSet(s, sbcontent, false);
			}
			for (const auto &c : s) {
				if(ESCAPEDCHARS.find(c)!= ESCAPEDCHARS.cend())//转义
					charVec.push_back('\\');
				charVec.push_back(c);
				charVec.push_back('|');
			}
			charVec.pop_back();
			charVec.push_back(')');
			++expIt;
			continue;
		}
		else if (inSquareBrackes) {
			sbcontent += *expIt;
			++expIt;
			continue;
		}
		
		charVec.push_back(*expIt);
		++expIt;
	}
	//输出vector的内容

	exp = "";
	for (const auto &e : charVec) {
		exp += e;
	}
	cout << exp;
}


// NEXT: 处理引号问题
void handleQuote(string& exp) {}

// NEXT: 替换？和+ (同时处理括号)
void replaceQuestionAndAdd(string& exp){}


// TODO: 加点
void  addDot(string &exp) {
	string oldExp = exp;
	string dotedExp, suffixedExp;
	for (auto oldExpIt = oldExp.cbegin(); oldExpIt != oldExp.cend(); ++oldExpIt) {
		dotedExp += (*oldExpIt);
		if ((*oldExpIt == '\\' && *(oldExpIt - 1) != '\\') || *oldExpIt == '(' || *(oldExpIt) == '|' || (*(oldExpIt) == '.' && *(oldExpIt - 1) != '\\')) continue; // 转义字符或操作符或左括号,不加点看下一个
		if ((oldExpIt + 1) == oldExp.cend()) continue; //最后一个字符，不加点
		if (*(oldExpIt + 1) == '|' || *(oldExpIt + 1) == '*' || *(oldExpIt + 1) == '.' || *(oldExpIt + 1) == ')') continue; //下一个字符已经是操作符或右括号，不加点
		dotedExp += '@';//as dot
	}
	cout << "formal:" << oldExp << "\tdoted:" << dotedExp << "\n";
}


void translate(vector<Rules>& reVec, map<string, string>& reMap) {
	// TODO: 先处理map里面的
	//for (auto & e : reMap) {
	//	replace(e.second, reMap);
	//}

	//再处理vector里面的
	for (auto & e : reVec) {
		replaceBrace(e.pattern, reMap);
		replaceSquareBrace(e.pattern);
		cout << "\n";
		handleQuote(e.pattern);
		cout << "\n";
		replaceQuestionAndAdd(e.pattern);
		cout << "\n";
		addDot(e.pattern);
	}
 
}