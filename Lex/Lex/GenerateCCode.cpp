#include"stdafx.h"
#include"structs.h"

using namespace std;

/*��ӡ���飬nameΪ��������sizeΪ�����С��valueΪ����ֵ��outΪд����ļ���*/
static void print_array(string name, int size, const int *value, ofstream& out);
/*pl(),�����������*/


/*����.c�ļ�,arraysΪ���������������������endVecΪ��̬��Ӧ�Ķ���*/
int generate_c_code(vector<pair<int*, int>>& arrays, vector<Rules>& endVec, vector<string>& part1, vector<string>& part4)
{

	ofstream out;
	out.open("lex.c", ios::out);

	/*�����ж�size�Ĵ�С�Ƿ�Ϊ4*/
	if (arrays.size() != 4)
	{
		return -1;
	}
	/*�������Ŀ�ʼ*/
	out << "#define _CRT_SECURE_NO_WARNINGS" << endl; 
	out << "#include\"stdio.h\"" << endl;
	out << "#include\"stdlib.h\"" << endl;
	out << "#include\"y.tab.h\"" << endl;
	out << "#include<string.h>" << endl;
	/*�������P1��P4*/
	for (int i = 0; i < part1.size(); i++)
	{
		out << part1[i] << endl;
	}
	for (int i = 0; i < part4.size(); i++)
	{
		out << part4[i] << endl;
	}

	out << "char* getCharPtr(char* fileName);" << endl;
	out << "void findAction(int action);" << endl; /*��������*/
	out << "void addToken(char* token);" << endl; /*��token����Token����*/
	out << "void comment();" << endl; /*comment������ɶ������*/
	out << "void getTokens(unsigned num,char** _tokens);" << endl; /*�õ�Token����*/
	out << "unsigned tokenNum=0;" << endl; /*�Ѵ洢��Token����*/
	out << "unsigned arraySize=0;" << endl; /*�洢����tokens�Ĵ�С*/
	out << "int* tokens = NULL;" << endl;
	out << "int lex_main(char* fileName)" << endl;
	out << "{" << endl;

	/*�������ɱ���*/
	out << "register int yy_current_state = 0;" << endl;
	out << "register int yy_last_accepting_state = 0;" << endl;
	out << "register char *yy_cp = NULL;" << endl;
	out << "register char *yy_last_accepting_cpos = NULL;" << endl;
	out << "register int yy_act = 0;" << endl;
	


	/*����char* getCharPtr(char* fileName)�õ��ļ��ַ�ָ��*/
	out << "yy_cp=getCharPtr(fileName);" << endl;


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
	out << "while(*yy_cp!=0){" << endl;	/*����Ϊ�ַ���������'\0'*/
	out << "register int yy_c = yy_ec[(int)*yy_cp];" << endl; /*��ǰ��ȡ�ַ���Ӧ���к�*/
	out << "if(yy_accept[yy_current_state])" << endl;
	out << "{" << endl;
	out << "yy_last_accepting_state=yy_current_state;" << endl;
	out << "yy_last_accepting_cpos=yy_cp;" << endl;
	out << "}" << endl;
	out << "if(yy_next[yy_base[yy_current_state]+yy_c]==-1&&yy_last_accepting_state!=-1)" << endl;/*���Ҳ�����һ��״̬ʱ������*/
	out << "{" << endl;
	out << "yy_current_state=yy_last_accepting_state;" << endl;
	out << "yy_cp=yy_last_accepting_cpos;" << endl;
	out << "yy_act=yy_accept[yy_current_state];" << endl;
	out << "findAction(yy_act);" << endl;/*����int findAction(int action)������Action*/
	out << "yy_current_state=0;" << endl; /*��״̬��Ϊ0*/
	out << "yy_last_accepting_state=-1;" << endl;
	out << "++yy_cp;" << endl;
	out << "yy_current_state=yy_next[yy_base[yy_current_state]+yy_c];" << endl;
	out << "continue;" << endl;
	out << "}" << endl;
	out << "if(yy_next[yy_base[yy_current_state]+yy_c]==-1&&yy_last_accepting_state==-1)" << endl;
	out << "{" << endl;
	out << "printf(\"ERROR DETECTED IN INPUT FILE !\");" << endl;
	out << "}" << endl;
	out << "if(yy_next[yy_base[yy_current_state]+yy_c]!=-1) " << endl;
	out << "{" << endl;
	out << "yy_current_state=yy_next[yy_base[yy_current_state]+yy_c];" << endl;
	out << "++yy_cp;" << endl;
	out << "}" << endl;
	out << "}" << endl;

	out << "if(yy_last_accepting_cpos==yy_cp-1)" << endl;
	out << "{" << endl;
	out << "yy_act=yy_accept[yy_current_state];" << endl;
	out << "findAction(yy_act);" << endl;/*����int findAction(int action)������Action*/
	out << "}" << endl;
	out << "else{" << endl;
	out << "printf(\"ERROR DETECTED IN INPUT FILE !\");" << endl;
	out << "}" << endl;
	//out << "system(\"pause\");" << endl;
	out << "}" << endl;/*lex_mian��������*/
  

	/*void findAction(int action)����*/
	out << "void findAction(int action)" << endl;
	out << "{" << endl;
	out << "switch (action) " << endl;/*����endVec��ӡswitch���*/
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
		out << "break;" << endl;

	}
	out << "default:" << endl;
	out << "break;" << endl;
	out << "}" << endl; /*int findAction(int state��������������*/
	out << "}" << endl;/*int findAction(int action)������������*/
	/*char* getCharPtr(char* fileName)����*/
	out << "char* getCharPtr(char* fileName){" << endl;
	out << "char* cp=NULL;" << endl;
	out << "FILE *fp;" << endl;
	out << "fp=fopen(fileName,\"r\");" << endl;
	out << "if(fp==NULL)" << endl;
	out << "{" << endl;
	out << "printf(\"can't open file\");" << endl;
	out << "exit(0);" << endl;
	out << "}" << endl;
	out << "fseek(fp,0,SEEK_END);" << endl;
	out << "int flen = ftell(fp);" << endl; /* �õ��ļ���С */
	out << "cp = (char *)malloc(flen + 1);" << endl; /* �����ļ���С��̬�����ڴ�ռ� */
	out << "if (cp == NULL)" << endl;
	out << "{" << endl;
	out << "fclose(fp);" << endl;
	out <<"	return 0;"<<endl;
	out << "}" << endl;
	out << "rewind(fp);" << endl; /* ��λ���ļ���ͷ */
	out << "memset(cp,0,flen+1);" << endl;
	out << "fread(cp, sizeof(char), flen, fp);" << endl; /* һ���Զ�ȡȫ���ļ����� */
	out << "cp[flen] = 0; " << endl;/* �ַ���������־ */
	out << "return cp;" << endl;
	out << "}" << endl;
	out << "void addToken(int token){" << endl; 
	out << "if(tokenNum>=arraySize)" << endl;/*������ռ䲻��ʱ*/
	out << "{" << endl;
	out << "tokens=(int*)realloc(tokens,sizeof(int)*(arraySize+100));" << endl;
	out << "arraySize=arraySize+100;" << endl;
	out << "}" << endl;
	out << "tokens[tokenNum]=token;" << endl;
	out << "++tokenNum;" << endl;
	out << "}" << endl;
	/*getTokens()��������Yacc�õ�Token����*/
	out << "void getTokens(unsigned& num,int* _tokens){" << endl; /*�õ�Token����*/
	out << "num=tokenNum;" << endl;
	out << "_tokens=tokens;" << endl;
	out << "}" << endl;
	/*comment����*/
	out << "void comment(){" << endl; 
	out << "char c,prev=0;" << endl;
	out << "while(++yy_cp!=0)" << endl;
	out << "{" << endl;
	out << "if(c=='/'&&prev=='*')" << endl;
	out << "return;" << endl;
	out << "prev=c;" << endl;
	out << "}" << endl;
	out << "printf(\"ERROR:unterminated comment!\");" << endl;
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
