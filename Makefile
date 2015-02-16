
AR ?= ar
CC ?= gcc
PREFIX ?= /usr/local

CFLAGS = -O3 -std=c99 -Wall -Wextra -Ideps

SRCS = src/dict.c \
		   src/dict_pair.c \
		   src/dict_iterator.c

OBJS = $(SRCS:.c=.o)

all: build/libdict.a

install: all
	cp -f build/libdict.a $(PREFIX)/lib/libdict.a
	cp -f src/dict.h $(PREFIX)/include/dict.h

uninstall:
	rm -f $(PREFIX)/lib/libdict.a
	rm -f $(PREFIX)/include/dict.h

build/libdict.a: $(OBJS)
	@mkdir -p build
	$(AR) rcs $@ $^

bin/test: test.o $(OBJS)
	@mkdir -p bin
	$(CC) $^ -o $@

bin/benchmark: benchmark.o $(OBJS)
	@mkdir -p bin
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -fr bin build *.o src/*.o

test: bin/test
	@./$<

benchmark: bin/benchmark
	@./$<

.PHONY: test benchmark clean install uninstall
