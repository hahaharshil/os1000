ENTRY(boot)

SECTIONS {
    . = 0x80200000;

    .text :{
        KEEP(*(.text.boot));
        *(.text .text.*);
    }

    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }

    .data : ALIGN(4) {
        *(.data .data.*);
    }

    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    . = ALIGN(4);
    . += 128 * 1024; /* 128KB */
    __stack_top = .;
}


/*

the key points of the linker script:

The entry point of the kernel is the boot function.

The base address is 0x80200000.

The .text.boot section is always placed at the beginning.

Each section is placed in the order of .text, .rodata, .data, and .bss.

The kernel stack comes after the .bss section, and its size is 128KB.

.text, .rodata, .data, and .bss sections mentioned here are data areas with specific roles:

Section	Description
.text	This section contains the code of the program.
.rodata	This section contains constant data that is read-only.
.data	This section contains read/write data.
.bss	This section contains read/write data with an initial value of zero.

*/
