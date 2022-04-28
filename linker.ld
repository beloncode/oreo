ENTRY(O_start)
STARTUP(libc/crt0.o)

SECTIONS {
  .text (0x1000) : ALIGN(0x1000) {
  __text__start = .;
  *(.text)
  __text__end = .;
  }

  .data : ALIGN(0x1000) {
  *(.data)
  }

  .bss : ALIGN(0x1000) {
  *(.bss)
  }
}

