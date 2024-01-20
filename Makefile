SRC=./src
OBJ=./obj

CC=gcc
FILES=$(OBJ)/main.o $(OBJ)/functions.o $(OBJ)/body.o $(OBJ)/view.o $(OBJ)/event-handler.o
CFLAGS_WARNINGS=-std=c17 -Wall -Wextra -pedantic -pedantic-errors
CFLAGS_LIBS=-lSDL2 -lm
CFLAGS=$(CFLAGS_WARNINGS) $(CFLAGS_LIBS)

OUTPUT_FILE=main

all: $(FILES)
	$(CC) $(OBJ)/*.o -o $(OUTPUT_FILE) $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm $(OBJ)/*