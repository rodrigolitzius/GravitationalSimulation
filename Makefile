src_folder=./src
obj_folder=./obj

cc=gcc
files=main.o functions.o body.o view.o event-handler.o
cflags_warnings=-std=c17 -Wall -Wextra -pedantic -pedantic-errors
cflags_libs=-lSDL2 -lm
cflags=$(cflags_warnings) $(cflags_libs)
output_file=main

all: $(files)
	$(cc) $(cflags) $(obj_folder)/*.o -o $(output_file)

%.o: $(src_folder)/%.c
	$(cc) $(cflags) -c $< -o $(obj_folder)/$@