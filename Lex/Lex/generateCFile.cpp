#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include"structs.h"
using namespace std;

/*打印数组，name为数组名，size为数组大小，value为数组值，out为写入的文件流*/
void print_array(string name, int size, const int *value, ofstream& out);
/*pl(),单行输出函数*/


/*生成.c文件,arrays为包含多个相关数组的容器，endVec为终态对应的动作*/
int generateCFile(vector<pair<int*, int>>& arrays, vector<Rules>& endVec, vector<string>& part1, vector<string>& part4)
{

	ofstream out;
	out.open("lex.c", ios::out);

	/*首先判断size的大小是否为4*/
	if (arrays.size() != 4)
	{
		return -1;
	}
	/*主函数的开始*/
	out << "#include\"stdio.h\"" << endl;
	/*依次输出P1和P4*/
	for (int i = 0; i < part1.size(); i++)
	{
		out << part1[i] << endl;
	}
	for (int i = 0; i < part1.size(); i++)
	{
		out << part4[i] << endl;
	}

	out << "char* getCharPtr(char* fileName);" << endl;
	out << "int findAction(int action);" << endl; /*函数声明*/

	out << "int main(int argc,char** argv)" << endl;
	out << "{" << endl;

	/*定义若干变量*/
	out << "register int yy_current_state = 0;" << endl;
	out << "register int yy_last_accepting_state = 0;" << endl;
	out << "register char *yy_cp = NULL;" << endl;
	out << "register char *yy_last_accepting_cpos = NULL;" << endl;
	out << "register int yy_act = 0;" << endl;

	/*调用char* getCharPtr(char* fileName)得到文件字符指针*/
	out << "yy_cp=getCharPtr(argv[1]);" << endl;


	/*依次输出ec表,base表,next表,accept表*/
	vector<string> array_name;
	array_name.push_back(string("yy_ec"));
	array_name.push_back(string("yy_base"));
	array_name.push_back(string("yy_next"));
	array_name.push_back(string("yy_accept"));

	for (int i = 0; i < 4; i++)
	{
		print_array(array_name[i], arrays[i].second, arrays[i].first, out);

	}


	/*状态跳转部分*/
	out << "while(*cp!=0){" << endl;	/*若不为字符串结束符'\0'*/
	out << "register int yy_c = yy_ec[(int)*yy_cp];" << endl; /*当前读取字符对应的列号*/
	out << "if(yy_accept[yy_current_state])" << endl;
	out << "{" << endl;
	out << "yy_last_accepting_state=yy_current_state;" << endl;
	out << "yy_last_accepting_cpos=yy_cp;" << endl;
	out << "}" << endl;
	out << "if(yy_next[yy_base[yy_current_satte]+yy_c]==-1&&yy_last_accepting_state!=-1)" << endl;/*当找不到下一个状态时，回退*/
	out << "{" << endl;
	out << "yy_current_state=yy_last_accepting_state;" << endl;
	out << "yy_cp=yy_last_accepting_cpos;" << endl;
	out << "yy_act=yy_accept[yy_current_state];" << endl;
	out << "findAction(yy_act);" << endl;/*调用int findAction(int action)来返回Action*/
	out << "yy_last_accepting_state=-1;" << endl;
	out << "}" << endl;
	out << "if(yy_next[yy_base[yy_current_satte]+yy_c]==-1&&yy_last_accepting_state==-1)" << endl;
	out << "{" << endl;
	out << "printf(\"ERROR DETECTED IN INPUT FILE !\");" << endl;
	out << "}" << endl;
	out << "if(yy_next[yy_base[yy_current_satte]+yy_c]!=-1) " << endl;
	out << "{" << endl;
	out << "yy_current_state=yy_next[yy_base[yy_current_satte]+yy_c];" << endl;
	out << "}" << endl;
	out << "++yy_cp;" << endl;
	out << "}" << endl;
	out << "if(yy_last_accepting_cpos==yy_cp-1)" << endl;
	out << "{" << endl;
	out << "yy_current_state=yy_last_accepting_state;" << endl;
	out << "yy_cp=yy_last_accepting_cpos;" << endl;
	out << "yy_act=yy_accept[yy_current_state];" << endl;
	out << "findAction(yy_act);" << endl;/*调用int findAction(int action)来返回Action*/
	out << "}" << endl;
	out << "else{" << endl;
	out << "printf(\"ERROR DETECTED IN INPUT FILE !\");" << endl;
	out << "}" << endl;
	out << "}" << endl;/*mian函数结束*/
  

	/*int findAction(int action)函数*/
	out << "int findAction(int action)" << endl;
	out << "{" << endl;
	out << "switch (yy_act) " << endl;/*根据endVec打印switch语句*/
	out << "{" << endl;
	out << "case 0:" << endl;
	/*...此处省略了一些东西*/
	out << "break;" << endl;
	for (int i = 0; i < endVec.size(); i++)
	{
		out << "case " << i + 1 << ":" << endl;
		for (int j = 0; j < endVec[i].actions.size(); j++)
		{
			out << endVec[i].actions[j] << endl;
		}
		out << "break;" << endl;

	}
	out << "default:" << endl;
	out << "break;" << endl;
	out << "}" << endl; /*int findAction(int state）函数的下括号*/
	out << "}" << endl;/*int findAction(int action)函数的下括号*/
	/*char* getCharPtr(char* fileName)函数*/
	out << "char* getCharPtr(char* fileName){" << endl;
	out << "char* cp=NULL;" << endl;
	out << "FILE *fp;" << endl;
	out << "fp=fopen(fileName,\"w\")" << endl;
	out << "if(fp==NULL)" << endl;
	out << "{" << endl;
	out << "printf(\"can't open file\")" << endl;
	out << "getch()" << endl;
	out << "exit(0)" << endl;
	out << "}" << endl;
	out << "fseek(fp,OL,SEEK_END);" << endl;
	out << "int flen = ftell(fp);" << endl; /* 得到文件大小 */
	out << "p = (char *)malloc(flen + 1);" << endl; /* 根据文件大小动态分配内存空间 */
	out << "if (p == NULL)" << endl;
	out << "{" << endl;
	out << "fclose(fp);" << endl;
	out <<"	return 0;"<<endl;
	out << "}" << endl;
	out << "fseek(fp, 0L, SEEK_SET);" << endl; /* 定位到文件开头 */
	out << "fread(p, flen, 1, fp);" << endl; /* 一次性读取全部文件内容 */
	out << "p[flen] = 0; " << endl;/* 字符串结束标志 */
	out << "return p;" << endl;
	out << "}" << endl;
	out.close();
	return 0;
}
void print_array(string name, int size, const int *value,ofstream& out)
{

	const int* array_buf = value;
	out << "static int	" <<name<<"[" << size << "]" << " =" << endl;
	out << "	{	0," << endl;
	for (int i = 1; i < size; i++)
	{
		
		out << setw(4) << left << array_buf[i];
		if (i != size - 1)
		{
			out << ",";
		}
		if (i % 10 == 0)
		{
			out << endl;			
		}
	}
	out << "};" << endl;
}
