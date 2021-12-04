#CC = clang++ 
CC = g++
LIBS = -lGLEW -lglfw -lGL -lGLU -ldl -lpthread #-DGLEW_STATIC
vertex: vertex.cpp
	$(CC) -o out.o vertex.cpp $(LIBS)  

run:
	./out.o
