CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic
OBJ = Sierpinski.o
DEPS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE = Sierpinski

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(EXE)
