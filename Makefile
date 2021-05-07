CC = gcc

a.out: main.c Func/*.c
        $(CC) main.c Func/*.c
