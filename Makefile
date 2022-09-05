CC?=gcc

LD?=ld

LD_SCRIPT=linker.ld

LDFLAGS=-T$(LD_SCRIPT)

AR?=ar

STRACE?=strace

DBG?=gdb

READELF=readelf

FILLARGV=

INCLUDEDIR=$(shell pwd)

CFLAGS=-Os\
	-ggdb\
	-nostdlib\
	-Wall\
	-Wno-implicit-function-declaration\
	-Wno-builtin-declaration-mismatch\
	-Wno-unknown-warning-option\
	-Werror\
	-I$(INCLUDEDIR)\
	-fPIC

BIN=bin

LIB=lib

GITVER=$(shell git rev-parse --short HEAD)

OREOVER=003.$(GITVER)

ARCH=x86

OREOBIN=$(BIN)/oreo$(OREOVER)$(ARCH)

all: $(OREOBIN)

run: $(OREOBIN)
	./$< $(FILLARGV)

info: $(OREOBIN)
	$(READELF) --relocs --dyn-syms --file-header --syms $<

dbg: $(OREOBIN)
	$(DBG) --args ./$< $(FILL_ARGV)

LIBCLIB=$(LIB)/libc$(OREOVER)$(ARCH).a
HEAPLIB=$(LIB)/heap$(OREOVER)$(ARCH).a

HEAPOBJS=\
	heap/mallocInt.o\
	heap/heap.o

LIBCOBJS=\
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
	$(LIBCLIB)\
	$(HEAPLIB)

$(HEAPLIB): $(HEAPOBJS)
	$(AR) rcs $@ $^

$(LIBCLIB): $(LIBCOBJS)
	$(AR) rcs $@ $^

TESTSTRINGOBJS=libc/stringTest.o
TESTMALLOCOBJS=heap/mallocTest.o

TESTEXTRAOBJS=test/expect.o fatal.o

TESTSTRING=libc/stringTest.$(OREOVER)$(ARCH)
TESTMALLOC=heap/mallocTest.$(OREOVER)$(ARCH)

TESTBINS=\
	$(TESTSTRING)\
	$(TESTMALLOC)

OREO_OBJS=\
	test/expect.o\
	fatal.o\
	flag.o\
	memory.o\
	oreomain.o

$(OREOBIN): $(OREO_OBJS) $(LIBRARIES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	wc -c $(OREOBIN)

$(TESTSTRING): $(TESTSTRINGOBJS) $(TESTEXTRAOBJS) $(LIBCLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TESTMALLOC): $(TESTMALLOCOBJS) $(TESTEXTRAOBJS) $(LIBCLIB) $(HEAPLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

test: $(TESTBINS)
	./$(TESTSTRING) && ./$(TESTMALLOC)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

party:
	$(CC) ./party/puts_sys_test.c -o ./party/puts_sys_test &&\
		$(STRACE) ./party/puts_sys_test 2> ./party/puts_sys_test_strace

clean:
	@rm -f -v $(LIBCOBJS)\
		$(HEAPOBJS)\
		$(OREO_OBJS)\
		$(TESTEXTRAOBJS)\
		$(OREOBIN)\
		$(TESTBINS)\
		$(TESTSTRINGOBJS)\
		$(TESTMALLOCOBJS)\
		$(LIBRARIES)\
		./party/puts_sys_test ./party/puts_sys_test_strace

.PHONY: all clean dbg info party run test

