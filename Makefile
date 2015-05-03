default : main.exe

main.o : main.cpp ConvertBit.h DataRate.h
	g++ -c main.cpp

main.exe: main.o
	g++ main.o -o main.exe

clear:
	rm -f *.o main.exe Output.txt
