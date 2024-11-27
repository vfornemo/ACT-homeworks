cd src/
gcc -I/usr/local/include -L/usr/local/lib  main.c util.c reader.c mol.c hf.c mp2.c -o ../main.o -ltrexio
