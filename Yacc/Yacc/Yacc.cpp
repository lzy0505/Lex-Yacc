// Yacc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include"structs.h"
#include<vector>
using namespace std;
int resolveYacc(string& fileName, vector<string>&token, vector<string>&left, string& start, vector<statement>&vStms, vector<string>& func);

/*公元2018年5月4日，中国冒险家赵千锋第一次登上Yacc大陆，这是他的一小步，却是人类的一大步*/
void zhaosTest();

int main()
{
	
	zhaosTest();
    return 0;
}
void zhaosTest()
{
	string fileName("yacc.y");
	vector<string>token;
	vector<string>left;
	string start;
	vector<statement>vStms;
	vector<string> func;
	resolveYacc(fileName, token, left, start, vStms, func);

	/*test output*/
	for (int i=0; i < token.size(); i++)
	{
		cout << token[i] << "    ";
	}
	for (int i = 0; i < left.size(); i++)
	{

		cout << left[i] << endl;
	}

	cout << endl;
	cout <<"START:"<<start<<endl;
	cout << endl;

	for (int i = 0; i < vStms.size(); i++)
	{
		cout << vStms[i].left << endl;
		for (int j = 0; j < vStms[i].line.size(); j++)
		{

			for (int k = 0; k < vStms[i].line[j].size(); k++)
			{

				cout << vStms[i].line[j].at(k) << "   " ;

			}

			cout << endl;
		}
		cout << endl;
	}
	
	for (int i = 0; i < func.size(); i++)
	{
		cout << func[i] << endl;
	}
	


}
