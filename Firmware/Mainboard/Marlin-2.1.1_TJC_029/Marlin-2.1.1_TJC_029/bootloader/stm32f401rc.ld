ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
  .isr_vector ORIGIN(FLASH) : ALIGN(512)
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
  } > FLASH

  /DISCARD/ :
  {
    *(.comment*)
    *(.note*)
    *(.ARM.exidx*)
    *(.ARM.extab*)
  }
}
