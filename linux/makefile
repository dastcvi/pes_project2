# Author: Alex St. Clair
# Created: 9-24-2018
#
# With inspiration from the following tutorial:
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC=gcc
CFLAGS= -Wall -Wextra
OBJECTS= circular_buffer.o

main: src/main.c $(OBJECTS)
	$(CC) -o main src/main.c $(OBJECTS) $(CFLAGS)

unittest: Unittest/unittest.c $(OBJECTS)
	$(CC) -o unittest Unittest/unittest.c $(OBJECTS) $(CFLAGS) -lcunit

%.o: src/%.c inc/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm unittest
	rm *.o
	rm main
