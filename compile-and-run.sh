src_folder="./src"

cflags_warnings="-std=c17 -Wall -Wextra -pedantic -pedantic-errors"
cflags_libs="$(pkg-config --cflags --libs sdl2) -lm"
cflags="$cflags_warnings $cflags_libs"

gcc $src_folder/main.c $src_folder/functions.c $src_folder/body.c $cflags -o main

./main