#CC:=ccache $(CC)
CC:=gcc 
CFLAGS+=-o2
CFLAGS+=-std=gnu99
CFLAGS+=-pedantic -Wall
LDFLAGS+=-lpthread

TARGET=main

$(TARGET): 
	$(CC) $(CFLAGS) main.c -o main $(LDFLAGS)


