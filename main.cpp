//GROUP_6
//Alec Nghiem - kou.alec@csu.fullerton.edu
//Deshawn Dana - dashwen@csu.fullerton.edu
//Michael Ghizzi - michaelghizzi@csu.fullerton.edu 
//Ronald Dubarry - r_dubarry@csu.fullerton.edu
//Tony Dao - sangdao2014@csu.fullerton.edu

#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std; 

int main ()
{
	//starting clock
	//put in function later? 
	std::clock_t start;
	double duration;
	start = std::clock();
	
	//read function 
	read(); 
	
	int word, line_num;
	int discription_num;
	cout << "Line " << line_num << ": Word " << word;
	
	//table for the word 0

	if (word == 0)
	{
		cout << ": Rec_Ctrl = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: cout << "no recording"; break;
			case 2: cout << "no processing"; break;
			case 3: cout << "processing & recording"; break;
			default: cout << "unknown"; break;
		}
	}

	//table for the word 1
	
	else if (word == 1) 
	{
		cout << ": Cmd_Type = " << discription_num << " (";
		switch (discription_num)
		{
			case 3: cout << "Type A"; break;
			case 4: cout << "Type B"; break;
			case 5: cout << "Type C"; break;
			default: cout << "unknown"; break;
		}
	}

	//table for the word 4

	else if (word == 4) 
	{
		cout << ": Rec_Raw = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: cout << "diable"; break;
			case 1: cout << "enable"; break;
			default: cout << "unknown"; break;
		}
	}
		
	//table for the word 5

	else if (word == 5) 
	{
		cout << ": Cmd_ID = " << discription_num;
	}

	//table for the word 10

	else if (word == 10) 
	{
		cout << ": Num_Responses = " << discription_num 
	}

	//table for the word 15

	else if (word == 15) 
	{
		cout << ": Reset_Enable = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: cout << "diable"; break;
			case 1: cout << "enable"; break;
			default: cout << "unknown"; break;
		}
	}

	//table for the word 22

	else if (word == 22) 
	{
		cout << ": Direction = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: cout << "Right"; break;
			case 1: cout << "Left"; break;
			default: cout << "unknown"; break;
		}
	}

	//table for the word 32

	else if (word == 32) 
	{
		cout << ": Num_Samples = " << discription_num;
	}

	//table for the word 37

	else if (word == 37) 
	{
		cout << ": Parity = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: cout << "even"; break;
			case 1: cout << "odd"; break;
			default: cout << "unknown"; break;
		}
	}

	//table for the word 38

	else if (word == 38) 
	{
		cout << ": Test = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: cout << "disable"; break;
			case 1: cout << "enable"; break;
			default: cout << "unknown"; break;
		}
	}

	//table for the word 40

	else if (word == 40) 
	{
		cout << ": Ctrl_Enable = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: cout << "disable"; break;
			case 1: cout << "enable"; break;
			default: cout << "unknown"; break;
		}
	}

	//table for the word 41

	else if (word == 41) 
	{
		cout << ": Code = " << discription_num;
	}

	cout << ")\n";
	
	//write function 
	write();
	
	//Ended time
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
   	cout << "Time: "<< duration <<'\n';
}

