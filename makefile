p01_chainCC=g++ -std=c++20
CFLAGS=-O0 -g -Wall
DEPS = matriz_distancia.h nodo.h
OBJ = main.o

SRC = './src/'

compilar:
	g++ $(CFLAGS) $(SRC)*.cc -o p02_laberinto


%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: chain

busqueda: main.o
	g++ -o p02_laberinto main.cc nodo.cc matriz_lab.cc

clean:
	rm -f *.o
