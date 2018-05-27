#include"stdafx.h"
#include"structs.h"
#include<fstream>
#include<iomanip>

using namespace std;
// TODO : 赵某
extern vector<pair<void*, int> > table_vec;
extern vector<string> tokensVec;
void print_array(string name, int size, void *value, ofstream& out);
void generate_files() {
	/*第一部分y.tab.h*/
	ofstream out;
	out.open("y.tab.h", ios::out);
	out << "#ifndef Y_TAB_H" << endl;
	out << "#define Y_TAB_H" << endl;
	string* pInt = (string *)table_vec[6].first;
	for (int i = 0; i < table_vec[6].second; i++)
	{

		out << "#define  " << pInt[i] <<"    "<< i+256 << endl;

	}
	
	out << "#endif" << endl;
	out.close();



	/*第二部分y.tab.c*/
	
	out.open("y.tab.c", ios::out);

	if (!out)
	{
		cout << "ERROR: can't open file y.tab.c !" << endl;
	}
	out << "include<stdio.h>" << endl;
	out << "include<stdlib.h>" << endl;
	out << "include<assert.h>" << endl;
	/*声明函数*/
	//out << "int getOneToken(int& token);" << endl;
	//out << "int nextToken();" << endl;
	//out << "int tokenIndex=0;" << endl;/*token数组的索引*/
	//out << "int *tokens=NULL;" << endl;/*token数组*/
	//out << "int tokenLength=0;" << endl; /*token的长度*/
	out << "void lex_init(char* fileName);" << endl;
	out << "int yy_lex();" << endl;/*yy_lex外部函数定义*/
	//out << "void getTokens(unsigned num, int* _tokens);" << endl;


	/*栈定义部分*/
	out << "struct Node" << endl;
	out << "{" << endl;
	out << "	int data;" << endl;
	out << "	struct Node* next;" << endl;
	out << "};" << endl;

	out << "struct Stack" << endl;
	out << "{" << endl;
	out << "struct Node* head;" << endl;
	out << "int size;" << endl;
	out << "};" << endl;

	out << "void StackInit(struct Stack* stack)" << endl;
	out << "{" << endl;
	out << "	stack->head = NULL;" << endl;
	out << "	stack->size = 0;" << endl;
	out << "}" << endl;

	out << "void StackPush(struct Stack* stack, const int data)//进栈 " << endl;
	out << "{" << endl;
	out << "struct Node* node;" << endl;
	out << "node = (struct Node*)malloc(sizeof(struct Node));" << endl;
	out << "assert(node != NULL);" << endl;
	out << "node->data = data;" << endl;
	out << "node->next = stack->head;" << endl;
	out << "stack->head = node;" << endl;
	out << "++stack->size;" << endl;
	out << "}" << endl;

	out << "int StackEmpty(struct Stack* stack)" << endl;
	out << "{" << endl;
	out << "return (stack->size == 0);" << endl;
	out << "}" << endl;

	out << "int StackPop(struct Stack* stack, int* data)//出栈  " << endl;
	out << "{" << endl;
	out << "if (StackEmpty(stack))" << endl;
	out << "{" << endl;
	out << "	return 0;" << endl;
	out << "}" << endl;

	out << "	struct Node* tmp = stack->head;" << endl;
	out << "	*data = stack->head->data;" << endl;
	out << "	stack->head = stack->head->next;" << endl;
	out << "	free(tmp);" << endl;
	out << "--stack->size;" << endl;

	out << "	return 1;" << endl;
	out << "}" << endl;
	out << "int StackTop(struct Stack* stack, int* data)" << endl;
	out << "{" << endl;

	out << "	if (StackEmpty(stack))" << endl;
	out << "	{" << endl;
	out << "		return 0;" << endl;
	out << "	}" << endl;
	out << "	*data = stack->head->data;" << endl;
	out << "	return 1;" << endl;
	out << "}" << endl;
	out << "void StackCleanup(struct Stack* stack)" << endl;
	out << "{" << endl;
	out << "struct Node* tmp;" << endl;
	out << "while (stack->head)" << endl;
	out << "{" << endl;
	out << "		tmp = stack->head;" << endl;
	out << "		stack->head = stack->head->next;" << endl;
	out << "		free(tmp);" << endl;
	out << "	}" << endl;

	out << "	stack->size = 0;" << endl;
	out << "}" << endl;


	
	/*table_vec.push_back(pair<void*, int>(next, (boundNInt + 2)*lrdfa.statesVec.size()));
	table_vec.push_back(pair<void*, int>(base, lrdfa.statesVec.size() + 1));
	table_vec.push_back(pair<void*, int>(producer_data, 5 * producerVec.size()));
	table_vec.push_back(pair<void*, int>(index, 2 * producerVec.size()));
	table_vec.push_back(pair<void*, int>(productions, boundTInt + 1));
	table_vec.push_back(pair<void*, int>(map_vec, defineCount));
	table_vec.push_back(pair<void*, int>(tokens, tokensDefineMap.size()));
	*/
	print_array("yy_next", table_vec[0].second, table_vec[0].first, out);
	print_array("yy_base", table_vec[1].second, table_vec[1].first, out);
	print_array("yy_producer_data", table_vec[2].second, table_vec[2].first, out);
	print_array("yy_index", table_vec[3].second, table_vec[3].first, out);
	print_array("yy_map_vec", table_vec[5].second, table_vec[5].first, out);
	
	/*对字符串类型数组单独处理*/
	
	out << "static char* yy_productions[]=" << endl;
	out << "{" << endl;

	string* pStr = (string*)table_vec[4].first;
	for (int i = 0; i < table_vec[4].second - 1; i++)
	{

		out << "\"" << pStr[i] << "\"" << ", ";
		if (i % 5 == 0)
		{
			out << endl;
		}
	}
	
	/*最后一个元素没得逗号*/

	out << "\"" << pStr[table_vec[4].second - 1] << "\"" << endl << "}" << endl;



	/*main()函数部分*/

	out << "int main(int argc,char **argv)" << endl;
	out << "{" << endl;

	/*调用lex_main*/
	out << "lex_init(\"q.txt\");" << endl;



	/*创建两个栈，状态栈和符号栈*/

	out << "Struct Stack stateStack;" << endl;
	out << "Struct Stack symbolStack;" << endl;
	out << "StackInit(&stateStack);" << endl;
	out << "StackInit(&symbolStack);" << endl;

	/*将初始状态和终结符压到两个栈中*/
	out << "StackPush(&stateStack,0);" << endl;
	out << "StackPush(&symbolStack,-2);" << endl;/*符号栈压入$*/
	out << "int token=0;" << endl; /*存放每次读取的token*/
	out << "int item=0;" << endl;  /*存放转移表的表项*/
	out << "int producerStart=0;" << endl; /*存放产生式开始坐标*/
	out << "int producerLength=0;" << endl; /*存放产生式的长度*/
	/*token读取函数yy_lex(); */
	out << "token=yy_lex();" << endl;
	
	/*接下来就重复作一些事情就完事了*/

	out << "do{" << endl;
	/*第一步，查表，看看移进还是归约*/
	out << "item=yy_next[ yy_base[StackTop(&stateStack)]+token" << endl;

	/*如果是accept状态*/
	out << "if(item==0)" << endl;
	out << "{" << endl;
	out << "prinf(\"accepted!\");"<<endl;
	out << "}" << endl;
    
	/*如果是移进*/
	out << "if(item>0)" << endl;
	out << "{" << endl;
	out << "StackPush(&symbolStack,token);" << endl;
	out << "StackPush(&stateStack,item);" << endl;
	/*token指针指向下一个*/
	out << "if((token=yy_lex())==-1)" << endl;
	out << "break;" << endl;
	out << "}" << endl;

	/*如果是归约*/
	out << "if(item<0)" << endl;
	out << "{" << endl;
	out << "producerStart=index[2*(-item)];" << endl;
	out << "producerLength=index[2*(-item)+1];" << endl;
	out << "int check=1;" << endl; /*check用于检查栈顶元素和产生式右边是否一致*/
	out << "int reverseIndex=producerStart+producerLenght-1;" << endl;/*反向索引*/
	
	out << "int stackTopItem=0;" << endl;
	/*弹出产生式右边个数量的状态和符号*/
	out << "for(int i=reverseIndex;i>producerStart;i--)" << endl;
	out << "{" << endl;
	out << "if(StackPop(&stateStack,&stackTopItem)==0)" << endl;
	out << "{" << endl;
	
	out << "prinf(\"ERROR:STACK EMPTY!\");" << endl;
	out << "check=0;" << endl;
	out << "return;" << endl;
	out << "}" << endl;

	out << "if(StackPop(&symbolStack,&stackTopItem)==0)" << endl;
	out << "{" << endl;
	out << "prinf(\"ERROR:STACK EMPTY!\");" << endl;
	out << "check=0;" << endl;
	out << "return;" << endl;
	out << "}" << endl;

	out << "if(yy_producer_data[i]!=stackTopItem)" << endl;
	out << "{" << endl;
	out << "prinf(\"ERROR:SYNTAX ERROR!\");" << endl;
	out << "check=0;" << endl;
	out << "}" << endl;

	out << "}" << endl;
	out << "if(check==1)" << endl;
	out << "{" << endl;

	/*将产生式左侧的符号压入符号栈以及GOTO(当前栈顶状态，产生式左侧符号)压入状态栈*/
	out << "StackPush(&symbolStack,yy_producer_data[producerStart]);" << endl;
	out << "item=yy_next[ yy_base[StackTop(&stateStack)]+yy_producer_data[producerStart]]" << endl;
	out << "StackPush(&stateSatck,item);" << endl;
	out << "printf(\"%s\\n\",yy_tokens[(-item)])" << endl;
	out << "}" << endl;
	out << "}while(token!=-1);" << endl;
	out << "}" << endl;
	/*
	out << "int getOneToken(int& token)" << endl;
	out << "{" << endl;
	out << "if(tokenLength<=0)" << endl;
	out << "return 0;" << endl;
	out << "token=tokens[tokenIndex];" << endl;
	out << "return 1;" << endl;
	out << "}" << endl;

	out << "int nextToken()" << endl;
	out << "{" << endl;
	out << "if(tokenLength>0)" << endl;
	out << "{" << endl;
	out << "++tokenIndex;" << endl;
	out << "--tokenLength;" << endl;
	out << "return 1;" << endl;
	out << "}" << endl;
	out << "return 0;" << endl;
	out << "}" << endl;
	*/
	out.close();

}

void print_array(string name, int size, void *value, ofstream& out)
{

	int* array_buf = (int*) value;
	out << "static int	" << name << "[" << size << "]" << " =" << endl;
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