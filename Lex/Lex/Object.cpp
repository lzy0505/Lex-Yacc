#include"stdafx.h"
#include<iostream>
#include<fstream>
#include"structs.h"
using namespace std;
//以文件的形式保存类对象
int saveDFA(string fileName,DFA& dfa)
{
	ofstream out;
	out.open(fileName, ios::binary|ios::out);
	if (!out)
	{
		cout << "ERROR: can't open dfaFile " << endl;
		return -1;
	}
	out.write((char*)&dfa, sizeof(DFA));
	out.close();
	return 0;
}
//从文件中读取类对象
int readDFA(string fileName, DFA& dfa)
{
	ifstream in;
	in.open(fileName, ios::binary | ios::in);
	if (!in)
	{
		cout << "ERROR: can't open dfaFile " << endl;
		return -1;
	}
	in.read((char*)&dfa, sizeof(DFA));
	in.close();
	return 0;

}