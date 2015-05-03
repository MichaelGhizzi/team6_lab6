#ifndef FILES
#define FILES
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//The ROW class holds the individual row information when
//reading the file
//An object of the class represents one row
//A string variable represents each column in one row

class ROW
{
public:
	ROW(){}
	string Col_Sample;
	string Col_BgL;
	string Col_RelTime;
	string Col_AbsTime;
	string Col_Transfer;
	string Col_AM_XAM;
	string Col_Address;
	string Col_Data;
	string Col_Size;
	string Col_Cycle;
	string Col_Status;
	string Col_Iack;
	string Col_Fail;
	string Col_IRQ;
};
#endif
