#pragma once
#include <fstream>
#include <string>
using namespace std;

class OUTPUT
{
public:
// Appends to the output file
	void append(string);	
private:
// output file object to write to file
	ofstream outFile;	
};


// Appends to the output file
void OUTPUT::append(string line)
{
	outFile.open("output.txt", ios::app);
	outFile << line << endl;
	outFile.close();
}
