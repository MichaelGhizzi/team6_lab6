#include <iostream>
#include <string>
#include <sstream>
#include <math.h> 
#include <stdlib.h>

using namespace std;

#ifndef DataRate_H
#define DataRate_H

class calculate_data_rate {
	private:
		string RelTime;
	public:
		//Default Constructor
		calculate_data_rate()
		{
			RelTime = "";
		}

		//Overload Constructor
		calculate_data_rate(string time)
		{
			RelTime = time;
		}

		~calculate_data_rate()
		{
		}
		
		double get_time ()
		{
			int length = RelTime.length();
			string time_type = RelTime.substr(length-2, length);

			if (time_type == "ns") // ns in nanosecond
			{
				return (hex_to_int(RelTime.substr(0, length-2)) * pow(10,-9));
			}
			else if (time_type == "us") // us in microsecond
			{
				return (hex_to_int(RelTime.substr(0, length-2)) * pow(10,-6));
			}
			else // ms is millisecond
			{
				return (hex_to_int(RelTime.substr(0, length-2)) * pow(10,-3));
			}
		}

		double hex_to_int(string hex)
		{
			double f; 
			istringstream(hex) >> f; 
			return (f);
		} 
};

#endif