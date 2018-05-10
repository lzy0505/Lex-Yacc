#include"stdafx.h"
#include<iostream>
#include<fstream>
#include"structs.h"
using namespace std;
//���ļ�����ʽ���������
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
//���ļ��ж�ȡ�����
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