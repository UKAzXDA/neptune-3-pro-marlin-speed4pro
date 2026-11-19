#include <stdint.h>

#define APPLICATION_ADDRESS 0x08008000u

void Reset_Handler(void);

__attribute__((used, section(".isr_vector")))
const uint32_t boot_vectors[] = {
  0x20010000u,
  (uint32_t)(uintptr_t)Reset_Handler
};

__attribute__((naked, noreturn, used))
void Reset_Handler(void) {
  __asm volatile(
    "ldr r0, =0x08008000\n"
    "ldr r1, [r0]\n"
    "ldr r2, [r0, #4]\n"
    "ldr r3, =0x20000000\n"
    "cmp r1, r3\n"
    "blo 1f\n"
    "ldr r3, =0x20010000\n"
    "cmp r1, r3\n"
    "bhi 1f\n"
    "tst r2, #1\n"
    "beq 1f\n"
    "ldr r3, =0x08008000\n"
    "cmp r2, r3\n"
    "blo 1f\n"
    "ldr r3, =0x08040000\n"
    "cmp r2, r3\n"
    "bhs 1f\n"
    "ldr r3, =0xE000ED08\n"
    "str r0, [r3]\n"
    "dsb\n"
    "isb\n"
    "msr msp, r1\n"
    "bx r2\n"
    "1: b 1b\n"
  );
}
