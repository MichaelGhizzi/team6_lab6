#include <iostream>
#include <string>

using namespace std;

#ifndef Header_H
#define Header_H

class convert_4_bits {
	private:
		string four_bits_word;
		int num_of_words;
	public:
		//Default Constructor
		convert_4_bits::convert_4_bits()
		{
			four_bits_word = "";
			num_of_words = 0;
		}

		//Overload Constructor
		convert_4_bits::convert_4_bits(string s, int words)
		{
			four_bits_word = s;
			num_of_words = words;
		}

		convert_4_bits::~convert_4_bits()
		{
		}

		int convert_4_bits::get_value()
		{
			long length = std::stoi(four_bits_word, nullptr, 16);
			//cout << "+++4Bit: " << four_bits_word << " +++ Length: " << length << endl;
			switch (num_of_words)
			{
			case 0: return ((length >> 13) & 3); break; // 12
			case 1: return ((length >> 13)); break; //12
			case 4: return (length & 1); break;
			case 5: return ((length & 127)); break;
			case 10: return (length >> 11); break; //10
			case 15: return ((length >> 2) & 1); break; //1
			case 22: return ((length >> 3) & 1); break; //2
			case 32: return (length & 16383); break;
			case 37: return (length >> 15); break; // 14
			case 38: return ((length >> 14) & 1); break; // 13
			case 40: return ((length >> 7) & 1); break; // 6
			case 41: return ((length >> 8) & 127); break; //7
			}
		}
};

#endif