Output: A1.o A1main.o
	g++ A1.o A1main.o -o output

A1.o: A1.cpp
	g++ -c A1.cpp

A1main.o: A1.cpp
	g++ -c A1main.cpp

clean:
	rm *.o output