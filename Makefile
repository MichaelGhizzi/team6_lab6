Prog : main.o
	g++ main.o -o main.exe

main.o : main.cpp
	g++ -c main.cpp

clear:
	rm -f *.o main.exe
