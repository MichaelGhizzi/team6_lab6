#include <iostream>

int main ()
{
	int word, line_num;

	int discription_num;
	std::cout << "Line " << line_num << ": Word " << word;
	
	//table for the word 0

	if (word == 0)
	{
		std::cout << ": Rec_Ctrl = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: std::cout << "no recording"; break;
			case 2: std::cout << "no processing"; break;
			case 3: std::cout << "processing & recording"; break;
			default: std::cout << "unknown"; break;
		}
	}

	//table for the word 1
	
	else if (word == 1) 
	{
		std::cout << ": Cmd_Type = " << discription_num << " (";
		switch (discription_num)
		{
			case 3: std::cout << "Type A"; break;
			case 4: std::cout << "Type B"; break;
			case 5: std::cout << "Type C"; break;
			default: std::cout << "unknown"; break;
		}
	}

	//table for the word 4

	else if (word == 4) 
	{
		std::cout << ": Rec_Raw = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: std::cout << "diable"; break;
			case 1: std::cout << "enable"; break;
			default: std::cout << "unknown"; break;
		}
	}
		
	//table for the word 5

	else if (word == 5) 
	{
		std::cout << ": Cmd_ID = " << discription_num;
	}

	//table for the word 10

	else if (word == 10) 
	{
		std::cout << ": Num_Responses = " << discription_num 
	}

	//table for the word 15

	else if (word == 15) 
	{
		std::cout << ": Reset_Enable = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: std::cout << "diable"; break;
			case 1: std::cout << "enable"; break;
			default: std::cout << "unknown"; break;
		}
	}

	//table for the word 22

	else if (word == 22) 
	{
		std::cout << ": Direction = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: std::cout << "Right"; break;
			case 1: std::cout << "Left"; break;
			default: std::cout << "unknown"; break;
		}
	}

	//table for the word 32

	else if (word == 32) 
	{
		std::cout << ": Num_Samples = " << discription_num;
	}

	//table for the word 37

	else if (word == 37) 
	{
		std::cout << ": Parity = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: std::cout << "even"; break;
			case 1: std::cout << "odd"; break;
			default: std::cout << "unknown"; break;
		}
	}

	//table for the word 38

	else if (word == 38) 
	{
		std::cout << ": Test = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: std::cout << "disable"; break;
			case 1: std::cout << "enable"; break;
			default: std::cout << "unknown"; break;
		}
	}

	//table for the word 40

	else if (word == 40) 
	{
		std::cout << ": Ctrl_Enable = " << discription_num << " (";
		switch (discription_num)
		{
			case 0: std::cout << "disable"; break;
			case 1: std::cout << "enable"; break;
			default: std::cout << "unknown"; break;
		}
	}

	//table for the word 41

	else if (word == 41) 
	{
		std::cout << ": Code = " << discription_num;
	}

	std::cout << ")\n";
}

