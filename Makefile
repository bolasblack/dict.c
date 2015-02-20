CC ?= gcc
CFLAGS = -O3 -std=c99 -Wall -Wextra -Ideps

SRCS = src/dict.c \
		   src/dict_pair.c \
		   src/dict_iterator.c

OBJS = $(SRCS:.c=.o)

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

.PHONY: test benchmark clean
