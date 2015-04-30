//
//  main.cpp
//  cpsc254parseaddress
//
//  Created by Deshawn Dana on 4/28/15.
//  Copyright (c) 2015 Deshawn Dana. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Record
{
    string Address, Data, Size, Cycle;
    int Line;
};

bool checkLengthSD(Record parsed_info);
bool checkLengthDS(Record parsed_info);
int getWord(Record parsed_info);

int main()
{
    
    fstream f;
    int line = 1;
    Record parsed_info;
    string address, data, test_line, size, cycle;
    
    f.open("sample.txt", ios::in);
    //skips first line b/c of title
    
    f.ignore(500,'\n');
    
    //since skips first line, make line start at 2
    line++;
    
    
    while(f.good())
    {
        //cout << "line # : " << line << endl;

        getline(f, test_line);

        //cout << test_line << endl << endl;
        
        //use substr to parse portion of a string
        parsed_info.Address = test_line.substr(81, 8);
        parsed_info.Data = test_line.substr(98, 8);
        parsed_info.Size = test_line.substr(110, 3);
        parsed_info.Cycle = test_line.substr(117, 2);
        
        //check length for S-D
        if (checkLengthSD(parsed_info))
        {
            
            //get Data amount at address
            
            
            cout << "Line " << line << " ";
            
            if(parsed_info.Cycle == "Wr")
            {
                parsed_info.Cycle = "Write";
            }
            else if(parsed_info.Cycle == "Rd")
            {
                parsed_info.Cycle = "Read";
            }
            
            cout << parsed_info.Address << " " << parsed_info.Data << " " << parsed_info.Size << " " << parsed_info.Cycle << endl;
            
        }
        else if(checkLengthDS(parsed_info))
        {
            
            cout << "Line " << line << " ";
            
            
            //check Data amount at address
            
            
            
            if(parsed_info.Cycle == "Wr")
            {
                parsed_info.Cycle = "Write";
            }
            else if(parsed_info.Cycle == "Rd")
            {
                parsed_info.Cycle = "Read";
            }
        
            
            cout << parsed_info.Address << " " << parsed_info.Data << " " << parsed_info.Size << " " << parsed_info.Cycle << endl;
            
        }
        
        
        
        line++;
        
    }

    return 0;
}
bool checkLengthSD(Record parsed_info)
{
    if(parsed_info.Address == "40000810")
    {
        return true;
    }
    
    return false;
}
    
bool checkLengthDS(Record parsed_info)
{
    if(parsed_info.Address == "40000C18")
    {
        return true;
    }
    
    return false;
        
}
/*
int getWords(Record parsed_info);
{
    int data;
    if(parsed_info.Data == "00000000")
    {
        data = 0;
        return data
    }
    else
        return
}
 */