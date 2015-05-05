#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>
#include "ConvertBit.h"
#include "DataRate.h"

using namespace std;

int hex_to_int(string);
bool check(int);
string num_to_string (int);
string increasing_word(int, int);
string get_rate_type(double);

int main(int argc, char* argv[])
{ 		
	if(argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <File Name>" << std::endl;
		return 1;
	}

	ofstream write_file;
    fstream open_file;
	
	bool s_to_d = false, d_to_s = false, increase = false, pre_StoD_cycle = true,  pre_DtoS_cycle = true;
	
    int line = 1;
	int start_word = 0, num_of_word = 0; 
	int get_StoD_time = 0, get_DtoS_time = 0, num_StoD_read = 0, num_StoD_write= 0, num_DtoS_read = 0, num_DtoS_write= 0;
	
	double read_StoD_time = 0, write_StoD_time = 0, read_DtoS_time = 0, write_DtoS_time = 0;
	
	string Sample, BgL, RelTime, AbsTime, Transfer, AMXAM, Address, Data, Size, Cycle, junk;
    string left_4bit, right_4bit, result;
	
     
    open_file.open(argv[1]);
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
            Cycle = "Write";
        else
            Cycle = "Read";

		//this divide the data into 2 (Ex:12345678 -> left = 1234, right = 5678)
		if(s_to_d || d_to_s)
		{
			left_4bit = Data.substr(0,4);
			right_4bit = Data.substr(4,8);
		}

		//this is calculate the rate of S-to-D read and write
		if(get_StoD_time > 0)
		{
			calculate_data_rate rate_StoD(RelTime);
			
			if(pre_StoD_cycle == true) //S-to-D write
			{
				num_StoD_write++;				
				write_StoD_time += rate_StoD.get_time();
			}
			else if (pre_StoD_cycle == false)  //S-to-D read
			{
				num_StoD_read++;
				read_StoD_time += rate_StoD.get_time();
			}
			
			get_StoD_time--;
		}

		//this is calculate the rate of D-to-S read and write
		if(get_DtoS_time > 0)
		{
			calculate_data_rate rate_DtoS(RelTime);
			
			if(pre_DtoS_cycle == true) // D-to-S write
			{
				num_DtoS_write++;
				write_DtoS_time += rate_DtoS.get_time();
			}
			else if (pre_DtoS_cycle == false) // D-to-S read
			{
				num_DtoS_read++;
				read_DtoS_time += rate_DtoS.get_time();
			}
			
			get_DtoS_time--;
		}

        //check if address is S to D
        if (Address == "40000810")
        {
			//get the number of word from data
			num_of_word = hex_to_int(Data)/2;	

			//this get the previous cycle to help calculate the rate
			if(Cycle == "Read")
				pre_StoD_cycle = false;
			else
				pre_StoD_cycle = true;

			//this help the calculate data rate
			if(num_of_word == 0)
				get_StoD_time = 1;
			else
				get_StoD_time = (num_of_word / 2 )+1;

			//write the result in Output.txt
			write_file << "Line " << line << ": " << Cycle << " S-to-D command: " << num_of_word << " words" << endl;
			
			//when the number of word on S-to-D command > 0
            if (num_of_word > 0)
            {
                s_to_d = true;
            }
			else
				write_file << endl;
            
        }
		//check if address is D to S
        else if(Address == "40000C18")
        { 
			//get the number of word from data
			num_of_word = hex_to_int(Data)/2;

			//this get the previous cycle to help calculate the rate
			if(Cycle == "Read")
				pre_DtoS_cycle = false;
			else
				pre_DtoS_cycle = true;

			//this help the calculate data rate
			if(num_of_word == 0)
				get_DtoS_time = 1;
			else
				get_DtoS_time = (num_of_word / 2)+1;

			//write the result in Output.txt
			write_file << "Line " << line << ": " << Cycle << " D-to-S command: " << num_of_word << " words" << endl;
            
			//when the number of word on D-to-S command > 0
            if (num_of_word > 0)
            {
                d_to_s = true;
            }
			else
				write_file << endl;
        }
        else if (s_to_d)
        {
			//reduce the number of word by 2 because 1 data contain 2 words
			num_of_word -= 2;

			//this get the previous cycle to help calculate the rate
			if(Cycle == "Read")
				pre_StoD_cycle = false;
			else
				pre_StoD_cycle = true;

			if(num_of_word > 1 && Address == "40000818")
			{
				increase = true;
			}

			//convert hex address to word number
			start_word = (hex_to_int(Address.substr(5,3)) - 2072) / 2;
			
			// check if the word number begin at 0
            if(increase) 
            {
				//print 2 words because data contain 2 words
				if(check(start_word)) // check the word match with the table
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
				//print 2 words as revest
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

			//stop the S-to-D print
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

			//get the previous cycle of D-to-S
			if(Cycle == "Read")
				pre_DtoS_cycle = false;
			else
				pre_DtoS_cycle = true;

			if(num_of_word > 1 && Address == "40000C18")
			{
				increase = true;
			}

			start_word = (hex_to_int(Address.substr(5,3)) - 3104) / 2;
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
			//stop the D-to-S print
            if (num_of_word <= 0)
            {
                d_to_s = false;
                increase = false;
				write_file <<  endl;
            }
        }
        line++;
	
    }
	
	//print data rate
	write_file << "Read S-to-D: " << get_rate_type((num_StoD_read*32) / read_StoD_time) << endl;
	write_file << "Read D-to-S: "<<	get_rate_type((num_DtoS_read*32) / read_DtoS_time) << endl;
	write_file << "Write S-to-D: " << get_rate_type((num_StoD_write*32) / write_StoD_time) << endl;
	write_file << "Write D-to-S: "<< get_rate_type((num_DtoS_write*32) / write_DtoS_time);

	//close 2 file
	open_file.close();
	write_file.close();
	return 0;
}

int hex_to_int(string data)
{
    unsigned int x;
    stringstream ss;
    ss << std::hex << data;
    ss >> x;
    return (x);
}

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
}

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
			case 0: discription += "disable)"; break;
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
			case 0: discription += "disable)"; break;
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
}

string get_rate_type(double rate)
{
	string f;
	ostringstream s;

	if(rate / pow(10,12) > 1)
	{
		s<< fixed<< setprecision(2)<< rate / pow(10,12);
		f += s.str() + " Terabits";
	}
	else if(rate / pow(10,9) > 1)
	{
		s<< fixed<< setprecision(2)<< rate / pow(10,9);
		f += s.str() + " Gigabits";
	}
	else if(rate / pow(10,6) > 1)
	{
		s<<fixed <<setprecision(2)<< rate / pow(10,6);
		f += s.str() + " Megabits";
	}
	else
	{
		s<<setprecision(2)<<fixed<< rate / pow(10,3);
		f += s.str() + " Kilobits";
	}
	f += "/sec";
	return f;
}
