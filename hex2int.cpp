// Function to convert hex string to numbers
// Example: http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
#include "stringTime.h"  //Need to create header file
#include <sstream> //Stringstreams
#include <iostream>
using namespace std;

unsigned long int hextoInt(string *str, int begOffset, int stringlen, bool wordHighLow)
{
  unsigned long int val;
  stringstream ss;
  string convertString = str->substr(begOffset, stringlen);
  ss << std::hex << convertString;
  ss >> val;
  return val;
}
