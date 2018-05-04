#pragma once
#ifndef  _STRUCTS_H
#define  _STRUCTS_H

#include "stdafx.h"
using std::vector;
using std::string;

//用于规则的结构体
typedef struct {
	string pattern; //RE
	vector<string> actions;//对应动作（语句）
} Rules;


#endif 