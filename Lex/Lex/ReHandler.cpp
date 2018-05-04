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



//�滻{X}
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
			if (findIt != reMap.end()) {//�ҵ��ˣ���ԭ���ĳ�ջ���ҵ�����ջ
				for (const char& c : findIt->second) {
					charVec.push_back(c);
				}
			}
			else {
				throw(""); //UNDONE: �����Ҳ���ǰ���name
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

	//���vector������
	exp = "";
	for (const auto &e : charVec) {
		exp += e;
	}
}



// �滻[X]
void constructCharSet(set<char> &s, const string &content, bool n) {
	bool flag = false;
	string stemp;
	for (auto &c : content) {//�Ȱ�[]���ת��
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
	//����[a-z]
	auto it = stemp.cbegin();
	set<char> temp;
	while (it != stemp.cend()) {
		if (*it == '-' && ((it) != stemp.cbegin()) && ((it + 1) != stemp.cend()) && isalnum(*(it - 1)) && isalnum(*(it + 1))) {
			//��ǰ�ַ���-��ǰ�����ַ����Ҷ�����ĸ������
			auto sit = ALLSET.find(*(it - 1)) + 1;
			auto eit = ALLSET.find(*(it + 1));
			if (eit >= sit) {
				// UNDONE: ����[]�ڲ���ʽ����
			}
			while (sit != eit) {
				temp.insert(ALLSET[sit]);
				++sit;
			}
			++it;
		}
		else {
			temp.insert(*it);//�����������
			++it;
		}
	}
	if (n) {//����ȡ��
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
			set<char> s;//����ת�������ַ�
			if (sbcontent[0] == '^') { // �ǲ���
				constructCharSet(s, sbcontent.substr(1, sbcontent.size() - 1), true);
			}
			else {
				constructCharSet(s, sbcontent, false);
			}
			for (const auto &c : s) {
				if(ESCAPEDCHARS.find(c)!= ESCAPEDCHARS.cend())//ת��
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
	//���vector������

	exp = "";
	for (const auto &e : charVec) {
		exp += e;
	}
	cout << exp;
}


// NEXT: ������������
void handleQuote(string& exp) {}

// NEXT: �滻����+ (ͬʱ��������)
void replaceQuestionAndAdd(string& exp){}


// TODO: �ӵ�
void  addDot(string &exp) {
	string oldExp = exp;
	string dotedExp, suffixedExp;
	for (auto oldExpIt = oldExp.cbegin(); oldExpIt != oldExp.cend(); ++oldExpIt) {
		dotedExp += (*oldExpIt);
		if ((*oldExpIt == '\\' && *(oldExpIt - 1) != '\\') || *oldExpIt == '(' || *(oldExpIt) == '|' || (*(oldExpIt) == '.' && *(oldExpIt - 1) != '\\')) continue; // ת���ַ����������������,���ӵ㿴��һ��
		if ((oldExpIt + 1) == oldExp.cend()) continue; //���һ���ַ������ӵ�
		if (*(oldExpIt + 1) == '|' || *(oldExpIt + 1) == '*' || *(oldExpIt + 1) == '.' || *(oldExpIt + 1) == ')') continue; //��һ���ַ��Ѿ��ǲ������������ţ����ӵ�
		dotedExp += '@';//as dot
	}
	cout << "formal:" << oldExp << "\tdoted:" << dotedExp << "\n";
}


void translate(vector<Rules>& reVec, map<string, string>& reMap) {
	// TODO: �ȴ���map�����
	//for (auto & e : reMap) {
	//	replace(e.second, reMap);
	//}

	//�ٴ���vector�����
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