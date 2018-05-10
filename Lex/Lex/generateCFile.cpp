#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"structs.h"
using namespace std;

/*打印数组，name为数组名，size为数组大小，value为数组值，out为写入的文件流*/
void print_array(string name, int size, const int *value, ofstream& out);

/*生成.c文件,arrays为包含多个相关数组的容器，endVec为终态对应的动作*/
int generateCFile(vector<pair<int*, int>>& arrays, vector<Rules>& endVec)
{

	ofstream out;
	out.open("lex.c", ios::out);

	//首先判断size的大小是否为4
	if (arrays.size() != 4)
	{
		return -1;
	}
	
	//依次输出ec表,base表,next表,accept表
	vector<string> array_name;
	array_name.push_back(string("yy_ec"));
	array_name.push_back(string("yy_base"));
	array_name.push_back(string("yy_next"));
	array_name.push_back(string("yy_accept"));
	
	for (int i = 0; i < 4; i++)
	{
		print_array(array_name[i], arrays[i].second, arrays[i].first, out);
	}

	//根据endVec打印switch语句
	out << "switch (yy_act) " << endl;
	out << "{" << endl;
	out << "case 0:" << endl;
	/*...此处省略一些东西*/
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