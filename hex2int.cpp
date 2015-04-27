//Function converts hex string to numbers
//Example of function taken from:
//http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
#include "string2timing.h"
#include <sstream>
#include <iostream>
using namespace std;

unsigned long int hex2int(string* str, int startOffset, int lenOfString, bool wordHighLow)
{
  unsigned long int x;
  stringstream ss;
  string convertString = str->substr(startOffset, lenOfString);
  ss << std::hex << convertString;
  ss >> x;
  return x;
}
