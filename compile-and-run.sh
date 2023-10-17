src_folder="./src"
gcc $src_folder/main.c $src_folder/functions.c -std=c17 -Wall -Wextra -pedantic -pedantic-errors -lSDL2 -lSDL2main -lm -o main

./main