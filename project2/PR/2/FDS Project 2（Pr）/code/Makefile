CC = gcc
TARGET = bst_program
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
# The source files should include the header file bst.h

CFLAGS = -Wall -Wextra -std=c99 -O2

all: $(TARGET) # Default target to build the program

$(TARGET): $(OBJ)
	$(CC) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(TARGET)

# To build the project, run `make` in the terminal.
# To clean up the object files and the executable, run `make clean`.
# To run the program, execute `./bst_program` in the terminal after building.