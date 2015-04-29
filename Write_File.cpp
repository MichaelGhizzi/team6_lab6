#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
  string line;
  ofstream outfile;
  outfile.open("test_data.txt");
  
  int count=0; //line numbers

  while(!infile.eof())
    {
      getline(infile,line);
      cin >> line; 
      count++;
    }

  cout << count << endl;
  
  
  infile.close();

  return 0;
}
