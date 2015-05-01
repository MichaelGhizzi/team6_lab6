#include "OUTPUT.h"

// Appends to the output file
void OUTPUT::append(string line)
{
	outFile.open("output.txt", ios::app);
	outFile << line << endl;
	outFile.close();
}
