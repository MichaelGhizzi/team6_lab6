#ifndef PARSE
#define PARSE

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "OUTPUT.cpp"		// To use it for the output txt file
using namespace std;

class Parse
{
public:
	int getbitsValue(string, int, int);
	string listAddresses[50];
	Parse(string);
	~Parse();
	void splitByPipe(string);
	string flipString(string);
	string getbits(string, int, int);

	int Rec_Ctrl;
	int Cmd_Type;
	int Rec_Raw;
	int Cmd_ID;
	int Num_Responses;
	int Reset_Enable;
	int Direction;
	int Num_Samples;
	int Parity;
	int Test;
	int Ctrl_Enable;
	int Code;
private:
	string _strAddresses;
};
#endif
