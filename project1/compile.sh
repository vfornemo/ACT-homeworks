cd src/
gcc -I/usr/local/include -L/usr/local/lib  main.c util.c reader.c mol.c hf.c -o ../main.o -ltrexio
