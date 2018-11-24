# Author: Alex St. Clair
# Created: 9-24-2018
#
# With inspiration from the following tutorial:
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC=gcc
CFLAGS= -Wall -Wextra
OBJECTS= circular_buffer.o

%.o: %.c ../inc/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

test_main: main.c $(OBJECTS)
	$(CC) -o test_main main.c $(OBJECTS) $(CFLAGS)

clean:
	rm test_main
	rm *.o
