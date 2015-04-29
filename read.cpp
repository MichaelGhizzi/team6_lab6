//WIP
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void read()
{
  string line;
  ifstream infile;
  infile.open("test_data.txt");
  
  int count=0; //line numbers

  while(!infile.eof())
    {
      getline(infile,line);
      cout << line;
      count++;
    }

  cout << count << endl;
  
  infile.close();

  return 0;
}


