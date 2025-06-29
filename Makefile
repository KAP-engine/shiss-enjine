CC=g++
CFLAGS=
CFILES=src/main.cpp src/utils.cpp src/evaluation.cpp src/console.cpp src/display.cpp src/chessboard.cpp src/movegen.cpp src/move.cpp
OBJECTS=src/main.o src/utils.o src/evaluation.o src/console.o src/display.o src/chessboard.o src/movegen.o src/move.o
BINARY=bin

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -fr $(BINARY) $(OBJECTS)
