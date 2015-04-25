#include <iostream>
#include <string>
using namespace std;

class convert_4_bits {
private:
	string four_bits_word;
	int discription_value, num_of_words;
public:
	//Default Constructor
	convert_4_bits()
	{
		four_bits_word = "";
		discription_value = 0;
		num_of_words = 0;
	}

	//Overload Constructor
	convert_4_bits (string s, int words)
	{
		four_bits_word = s;
		discription_value = 0;
		num_of_words = words;
	}
	
	int convert_4_bits::get_value ()
	{
		string binary_bit = "", binary_number = "";
		int first_num = 0, second_num = 0, first_sub_num = 0, second_sub_num = 0;
		//get the number of sub string for the 4-bits hex (Ex: word 1 and Data = C405 (hex) => "110"0 0100 0000 0101 (binary) | first)
		//and number and bits require on the table			substring of hex from 0 to 1 | substring of binary from 0 to 3
		switch(num_of_words)
		{
			case 0: first_num = 0; second_num = 1; first_sub_num = 1; second_sub_num = 2; break;
			case 1: first_num = 0; second_num = 1; first_sub_num = 0; second_sub_num = 2; break;
			case 4: first_num = 3; second_num = 4; first_sub_num = 3; second_sub_num = 4; break;
			case 5: first_num = 2; second_num = 4; first_sub_num = 1; second_sub_num = 7; break;
			case 10: first_num = 0; second_num = 2; first_sub_num = 0; second_sub_num = 5; break;
			case 15: first_num = 3; second_num = 4; first_sub_num = 1; second_sub_num = 2; break;
			case 22: first_num = 3; second_num = 4; first_sub_num = 0; second_sub_num = 1; break;
			case 32: first_num = 0; second_num = 4; first_sub_num = 1; second_sub_num = 16; break;
			case 37: first_num = 0; second_num = 1; first_sub_num = 0; second_sub_num = 1; break;
			case 38: first_num = 0; second_num = 1; first_sub_num = 1; second_sub_num = 2; break;
			case 40: first_num = 2; second_num = 3; first_sub_num = 0; second_sub_num = 1; break;
			case 41: first_num = 0; second_num = 2; first_sub_num = 1; second_sub_num = 8; break;
		}
		//plug the number in the sub string
		binary_bit = convert_hex_2_binary(four_bits_word.substr(first_num,second_num));
		binary_number = binary_bit.substr(first_sub_num,second_sub_num);

		//convert binary number to decimal
		int length = binary_number.size(), remainder, base = 1;
		while(length > 0)
		{
			if(binary_number.at(length-1) == '0')
				remainder = 0;
			else
				remainder = 1;
			discription_value += (remainder * base);
			base *= 2;
			length--;
		}
		return discription_value;
	}
	
	//function convert from hex to binary number
	string convert_hex_2_binary(string sub)
	{
		string binary = "";
		for(int i = 0; i<sub.length();i++)
		{
			switch (sub.at(i))
			{
				case '0': binary +="0000"; break;
				case '1': binary +="0001"; break;
				case '2': binary +="0010"; break;
				case '3': binary +="0011"; break;
				case '4': binary +="0100"; break;
				case '5': binary +="0101"; break;
				case '6': binary +="0110"; break;
				case '7': binary +="0111"; break;
				case '8': binary +="1000"; break;
				case '9': binary +="1001"; break;
				case 'A': binary +="1010"; break;
				case 'B': binary +="1011"; break;
				case 'C': binary +="1100"; break;
				case 'D': binary +="1101"; break;
				case 'E': binary +="1110"; break;
				case 'F': binary +="1111"; break;
			}
		}
		return binary;
	}
};