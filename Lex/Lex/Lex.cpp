// Lex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include"rules.h"
#include<map>
#include<vector>
#include<string>
using namespace std;

int resolve(string filePath, map<string, string>& m, vector<Rules>& vRules, vector<string>&P1, vector<string>&P4);
void resolve_test();
int main()
{
	resolve_test();
    return 0;
}

