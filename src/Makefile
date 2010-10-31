CC = g++
DBG = -g -D_DBG
SRCS = sparseMat.cpp main.cpp
CFLAGS = -ansi -pedantic -Wall -Wshadow
OBJS = $(SRCS:.cpp=.o) 
OUT= out

.PHONY: mat

all: mat

mat: $(OBJS)
	echo "Linking $(OBJS)"
	$(CC) $(CFLAGS) $(DBG) -o $(OUT) $^

.cpp.o:
	echo "Compiling $@\n"
	$(CC) $(CFLAGS) $(DBG) -c -o $@ $<

depend:
	makedepend -- $(CFLAGS) -- $(SRCS)

clean:
	rm $(OUT)
	rm $(OBJS)

# DO NOT DELETE THIS LINE

sparseMat.o: sparseMat.h
main.o: /usr/include/stdio.h /usr/include/_types.h /usr/include/sys/_types.h
main.o: /usr/include/sys/cdefs.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
main.o: /usr/include/secure/_common.h sparseMat.h
