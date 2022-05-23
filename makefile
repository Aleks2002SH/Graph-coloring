main:
	echo "Main target"
compile: main.cpp
	g++ -c GraphColoring.cpp
	g++ GraphColoring.o -o result
clean:
	rm *.o
workresult:
	./result
