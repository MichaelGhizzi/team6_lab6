#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#ifndef ConvertBit_H
#define ConvertBit_H

class convert_4_bits {
	private:
		string four_bits_word;
		int num_of_words;
	public:
		//Default Constructor
		convert_4_bits()
		{
			four_bits_word = "";
			num_of_words = 0;
		}

		//Overload Constructor
		convert_4_bits(string s, int words)
		{
			four_bits_word = s;
			num_of_words = words;
		}

		~convert_4_bits()
		{
		}

		int get_value()
		{
			long length;
			    stringstream ss;
			    ss << std::hex << four_bits_word;
			    ss >> length;
			switch (num_of_words)
			{
				case 0: return ((length >> 13) & 3); break;
				case 1: return ((length >> 13)); break;
				case 4: return (length & 1); break;
				case 5: return ((length & 127)); break;
				case 10: return (length >> 11); break;
				case 15: return ((length >> 2) & 1); break;
				case 22: return ((length >> 3) & 1); break;
				case 32: return (length & 16383); break;
				case 37: return (length >> 15); break; 
				case 38: return ((length >> 14) & 1); break; 
				case 40: return ((length >> 7) & 1); break;
				case 41: return ((length >> 8) & 127); break;
				default: return 0; break;
			}
		}
};

#endif
