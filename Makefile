Prog : main.o convert_4_bits.o
	g++ main.o -o main.exe

convert_4_bits.o:
	g++ -c convert_4_bits.cpp

main.o : main.cpp
	g++ -c main.cpp

clear:
	rm -f *.o main.exe
