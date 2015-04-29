#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
using namespace std;

int main()
{
    clock_t start;
    start = clock();
    double duration;
    
    fstream TestData;
    string Sample, BgL, RelTime, AbsTime, Transfer, AMXAM, Address, Data, Size, Cycle;
    string junk;
    int counter = 2;
    
    TestData.open("test_data.txt");
    getline(TestData, junk);
    
    while (!TestData.eof())
    {
        TestData >> Sample >> BgL >> RelTime >> AbsTime >> Transfer >> AMXAM >> Address >> Data >> Size >> Cycle;
        getline(TestData, junk);
        //cin.ignore();
        if (Address == "40000810" || Address == "40000C18")
            cout << "Line: " << counter << "    " << Address << "    " << Data << "    " << Size << "    " << Cycle << endl;
        counter++;
    }
    
    TestData.close();
    cout << "Done" << endl;
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Time: " << duration << endl;
    
    return 0;
}
