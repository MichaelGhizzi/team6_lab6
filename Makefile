default : main.exe

main.o : main_dd.cpp Header.h
	g++ -c main_dd.cpp

main.exe: main.o
	g++ main.o -o main.exe

clear:
	rm -f *.o main.exe Output.txt
