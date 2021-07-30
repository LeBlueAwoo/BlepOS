.set MAGIC, 0x1badb002                 # Behold: the magic number. Oooooooooh!
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain
.extern callConstructors
.global loader

loader:                                # Eww, x86 Assembly? Get me outta here! (Enter kernel.cpp)
    mov $kernel_stack, %esp

    call callConstructors

    push %eax
    push %ebx
    call kernelMain

_stop:                                 # The "Halt and catch fire" command.
    cli        # Disable interrupts
    hlt        # Halt the CPU
    jmp _stop  # "It ain't dead? Kill it again!"


.section .bss
.space 2*1024*1024 # 2MiB

kernel_stack:

