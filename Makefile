OUTPUT_FILE=main
SRC=./src
COMP=./comp

FILES=$(wildcard $(SRC)/*.c)
HEADERS=$(wildcard $(SRC)/*.h)
OBJECTS=$(patsubst $(SRC)/%,$(COMP)/%,$(patsubst %.c,%.o,$(FILES)))
DEPENDS=$(patsubst $(SRC)/%,$(COMP)/%,$(patsubst %.c,%.d,$(FILES)))

CC=gcc
CFLAGS_WARNINGS=-std=c17 -Wall -Wextra -pedantic -pedantic-errors
CFLAGS_LIBS=-lSDL2 -lm
CFLAGS=$(CFLAGS_WARNINGS) $(CFLAGS_LIBS)

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTPUT_FILE) $(CFLAGS)

-include $(DEPENDS)
$(COMP)/%.o: $(SRC)/%.c Makefile
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

clean:
	@rm $(COMP)/*