/* led_on.S */

.global _start
_start:
    ldr r0, =0xE0200240
    ldr r1, =0x00001000
    str r1, [r0]

    ldr r0, =0xE0200244
    ldr r1, =0x00000000
    str r1, [r0]

halt:
    b halt

