#include"stdafx.h"
#include"structs.h"
using namespace std;

int open_and_read_yacc_file(const string& fileName, vector<string> &tokensVec, vector<string>&left, string& start, ProducerVecStr &producerVecStr, vector<string>& funcVec){
	ifstream in;
	in.open(fileName, ios::in);
	if (!in)
	{
		cout << "ERROR: Can't open Yacc file!" << endl;
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
		tokensVec.push_back(str);
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
		int counter = 0;
		while (str!= "%%")
		{
			vector<string> line;
			pair<string, vector<string> > p;
			p.first = str;
			in >> str;
			if (str != ":")
			{
				cout << "ERROR: NO \":\" " << endl;
				return -1;
			}
			in >> str;
			p.second = line;
			do {

				if (str == "|")
				{
					producerVecStr.push_back(p);
					p.second= line;
					++i;
					in >> str;
				}

				while (str != "|"&&str != ";")
				{
					p.second.push_back(str);
					in >> str;
				}
				
			} while (str != ";");
			producerVecStr.push_back(p);
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
			funcVec.push_back(str);

		}
	}

	return 0;

}