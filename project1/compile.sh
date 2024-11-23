cd src/
gcc -I./usr/local/include -L./usr/local/lib main.c reader.c mol.c matrix.c -ltrexio -o main