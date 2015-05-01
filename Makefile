main.o : main.cpp
	g++ -c main.cpp
	
clean:
	rm -f *.o main.exe
