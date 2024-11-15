CC=g++
CFLAGS=
CFILES=main.cpp utils.cpp evaluation.cpp console.cpp display.cpp
OBJECTS=main.o utils.o evaluation.o console.o display.o
BINARY=bin

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -fr $(BINARY) $(OBJECTS)
