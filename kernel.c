typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;


extern char __bss[], __bss_end[], __stack_top[];  //so basically this line leaves some space in the memory. usefil to work with linker fines I guess.
//each symbol defined in the linker script is declared using extern char, (char is theere because 1 byte and its simple, becasue c being c it asks for type. So we give char) 
//extern char __bss, here _bss means the value at the start of bss, but we want the address, so we write []. This is supposed to return
//the address.


//memset function similar to memset in cpp
void *memset(void *buf, char c, size_t n){
    uint8_t *p = (uint8_t *) buf;
    while(n--)
        *p++ = c;

    return buf;
}

//just calls memset in assign 0 to the bss start to bss end. 
void kernel_main(void) {
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    for (;;);
}

__attribute__((section(".text.boot")))
__attribute((naked))

void boot(void){
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n" //sets the stack pointer
        "j kernel_main\n" //Jump to the kernel main function 
        :
        : [stack_top] "r" (__stack_top) //pass the stack top address as %[stack_top]
    );
}



//wowo none of this is making sense, it does not even look like c bhai, what did gaurav sir teach us and what is this.

//Kernal starts from boot func (written in the kernel.ld as the entry)
//in the boot function stack pointer sp, starts with end address of the stack, defined in kernel.ld
//then is jumps to kernel_main function
//stack is decremented as it is used thats why the end addresss of the stack is set not the start .


//boot func
/*
    __attribute__((section("naked"))) attribute instructs compiler to not generate unnecessary
    code before and after the function body. such is return function (I mean why does it do that wtf)

    The boot function also has the __attribute__((section(".text.boot"))) attribute, which controls
    the placement of the function in the linker script. 
    
    Since OpenSBI simply jumps to 0x80200000 
    without knowing the entry point, the boot function needs to be placed at 0x80200000

*/

