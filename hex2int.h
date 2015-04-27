//hex2int.h
//Function takes a string and returns an integer of hex digits
//Uses offsets to show where the string should beg and end

#include <string>
#ifndef __HEX2INT__
#define __HEX2INT 
using namespace std;
unsigned long int hex2int(string *str, int begOffset, int endOffset, bool wordHighLow);
#endif
