CC=gcc
TARGET=main
OBJS=main.o
LIBS= -lcrypto -lssl -ldl
CFLAGS=-Wall -O2
CC = gcc

main: main.o
	$(CC) -o main main.o $(LIBS)

all: $(OBJS)
	gcc $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET) *~ *.log