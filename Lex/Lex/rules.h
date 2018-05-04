#ifndef  _RULES_H
#define  _RULES_H

#include<string>
#include<vector>
//规则结构体定义
typedef struct Rules {
	std::string pattern;
	std::vector<std::string> action;
}Rules;

#endif // ! _RULES_H
