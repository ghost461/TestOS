#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

#参数解释: -m32 是生成32位代码; 
#		   -ggdb和-gstabs+ 是添加相关调试信息; 
#		   -nostdlic 是不包含C语言标准库里的头文件
#		   -fno-builtin 是要求GCC不主动使用自己的内建函数，除非显式声明
#		   -fno-stack-protector 是不使用栈保护等检测
C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include

#参数解释: -T scripts/kernel.ld 是使用自己的链接器脚本; 
#		   -m elf_i386 是生成i386平台下的ELF格式的可执行文件，这是Linux下的可执行文件格式
#		   -nostdlib 是不链接C语言的标准库，原因同上
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib

ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

.c.o:
	@echo Compiling code files $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo  Compiling assembly files $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo Linking the kernel file...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o TestOS_kernel

.PHONY:clean
clean:
	$(RM) $(S_OBJECT) $(C_OBJECTS) TestOS_kernel

.PHONY:update_image
update_image:
	sudo mount grub.img /mnt/kernel
	sudo cp TestOS_kernel /mnt/kernel/TestOS_kernel
	sleep 1
	sudo umount /mnt/kernel

.PHONY:umount_image
umount_image:
	sudo umount /mnt/kernel

.PHONY:qemu
qemu:
	qemu -fda grub.img -boot a

.PHONY:bochs
bochs:
	bochs -f tools/bochsrc.txt

.PHONY:debug
debug:
	qemu -S -s -fda grub.img -boot a &
	sleep 1
	cgdb -x tools/gdbinit
