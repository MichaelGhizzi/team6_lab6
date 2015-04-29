//Write function
//Going to write already parsed data to text file
//not complete 

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void write()    //shouldnt be main 
{
  string line;
  ofstream outfile;
  outfile.open("test_data.txt");
  
  outFile >> count; 

  while(!outfile.eof())
    {
      getline(infile,line);
      outFile >> line; 
    }
  infile.close();

  return 0;
}
