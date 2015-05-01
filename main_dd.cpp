
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

        //cout << test_line << endl << endl;
        
        //use substr to parse portion of a string
		parsed_info.Address = Address;
        parsed_info.Data = Data;
        parsed_info.Size = Size;
        parsed_info.Cycle = Cycle;

		left_4bit = parsed_info.Data.substr(0,4);
        right_4bit = parsed_info.Data.substr(4,8);

        //check length for S-D
        if (parsed_info.Address == "40000810")
        {
            std::cout << "Line " << line << ": ";
            
            if(parsed_info.Cycle == "Wr")
            {
                parsed_info.Cycle = "Write";
            }
            else
            {
                parsed_info.Cycle = "Read";
            }
            
            num_of_word = convertHexToInt(parsed_info);
            
            std::cout << parsed_info.Cycle << " S-D command " << convertHexToInt(parsed_info) << " words" << endl;
                        
            if (num_of_word > 0)
            {
                s_to_d = true;
            }
			else
				cout << endl;
            
        }
        else if(parsed_info.Address == "40000C18")
        {            
            std::cout << "Line " << line << ": ";            
            
            //check Data amount at address 
			if(parsed_info.Cycle == "Wr")
            {
                parsed_info.Cycle = "Write";
            }
            else
            {
                parsed_info.Cycle = "Read";
            }
            
            num_of_word = convertHexToInt(parsed_info);
            
            std::cout << parsed_info.Cycle << " D-S command " << convertHexToInt(parsed_info) << " words" << endl;
            
            if (num_of_word > 0)
            {
                d_to_s = true;
            }
			else
				cout << endl;
        }
        else if (s_to_d)
        {
			num_of_word -= 2;
			if(num_of_word > 1 && parsed_info.Address == "40000818")
			{
				increase = true;
			}
			start_word = stoi(parsed_info.Address.substr(5,3), nullptr, 16) - 2072;
			start_word /= 2;
            if(increase)
            {
				convert_4_bits StoD_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << StoD_left_4.get_value() << endl;
				convert_4_bits StoD_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << StoD_right_4.get_value() << endl;
            }
            else
            {
				convert_4_bits StoD_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << StoD_right_4.get_value() << endl;
				convert_4_bits StoD_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << StoD_left_4.get_value() << endl;
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
			num_of_word -= 2;
			if(num_of_word > 1 && parsed_info.Address == "40000C18")
			{
				increase = true;
			}

			start_word = stoi(parsed_info.Address.substr(5,3), nullptr, 16) - 3104;
			start_word /= 2;
            if(increase)
            {
				convert_4_bits DtoS_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << DtoS_left_4.get_value() << endl;
				convert_4_bits DtoS_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << DtoS_right_4.get_value() << endl;
            }
            else
            {
				convert_4_bits DtoS_right_4(right_4bit, start_word+1);
                std::cout << "Line " << line << ": Word " << start_word+1 << ": " << DtoS_right_4.get_value() << endl;
				convert_4_bits DtoS_left_4(left_4bit, start_word);
                std::cout << "Line " << line << ": Word " << start_word << ": " << DtoS_left_4.get_value() << endl;
            }

            if (num_of_word <= 0)
            {
                s_to_d = false;
                increase = false;
				cout << endl;
            }
        }
        line++;
        if(line > 800)
        {
            break;
        }

    }
	file.close();
	std::system("pause");
	return 0;
}


int convertHexToInt(Record parsed_info)
{
    //code sourced from stackoverflow    
    unsigned int x;
    stringstream ss;

    ss << std::hex << parsed_info.Data;
    ss >> x;
    
    //return x/2 for word count
    return (x/2);
}