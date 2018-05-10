#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"structs.h"
using namespace std;

/*��ӡ���飬nameΪ��������sizeΪ�����С��valueΪ����ֵ��outΪд����ļ���*/
void print_array(string name, int size, const int *value, ofstream& out);
/*pl(),�����������*/


/*����.c�ļ�,arraysΪ���������������������endVecΪ��̬��Ӧ�Ķ���*/
int generateCFile(vector<pair<int*, int>>& arrays, vector<Rules>& endVec)
{

	ofstream out;
	out.open("lex.c", ios::out);

	/*�����ж�size�Ĵ�С�Ƿ�Ϊ4*/
	if (arrays.size() != 4)
	{
		return -1;
	}
	/*�������Ŀ�ʼ*/
	out << "int findAction(int action);" << endl; /*��������*/
	out << "int main(int argc,char** argv)" << endl;
	out << "{" << endl;

	/*�������ɱ���*/
	out << "register int yy_current_state = 0;" << endl;
	out << "register int yy_last_accepting_state = 0;" << endl;
	out << "register char *yy_cp = NULL;" << endl;
	out << "register char *yy_last_accepting_cpos = NULL;" << endl;
	out << "register int yy_act = 0;" << endl;

	/*����char* getCharPtr(char* fileName)�õ��ļ��ַ�ָ��*/
	out << "yy_cp=getCharPtr(argv[1]);" << endl;


	/*�������ec��,base��,next��,accept��*/
	vector<string> array_name;
	array_name.push_back(string("yy_ec"));
	array_name.push_back(string("yy_base"));
	array_name.push_back(string("yy_next"));
	array_name.push_back(string("yy_accept"));

	for (int i = 0; i < 4; i++)
	{
		print_array(array_name[i], arrays[i].second, arrays[i].first, out);
	}


	/*״̬��ת����*/
	out << "while(*cp!=26){" << endl;	/*windows���ļ�������Ϊctrl+z,asciiΪ26*/
	out << "register int yy_c = yy_ec[(int)*yy_cp];" << endl; /*��ǰ��ȡ�ַ���Ӧ���к�*/
	out << "if(yy_accept[yy_current_state])" << endl;
	out << "{" << endl;
	out << "yy_last_accepting_state=yy_current_state;" << endl;
	out << "yy_last_accepting_cpos=yy_cp;" << endl;
	out << "}" << endl;
	out << "if(yy_next[yy_base[yy_current_satte]+yy_c]==0)" << endl;/*���Ҳ�����һ��״̬ʱ������*/
	out << "{" << endl;
	out << "yy_current_state=yy_last_accepting_state;" << endl;
	out << "yy_cp=yy_last_accepting_cpos;" << endl;
	out << "yy_act=yy_accept[yy_current_state];" << endl;
	out << "findAction(yy_act);" << endl;/*����int findAction(int action)������Action*/
	out << "}" << endl;
	out << "else {" << endl;
	out << "yy_current_state=yy_next[yy_base[yy_current_satte]+yy_c];";
	out << "}" << endl;
	out << "++yy_cp;" << endl;
	out << "}" << endl;
	out << "}" << endl;/*mian��������*/
  

	/*int findAction(int action)����*/
	out << "int findAction(int action)" << endl;
	out << "{" << endl;
	out << "switch (yy_act) " << endl;/*����endVec��ӡswitch���*/
	out << "{" << endl;
	out << "case 0:" << endl;
	/*...�˴�ʡ����һЩ����*/
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
	out << "}" << endl; /*int findAction(int state��������������*/



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
