#pragma once
#ifndef  _STRUCTS_H
#define  _STRUCTS_H

#include "stdafx.h"
using std::vector;
using std::string;

//���ڹ���Ľṹ��
typedef struct {
	string pattern; //RE
	vector<string> actions;//��Ӧ��������䣩
} Rules;


#endif 