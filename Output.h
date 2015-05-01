#pragma once
#include <fstream>
#include <string>
using namespace std;

class OUTPUT
{
public:
	void append(string);	// Appends to the output file
private:
	ofstream outFile;		// output file object to write to file
};
