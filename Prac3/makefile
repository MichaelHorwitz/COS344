#add all the files that you need to the files makefile variable below as a space seperated list
files = Vector.cpp Matrix.cpp shapes.cpp

main: main.cpp glad.c
	g++ -g shader.cpp $(files) main.cpp glad.c -g -lglfw -pthread -lGLEW -ldl -lGL -o main

clean:
	rm -f *.o main

run: main
	./main

all:
	make clean
	make
	make run