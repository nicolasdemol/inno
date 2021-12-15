CC=gcc
BIN_DIR=./bin
OBJ_DIR=./obj
SRC_DIR=./src
INCL_DIR=./include

OBJECTS=$(addprefix $(OBJ_DIR)/, functions.o shuffle.o)
INCLUDES=$(addprefix $(INCL_DIR)/, functions.h shuffle.h mnist.h)

CFLAGS=-g -Wall
EXEC=neural

# Generate the executable file
$(EXEC): $(SRC_DIR)/main.c $(OBJECTS)
	$(CC) $(CFLAGS) $< $(OBJECTS) -o $(BIN_DIR)/$(EXEC) -I $(INCL_DIR) -lm

# Compile and Assemble C source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $@

# Clean the generated executable file and object files
.PHONY: clean mrproper
clean:
	rm -rf $(OBJ_DIR)/*.o

mrproper: clean
	rm -rf $(BIN_DIR)/$(EXEC)*