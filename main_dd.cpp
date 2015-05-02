
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include "Header.h"
//#include "Write.h"

using namespace std;

int convertHexToInt(string data)
{
    unsigned int x;
    stringstream ss;
    ss << std::hex << data;
    ss >> x;
    return (x);
};

string num_to_string (int num)
{
	ostringstream ss;
	ss << num;
	return ss.str();
}

bool check(int word)
{
	switch(word)
	{
		case 0: return true; break;
		case 1: return true; break;
		case 4: return true; break;
		case 5: return true; break;
		case 10: return true; break;
		case 15: return true; break;
		case 22: return true; break;
		case 32: return true; break;
		case 37: return true; break;
		case 38: return true; break;
		case 40: return true; break;
		case 41: return true; break;
		default: return false; break;
	}
};

string increasing_word(int word, int discription_num)
{
	string discription = "";
	//table for the word 0
	discription += num_to_string(word);
	if (word == 0)
	{
		 discription += ": Rec_Ctrl = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 0: discription += "no recording)"; break;
			case 2: discription += "no processing)"; break;
			case 3: discription += "processing & recording)"; break;
			default: discription += "unknown)"; break;
		}
	}
	//table for the word 1	
	else if (word == 1) 
	{
		discription += ": Cmd_Type = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 4: discription += "Type A)"; break;
			case 5: discription += "Type B)"; break;
			case 6: discription += "Type C)"; break;
			default: discription += "unknown)"; break;
		}
	}

	//table for the word 4

	else if (word == 4) 
	{
		discription += ": Rec_Raw = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 0: discription += "diable)"; break;
			case 1: discription += "enable)"; break;
			default: discription += "unknown)"; break;
		}
	}
		
	//table for the word 5

	else if (word == 5) 
	{
		discription += ": Cmd_ID = " + num_to_string(discription_num);
	}

	//table for the word 10

	else if (word == 10) 
	{
		discription += ": Num_Responses = " + num_to_string(discription_num);
	}

	//table for the word 15

	else if (word == 15) 
	{
		discription += ": Reset_Enable = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 0: discription += "diable)"; break;
			case 1: discription += "enable)"; break;
			default: discription += "unknown)"; break;
		}
	}

	//table for the word 22

	else if (word == 22) 
	{
		discription += ": Direction = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 0: discription += "Right)"; break;
			case 1: discription += "Left)"; break;
			default: discription += "unknown)"; break;
		}
	}

	//table for the word 32

	else if (word == 32) 
	{
		discription += ": Num_Samples = " + num_to_string(discription_num);
	}

	//table for the word 37

	else if (word == 37) 
	{
		discription += ": Parity = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 0: discription += "even)"; break;
			case 1: discription += "odd)"; break;
			default: discription += "unknown)"; break;
		}
	}

	//table for the word 38

	else if (word == 38) 
	{
		discription += ": Test = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 0: discription += "disable)"; break;
			case 1: discription += "enable)"; break;
			default: discription += "unknown)"; break;
		}
	}

	//table for the word 40

	else if (word == 40) 
	{
		discription += ": Ctrl_Enable = " + num_to_string(discription_num) + " (";
		switch (discription_num)
		{
			case 0: discription += "disable)"; break;
			case 1: discription += "enable)"; break;
			default: discription += "unknown)"; break;
		}
	}

	//table for the word 41

	else if (word == 41) 
	{
		discription += ": Code = " + num_to_string(discription_num);
	}
	discription += "\n";
	return discription;
};

int main(int argc, char* argv[])
{ 	
	std::clock_t start;
	double duration;
	start = std::clock();
	if(argc < 2 || argc > 2)
	{
		std::cerr << "Usage: " << argv[0] << " <File Name>" << std::endl;
		return 1;
	}

	ofstream write_file;
    fstream open_file;
    int line = 1;
	string Sample, BgL, RelTime, AbsTime, Transfer, AMXAM, Address, Data, Size, Cycle, junk;
    string left_4bit, right_4bit, result;
    int start_word = 0, num_of_word = 0;    
    bool s_to_d = false, d_to_s = false, increase = false;
    
    open_file.open("test_data.txt");
	write_file.open ("Output.txt");
  
    //skips first line b/c of title    
    open_file.ignore(500,'\n');
    
    //since skips first line, make line start at 2
    line++;    
    
    while(open_file.good())
    {
        //cout << "line # : " << line << endl;
		open_file >> Sample >> BgL >> RelTime >> AbsTime >> Transfer >> AMXAM >> Address >> Data >> Size >> Cycle;
        getline(open_file, junk);

		//turn wr to write and rd to read
		if(Cycle == "Wr")
        {
            Cycle = "Write";
        }
        else
        {
            Cycle = "Read";
        }

		if(s_to_d || d_to_s)
		{
			left_4bit = Data.substr(0,4);
			right_4bit = Data.substr(4,8);
		}

        //check length for S-D
        if (Address == "40000810")
        {
			num_of_word = convertHexToInt(Data)/2;
			//write the result in Output.txt
			write_file << "Line " << line << ": " << Cycle << " S-D command " << num_of_word << " words" << endl;
            if (num_of_word > 0)
            {
                s_to_d = true;
            }
			else
				write_file << endl;
            
        }
        else if(Address == "40000C18")
        { 
			num_of_word = convertHexToInt(Data)/2;
			write_file << "Line " << line << ": " << Cycle << " D-S command " << num_of_word << " words" << endl;
            
            if (num_of_word > 0)
            {
                d_to_s = true;
            }
			else
				write_file << endl;
        }
        else if (s_to_d)
        {
			num_of_word -= 2;
			if(num_of_word > 1 && Address == "40000818")
			{
				increase = true;
			}
			start_word = (convertHexToInt(Address.substr(5,3)) - 2072) / 2;
            if(increase)
            {
				if(check(start_word))
				{
				convert_4_bits StoD_left_4(left_4bit, start_word);
				result = increasing_word(start_word,StoD_left_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
				if(check(start_word+1))
				{
				convert_4_bits StoD_right_4(right_4bit, start_word+1);
				result = increasing_word(start_word+1,StoD_right_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
            }
            else
            {
				if(check(start_word+1))
				{
				convert_4_bits StoD_right_4(right_4bit, start_word+1);
				result = increasing_word(start_word+1,StoD_right_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
				if(check(start_word))
				{
				convert_4_bits StoD_left_4(left_4bit, start_word);
				result = increasing_word(start_word,StoD_left_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
            }            

            if (num_of_word <= 0)
            {
                s_to_d = false;
                increase = false;
				write_file << endl;
            }
        }
        else if (d_to_s)
        {
			num_of_word -= 2;
			if(num_of_word > 1 && Address == "40000C18")
			{
				increase = true;
			}

			start_word = (convertHexToInt(Address.substr(5,3)) - 3104) / 2;
            if(increase)
            {
				if(check(start_word))
				{
				convert_4_bits DtoS_left_4(left_4bit, start_word);
				result = increasing_word(start_word,DtoS_left_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
				if(check(start_word+1))
				{
				convert_4_bits DtoS_right_4(right_4bit, start_word+1);
				result = increasing_word(start_word+1,DtoS_right_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
            }
            else
            {
				if(check(start_word+1))
				{
				convert_4_bits DtoS_right_4(right_4bit, start_word+1);
				result = increasing_word(start_word+1,DtoS_right_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
				if(check(start_word))
				{
				convert_4_bits DtoS_left_4(left_4bit, start_word);
				result = increasing_word(start_word,DtoS_left_4.get_value());
				write_file << "Line " << line << ": Word " << result;
				}
            }

            if (num_of_word <= 0)
            {
                d_to_s = false;
                increase = false;
				write_file <<  endl;
            }
        }
        line++;
/*
        if(line > 1100)
        {
            break;
        }
*/
    }
	open_file.close();
	write_file.close();

	//Ended time
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
   	cout << "Time: "<< duration <<'\n';
	//system("pause");
	return 0;
}
