CC?=gcc

LD?=ld

LD_SCRIPT=linker.ld

LDFLAGS=-T$(LD_SCRIPT)

AR?=ar

DBG=gdb

READELF=readelf

FILL_ARGV?=

INCLUDE_DIR=$(shell pwd)

CFLAGS=-Os -ggdb -nostdlib -Wall -Werror -I$(INCLUDE_DIR)

BIN=bin

LIB=lib

OREO_VER=0.0.1

ARCH=$(shell uname -m)

OREO_BIN=$(BIN)/oreo_$(OREO_VER)_$(ARCH)

all: $(OREO_BIN)

run: $(OREO_BIN)
	./$< $(FILL_ARGV)

info: $(OREO_BIN)
	$(READELF) --relocs --dyn-syms --file-header --syms $<

dbg: $(OREO_BIN)
	$(DBG) --args ./$< $(FILL_ARGV)

LIBC_LIB=$(LIB)/libc_$(OREO_VER)_$(ARCH).a

LIBC_OBJS=\
	libc/crt0.o\
	libc/features.o\
	libc/strrchr.o\
	libc/unistd.o\
	libc/stdlib.o\
	libc/mutex.o\
	libc/stdin.o\
	libc/stdout.o\
	libc/stdio.o

LIBRARIES=\
	$(LIBC_LIB)

$(LIBC_LIB): $(LIBC_OBJS)
	$(AR) rcs $@ $^

TEST_STRING_OBJS=libc/string_test.o
TEST_EXTRA_OBJS=test/expect.o fatal.o

TEST_STRING=libc/string_test_$(OREO_VER)_$(ARCH)

TEST_BINS=\
	$(TEST_STRING)

OREO_OBJS=\
	test/expect.o\
	fatal.o\
	oreomain.o

$(OREO_BIN): $(OREO_OBJS) $(LIBRARIES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	wc -c $(OREO_BIN)

$(TEST_STRING): $(TEST_STRING_OBJS) $(TEST_EXTRA_OBJS) $(LIBC_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

test: $(TEST_BINS)
	./$(TEST_STRING)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(LIBC_OBJS)
	rm -f $(OREO_OBJS)
	rm -f $(TEST_EXTRA_OBJS)
	rm -f $(OREO_BIN)
	rm -f $(TEST_BINS)
	rm -f $(TEST_STRING_OBJS)
	rm -f $(LIBRARIES)

.PHONY: all clean dbg info run test

