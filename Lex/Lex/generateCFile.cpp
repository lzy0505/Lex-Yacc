#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"structs.h"
using namespace std;

/*��ӡ���飬nameΪ��������sizeΪ�����С��valueΪ����ֵ��outΪд����ļ���*/
void print_array(string name, int size, const int *value, ofstream& out);

/*����.c�ļ�,arraysΪ���������������������endVecΪ��̬��Ӧ�Ķ���*/
int generateCFile(vector<pair<int*, int>>& arrays, vector<Rules>& endVec)
{

	ofstream out;
	out.open("lex.c", ios::out);

	//�����ж�size�Ĵ�С�Ƿ�Ϊ4
	if (arrays.size() != 4)
	{
		return -1;
	}
	
	//�������ec��,base��,next��,accept��
	vector<string> array_name;
	array_name.push_back(string("yy_ec"));
	array_name.push_back(string("yy_base"));
	array_name.push_back(string("yy_next"));
	array_name.push_back(string("yy_accept"));
	
	for (int i = 0; i < 4; i++)
	{
		print_array(array_name[i], arrays[i].second, arrays[i].first, out);
	}

	//����endVec��ӡswitch���
	out << "switch (yy_act) " << endl;
	out << "{" << endl;
	out << "case 0:" << endl;
	/*...�˴�ʡ��һЩ����*/
	out << "break;" << endl;
	for (int i = 0; i < endVec.size(); i++)
	{
		out << "case " << i + 1 << ":" << endl;
		for (int j = 0; j < endVec[i].actions.size(); j++)
		{
			out << endVec[i].actions[j] << endl;
		}
		out << "break" << endl;

	}

	out.close();
	return 0;
}
void print_array(string name, int size, const int *value,ofstream& out)
{

	const int* array_buf = value;
	out << "int	" <<name<<"[" << size << "]" << " =" << endl;
	out << "	{	0," << endl;
	for (int i = 1; i < size; i++)
	{

		out << "\t" << array_buf[i];
		if (i % 10 == 0)
		{
			out << endl;
			
		}
	}
	out << "};" << endl;
}