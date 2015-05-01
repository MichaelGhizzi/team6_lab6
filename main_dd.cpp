
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Header.h"

using namespace std;

struct Record
{
    string Address, Data, Size, Cycle;
    int Line;
};

bool checkLengthSD(Record parsed_info);
bool checkLengthDS(Record parsed_info);
int convertHexToInt(Record parsed_info);


int main()
{    
    fstream file;
    int line = 1;
    Record parsed_info;
    string test_line;
	string Sample, BgL, RelTime, AbsTime, Transfer, AMXAM, Address, Data, Size, Cycle;
    
    string left_4bit, right_4bit;
    
    int start_word = 0, num_of_word = 0;
    
    bool s_to_d = false;
    bool d_to_s = false;
    bool increase = false;
    
    file.open("test_data.txt", ios::in);
    //skips first line b/c of title
    
    file.ignore(500,'\n');
    
    //since skips first line, make line start at 2
    line++;    
    
    while(file.good())
    {
        //cout << "line # : " << line << endl;
		file >> Sample >> BgL >> RelTime >> AbsTime >> Transfer >> AMXAM >> Address >> Data >> Size >> Cycle;
        getline(file, test_line);
		test_line = "";
        //cout << test_line << endl << endl;
        
        //use substr to parse portion of a string
		/*parsed_info.Address = Address;
        parsed_info.Data = Data;
        parsed_info.Size = Size;
        parsed_info.Cycle = Cycle;*/
		//cout << "Line " << line << ":[" <<AbsTime << "]["  << Transfer << "]["  << AMXAM << "]["  << Address << "]["  << Data << "]["  << Cycle << "][" << test_line << "]"<< endl;
        //check length for S-D
        if (Address == "40000810")
        {
            std::cout << "Line " << line << ": ";
            
            if(Cycle == "Wr")
            {
                Cycle = "Write";
            }
            else
            {
                Cycle = "Read";
            }
            
			num_of_word = (stoi(Data, nullptr, 16))/2;
            
            std::cout << Cycle << " S-D command " << num_of_word << " words" << endl;
                        
            if (num_of_word > 0)
            {
                s_to_d = true;
            }
			else
				cout << endl;
            
        }
        else if(Address == "40000C18")
        { 
            std::cout << "Line " << line << ": ";            
            
            //check Data amount at address 
			if(Cycle == "Wr")
            {
                Cycle = "Write";
            }
            else
            {
                Cycle = "Read";
            }
            
			num_of_word = (stoi(Data, nullptr, 16))/ 2;
            
            std::cout << Cycle << " D-S command " << num_of_word << " words" << endl;
            
            if (num_of_word > 0)
            {
                d_to_s = true;
            }
			else
				cout << endl;
        }
        else if (s_to_d)
        {
			left_4bit = Data.substr(0,4);
			right_4bit = Data.substr(4,8);
			num_of_word -= 2;
			if(num_of_word > 1 && Address == "40000818")
			{
				increase = true;
			}
			start_word = stoi(Address.substr(5,3), nullptr, 16) - 2072;
			start_word /= 2;
            if(increase)
            {
				if(start_word == 0 || start_word == 1 || start_word == 4 || start_word == 5 || start_word == 10 || start_word == 15 || start_word == 22 || start_word == 32 || start_word == 37 || start_word == 38 || start_word == 40 || start_word == 41)
				{
				convert_4_bits StoD_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << StoD_left_4.get_value() << endl;
				}
				if(start_word+1 == 0 || start_word+1 == 1 || start_word+1 == 4 || start_word+1 == 5 || start_word+1 == 10 || start_word+1 == 15 || start_word+1 == 22 || start_word+1 == 32 || start_word+1 == 37 || start_word+1 == 38 || start_word+1 == 40 || start_word+1 == 41)
				{
				convert_4_bits StoD_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << StoD_right_4.get_value() << endl;
				}
            }
            else
            {
				if(start_word+1 == 0 || start_word+1 == 1 || start_word+1 == 4 || start_word+1 == 5 || start_word+1 == 10 || start_word+1 == 15 || start_word+1 == 22 || start_word+1 == 32 || start_word+1 == 37 || start_word+1 == 38 || start_word+1 == 40 || start_word+1 == 41)
				{
				convert_4_bits StoD_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << StoD_right_4.get_value() << endl;
				}
				if(start_word == 0 || start_word == 1 || start_word == 4 || start_word == 5 || start_word == 10 || start_word == 15 || start_word == 22 || start_word == 32 || start_word == 37 || start_word == 38 || start_word == 40 || start_word == 41)
				{
				convert_4_bits StoD_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << StoD_left_4.get_value() << endl;
				}
            }            

            if (num_of_word <= 0)
            {
                s_to_d = false;
                increase = false;
				cout << endl;
            }
        }
        else if (d_to_s)
        {
			left_4bit = Data.substr(0,4);
			right_4bit = Data.substr(4,8);
			num_of_word -= 2;
			if(num_of_word > 1 && Address == "40000C18")
			{
				increase = true;
			}

			start_word = stoi(Address.substr(5,3), nullptr, 16) - 3104;
			start_word /= 2;
            if(increase)
            {
				if(start_word == 0 || start_word == 1 || start_word == 4 || start_word == 5 || start_word == 10 || start_word == 15 || start_word == 22 || start_word == 32 || start_word == 37 || start_word == 38 || start_word == 40 || start_word == 41)
				{
				convert_4_bits DtoS_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << DtoS_left_4.get_value() << endl;
				}
				if(start_word+1 == 0 || start_word+1 == 1 || start_word+1 == 4 || start_word+1 == 5 || start_word+1 == 10 || start_word+1 == 15 || start_word+1 == 22 || start_word+1 == 32 || start_word+1 == 37 || start_word+1 == 38 || start_word+1 == 40 || start_word+1 == 41)
				{
				convert_4_bits DtoS_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << DtoS_right_4.get_value() << endl;
				}
            }
            else
            {
				if(start_word+1 == 0 || start_word+1 == 1 || start_word+1 == 4 || start_word+1 == 5 || start_word+1 == 10 || start_word+1 == 15 || start_word+1 == 22 || start_word+1 == 32 || start_word+1 == 37 || start_word+1 == 38 || start_word+1 == 40 || start_word+1 == 41)
				{
				convert_4_bits DtoS_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << DtoS_right_4.get_value() << endl;
				}
				if(start_word == 0 || start_word == 1 || start_word == 4 || start_word == 5 || start_word == 10 || start_word == 15 || start_word == 22 || start_word == 32 || start_word == 37 || start_word == 38 || start_word == 40 || start_word == 41)
				{
				convert_4_bits DtoS_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << DtoS_left_4.get_value() << endl;
				}
            }

            if (num_of_word <= 0)
            {
                d_to_s = false;
                increase = false;
				cout << endl;
            }
        }
        line++;
        if(line > 1100)
        {
            break;
        }

    }
	file.close();
	std::system("pause");
	return 0;
}


int convertHexToInt(string data)
{
    //code sourced from stackoverflow    
    unsigned int x;
    stringstream ss;

    ss << std::hex << data;
    ss >> x;
    
    //return x/2 for word count
    return (x/2);
}