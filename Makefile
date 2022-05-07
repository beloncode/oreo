CC?=gcc

LD?=ld

LD_SCRIPT=linker.ld

LDFLAGS=-T$(LD_SCRIPT)

AR?=ar

STRACE?=strace

DBG?=gdb

READELF=readelf

FILL_ARGV?=

INCLUDE_DIR=$(shell pwd)

CFLAGS=-Os\
	-ggdb\
	-nostdlib\
	-Wall\
	-Wno-implicit-function-declaration\
	-Wno-builtin-declaration-mismatch\
	-Wno-unknown-warning-option\
	-Werror\
	-I$(INCLUDE_DIR)\
	-fPIC

BIN=bin

LIB=lib

GIT_VER=$(shell git rev-parse --short HEAD)

OREO_VER=0.0.2_$(GIT_VER)

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
HEAP_LIB=$(LIB)/heap_$(OREO_VER)_$(ARCH).a

HEAP_OBJS=\
	heap/malloc_int.o

LIBC_OBJS=\
	libc/crt0.o\
	libc/features.o\
	libc/strrchr.o\
	libc/unistd.o\
	libc/stdlib.o\
	libc/mutex.o\
	libc/stdin.o\
	libc/stdout.o\
	libc/stdio.o\
	libc/poll.o\
	libc/strlen.o\
	libc/memcpy.o\
	libc/memmove.o\
	libc/memset.o\
	libc/strcmp.o

LIBRARIES=\
	$(LIBC_LIB)\
	$(HEAP_LIB)

$(HEAP_LIB): $(HEAP_OBJS)
	$(AR) rcs $@ $^

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
	flag.o\
	memory.o\
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

party:
	$(CC) ./party/puts_sys_test.c -o ./party/puts_sys_test &&\
		$(STRACE) ./party/puts_sys_test 2> ./party/puts_sys_test_strace

clean:
	@rm -f -v $(LIBC_OBJS)\
		$(HEAP_OBJS)\
		$(OREO_OBJS)\
		$(TEST_EXTRA_OBJS)\
		$(OREO_BIN)\
		$(TEST_BINS)\
		$(TEST_STRING_OBJS)\
		$(LIBRARIES)\
		./party/puts_sys_test ./party/puts_sys_test_strace

.PHONY: all clean dbg info party run test

