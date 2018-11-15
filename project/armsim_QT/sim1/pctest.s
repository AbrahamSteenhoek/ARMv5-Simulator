@@@ PC modification test

.global _start
.text
_start:
  mov r0, #2
  mov r1, #10
  mov r2, #32
  add r15, r15, #12
  add r3, r1, r2
  add r4, r2, r1, lsl r0
  add r6, r15, #8
  mov r15, r6
  orr r5, r2, r0
  sub r15, r15, #28
  ldm r13, {r0 - r6}
  mov r0, r15
  swi 0x11
  