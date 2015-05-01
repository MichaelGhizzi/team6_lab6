#include "Parse.h"
using namespace std;

//Seperates and store string of Addresses seperated by | to listAddresses
void Parse::splitByPipe(string queue)
{
	string s = queue;
	string delimiter = "|";
	string listAddresses[50];
	size_t pos = 0;
	string token;
	int it = 0;

	int Rec_Ctrl = -1;
	int Cmd_Type = -1;

	int Rec_Raw = -1;
	int Cmd_ID = -1;
	int Num_Responses = -1;
	int Reset_Enable = -1;
	int Direction = -1;
	int Num_Samples = -1;
	int Parity = -1;
	int Test = -1;
	int Ctrl_Enable = -1;
	int Code = -1;
	string wordCount = "";
	string outputstring = "";

	string Rec_Ctrl_strings[4];

	Rec_Ctrl_strings[0] = "no recording";
	Rec_Ctrl_strings[1] = "unknown";
	Rec_Ctrl_strings[2] = "no processing";
	Rec_Ctrl_strings[3] = "processing & recording";

	string Cmd_Type_strings[7];

	Cmd_Type_strings[0] = "unknown";
	Cmd_Type_strings[1] = "unknown";
	Cmd_Type_strings[2] = "unknown";
	Cmd_Type_strings[3] = "unknown";
	Cmd_Type_strings[4] = "Type A";
	Cmd_Type_strings[5] = "Type B";
	Cmd_Type_strings[6] = "Type C";

	string Rec_Raw_strings[3];

	Rec_Raw_strings[0] = "disable";
	Rec_Raw_strings[1] = "enable";
	Rec_Raw_strings[2] = "unkown";


	string Reset_Enable_strings[3];

	Reset_Enable_strings[0] = "disable";
	Reset_Enable_strings[1] = "enable";
	Reset_Enable_strings[2] = "unknown";

	string Direction_strings[3];

	Direction_strings[0] = "Right";
	Direction_strings[1] = "Left";
	Direction_strings[2] = "unknown";

	string Parity_strings[3];

	Parity_strings[0] = "even";
	Parity_strings[1] = "odd";
	Parity_strings[2] = "unknown";

	string Test_strings[3];

	Test_strings[0] = "disable";
	Test_strings[1] = "enable";
	Test_strings[2] = "unknown";

	string Ctrl_Enable_strings[3];

	Ctrl_Enable_strings[0] = "disable";
	Ctrl_Enable_strings[1] = "enable";
	Ctrl_Enable_strings[2] = "unknown";

	OUTPUT appender;

	//if it stays -1 then do not display
	while ((pos = s.find(delimiter)) != std::string::npos) 
	{
		token = s.substr(0, pos);
		if (it == 0)
		{
			outputstring += token;
			outputstring += ": ";
		}
		else if (it == 1)
		{
			wordCount = token;
			outputstring += token;
			outputstring += " words";
			outputstring += "\n";
		}
		else if (it == 2)
		{
			Rec_Ctrl = getbitsValue(token, 13, 14);
			Cmd_Type = getbitsValue(token, 29, 31);
			outputstring += "Word 0: Rec_Ctrl = ";
			outputstring += Rec_Ctrl_strings[Rec_Ctrl];
			outputstring += "\n";
			outputstring += "Word 1: Cmd_Type = ";
			outputstring += Cmd_Type_strings[Cmd_Type];
			outputstring += "\n";
		}
		else if (it == 4) 
		{
			Rec_Raw = getbitsValue(token, 0, 0);
			Cmd_ID = getbitsValue(token, 16, 22);
			outputstring += "Word 4: Rec_Raw = ";
			outputstring += Rec_Raw_strings[Rec_Raw];
			outputstring += "\n";
			outputstring += "Word 5: CMD_ID = ";
			outputstring += to_string(Cmd_ID);
			outputstring += "\n";
		}
		else if (it == 7)
		{
			outputstring += "Word 10: Num_Responses = ";
			Num_Responses = getbitsValue(token, 11, 15);
			outputstring += to_string(Num_Responses);
			outputstring += "\n";
		}
		else if (it == 9)
		{
			outputstring += "Word 15: Reset_Enable = ";
			Reset_Enable = getbitsValue(token, 17, 17);
			outputstring += Reset_Enable_strings[Reset_Enable];
			outputstring += "\n";
		}
		else if (it == 13)
		{
			outputstring += "Word 22: Direction = ";
			Direction = getbitsValue(token, 3, 3);
			outputstring += Direction_strings[Direction];
			outputstring += "\n";
		}
		else if (it == 18)
		{
			outputstring += "Word 32: Num_Samples = ";
			Num_Samples = getbitsValue(token, 0, 14);
			outputstring += to_string(Num_Samples);
			outputstring += "\n";
		}
		else if (it == 20)
		{
			outputstring += "Word 37: Parity = ";
			Parity = getbitsValue(token, 30, 30);
			outputstring += Parity_strings[Parity];
			outputstring += "\n";
		}
		else if (it == 21)
		{
			outputstring += "Word 38: Test = ";
			Test = getbitsValue(token, 14, 14);
			outputstring += Test_strings[Test];
			outputstring += "\n";
		}
		else if (it == 22)
		{
			outputstring += "Word 40: Ctrl_Enable = ";
			Ctrl_Enable = getbitsValue(token, 7, 7);
			Code = getbitsValue(token, 24, 30);
			outputstring += Ctrl_Enable_strings[Ctrl_Enable];
			outputstring += "\n";
			outputstring += "Word 41: Code = ";
			outputstring += to_string(Code);
			outputstring += "\n";
		}
		else {
		}
		listAddresses[it] = (token);
		s.erase(0, pos + delimiter.length());
		it++;
	}
	appender.append(outputstring);
}

Parse::Parse(string strAddresses)
{
	_strAddresses = strAddresses;
	splitByPipe(_strAddresses);
}

string Parse::flipString(string input)
{
	return string(input.rbegin(), input.rend());
}

//Converts the bits into decimal when returned
int Parse::getbitsValue(string bits, int start, int end)
{
	string finalbits = "";
	for (int i = start; i <= end; i++)
    {
		finalbits += bits[i];
	}

	string BinaryInput = finalbits;
	int currentBinaryValue = 1;
	int totalValue = 0;

	for (int i = 0; i <= (BinaryInput.size() - 1); i++) 
	{
		if (BinaryInput[i] == '1')
        {
            totalValue += currentBinaryValue;
        }
		currentBinaryValue *= 2;
	}
	return totalValue;
}

//Alternative to bitmasking
string Parse::getbits(string bits, int start, int end)
{
	string finalbits = "";
	for (int i = start; i <= end; i++)
    {
		finalbits += bits[i];
	}
	return finalbits;
}

Parse::~Parse()
{
}
