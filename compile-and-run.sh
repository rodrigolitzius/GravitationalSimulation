src_folder="./src"
cflags="-std=c17 -Wall -Wextra -pedantic -pedantic-errors -lSDL2 -lSDL2main -lm"
gcc $src_folder/main.c $src_folder/functions.c $src_folder/body.c $cflags -o main

./main