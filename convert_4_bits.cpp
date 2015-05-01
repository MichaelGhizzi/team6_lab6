#include <iostream>
#include <string>
#include <bitset>
#include <math.h>
using namespace std;

class convert_4_bits {
private:
	string four_bits_word;
	int discription_value = 0, num_of_words;
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

	int convert_4_bits::get_value()
	{
		cout << "Hex 4 bits: " << four_bits_word << endl;
		signed long long length = std::stoi(four_bits_word, nullptr, 16);
		int bitShift;
		cout << "Length " << length << endl;
		switch (num_of_words)
		{
		case 0: bitShift = (length >> 12) & 4; break;
		case 1: bitShift = (length >> 13); break;
		case 4: bitShift = length & 2; break;
		case 5: bitShift = (length & 127); break;
		case 10: bitShift = length >> 10; break;
		case 15: bitShift = (length >> 1) & 2; break;
		case 22: bitShift = (length >> 2) & 2; break;
		case 32: bitShift = length & 16384; break;
		case 37: bitShift = length >> 14; break;
		case 38: bitShift = (length >> 13) & 2; break;
		case 40: bitShift = (length >> 6) & 2; break;
		case 41: bitShift = (length >> 7) & 128; break;
		}
		cout << "bitShift " << bitShift << endl;
		discription_value = bitShift;
		return discription_value;
	}
};

int main()
{
	int start_word = 5;
	string four_bit = "0106";

	convert_4_bits get(four_bit, start_word);
	cout << "Words " << start_word << " discription_value: " << get.get_value() << endl;
	system("pause");
	return 0;
}
