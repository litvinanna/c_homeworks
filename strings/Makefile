CC=gcc
CFLAGS=-c -Wall -O3

all: bitseq testRK

# bitseqanother: mainasiudhga.o strings.o

bitseq: mainBitSeq.o strings.o lists.o stack.o arrays.o
	$(CC) mainBitSeq.o stack.o lists.o strings.o arrays.o -o bitseq

testRK: mainTestRK.o strings.o lists.o stack.o arrays.o
	$(CC) -O3 mainTestRK.o stack.o lists.o strings.o arrays.o -o testRK
strings.o: ../libs/strings.c
	$(CC) $(CFLAGS) ../libs/strings.c

lists.o: ../libs/lists.c
	$(CC) $(CFLAGS) ../libs/lists.c

stack.o: ../libs/stack.c
	$(CC) $(CFLAGS) ../libs/stack.c

arrays.o:
	$(CC) $(CFLAGS) ../libs/arrays.c

mainBitSeq.o: mainBitSeq.c
	$(CC) $(CFLAGS) mainBitSeq.c

mainTestRK.o: mainTestRK.c
	$(CC) $(CFLAGS) mainTestRK.c


clean:
	rm -rf *.o bitseq

