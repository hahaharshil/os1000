#include <stdio.h>

//assembly in c template
// __asm__ --volatile__("assembly" : outputs operands : input operands : clobbered registers);

int main(void) {
    uint32_t value;

    __asm__ __volatile__("csrr %0, sepc" : "=r"(value));

}