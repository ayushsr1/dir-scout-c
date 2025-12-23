CC=gcc
CFLAGS=-Wall -O2
LIBS=-lcurl

all:
	$(CC) dirscout.c -o dirscout $(CFLAGS) $(LIBS)

clean:
	rm -f dirscout
