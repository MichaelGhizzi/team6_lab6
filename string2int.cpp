//This functions converts a string to an integer
//Referenced from: http://www.cplusplus.com/reference/string/stoi/
//Another example we could use http://www.cplusplus.com/forum/general/13135/
#include "string2int.h"
using namespace std;

int string2int(string *str, int begOffset, int stringLen)
{
  int val;
  string convertString = str->substr(begOffset, stringLen);
  val = stoi(convertString);
  return val;
}
