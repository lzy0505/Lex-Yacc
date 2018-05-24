#include"stdafx.h"
#include"structs.h"
using std::map;


// 先处理所有的token, 都转换并替代成正整数。
// char 0-255
// tokens 256-n
// 非终结符 n-m

extern int boundTInt, boundNInt, startInt;
extern ProducerVec producerVec;
extern map<int, pair<int, int> > indexMap;
extern vector<unordered_set<int> > precedenceRulesVec;
map<string, int> tokensMap;//<token,number>

void translate_expression(const string &startItemStr, const vector<string> &tokensVec, const ProducerVecStr & producerVecStr,  const vector<unordered_set<string>>&left) {
	int count = 256;
	
	for (const auto &token : tokensVec) {
		tokensMap.emplace(token, count++);
	}
	boundTInt = count - 1;
	for (const auto &producer : producerVecStr) {
		auto result = tokensMap.try_emplace(producer.first, count);
		if (result.second)++count;
	}
	boundNInt = count - 1;

	for (const auto & s : left) {
		unordered_set<int> newSet;
		for (const auto & e : s) {
			if (e[0] == '\'' && e[2] == '\'') {
				newSet.insert((int)e[1]);
			}
			else {
				newSet.insert(tokensMap[e]);
			}
		}
		precedenceRulesVec.push_back(newSet);
	}

	vector<int > tempRightVec;
	int preleftInt = boundTInt + 1, counter = 0, temp;
	for (const auto &producer : producerVecStr) {
		tempRightVec.clear();
		//翻译右部产生式
		for (const auto & item : producer.second) {
			if (item[0] == '\'' && item[2] == '\'') {
				tempRightVec.push_back((int)item[1]);
			}
			else {
				tempRightVec.push_back(tokensMap[item]);
			}
		}
		//翻译左部产生式并存入
		temp = tokensMap[producer.first];
		if (temp != preleftInt) {
			indexMap.try_emplace(preleftInt, pair<int,int>(producerVec.size()- counter,counter));
			counter = 0;
			preleftInt = temp;
		}
		producerVec.push_back(pair<int,vector<int> >(temp, tempRightVec));
		++counter;
		
	}
	indexMap.try_emplace(preleftInt, pair<int, int>(producerVec.size() - counter, counter));

	startInt = tokensMap[startItemStr];
	producerVec.push_back(pair<int, vector<int> >(0, vector<int>({ startInt })));
}