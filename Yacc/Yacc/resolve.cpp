#include"stdafx.h"
#include<iostream>
#include<vector>
#include<fstream>
#include"structs.h"
using namespace std;

int resolveYacc(string& fileName, vector<string>&token, vector<string>&left, string& start, vector<statement>&vStms, vector<string>& func)
{
	ifstream in;
	in.open(fileName, ios::in);
	if (!in)
	{
		cout << "ERROR:can't open Yacc file!" << endl;
	}
	string str;
	int i = 0;//表示statement中第几行
	
	/*将所有token纳入token中*/
	in >> str;
	do
	{
		if (str == "%token")
		{
			in >> str;
		}
		token.push_back(str);
		in >> str;
	} while (str!="%left"&&str!="%start"&&str!="%%");

	if (str == "%left")
	{
		do
		{
			if (str == "%left")
			{
				in >> str;
			}
			left.push_back(str);
			in >> str;
		} while (str != "%start"&&str != "%%");
	}
	
	if (str == "%start")
	{
		
		in >> str;
		start=str;
		in >> str;
	}
	if (str == "%%")
	{
		in >> str;
		while (str!= "%%")
		{
			i = 0;
			statement bufStm;
			vector<string> line;
			bufStm.left = str;
			in >> str;
			if (str != ":")
			{
				cout << "ERROR: NO \":\" " << endl;
				return -1;
			}
			in >> str;
			bufStm.line.push_back(line);
			do {

				if (str == "|")
				{
					bufStm.line.push_back(line);
					++i;
					in >> str;
					
				}

				while (str != "|"&&str != ";")
				{
					bufStm.line.at(i).push_back(str);
					in >> str;
				}
				
			} while (str != ";");

			vStms.push_back(bufStm);
			in >> str;
		}
	}

	if (str == "%%")
	{

		while (!in.eof())
		{
			getline(in, str);
			while (str.empty())
			{
				getline(in, str);

			}
			func.push_back(str);

		}
	}

	return 0;

}