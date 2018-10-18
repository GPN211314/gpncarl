CC=gcc
all:
	gcc -g *.c -o main `pkg-config --cflags --libs gtk+-2.0`
