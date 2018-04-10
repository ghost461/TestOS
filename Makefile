#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

#��������: -m32 ������32λ����; 
#		   -ggdb��-gstabs+ �������ص�����Ϣ; 
#		   -nostdlic �ǲ�����C���Ա�׼�����ͷ�ļ�
#		   -fno-builtin ��Ҫ��GCC������ʹ���Լ����ڽ�������������ʽ����
#		   -fno-stack-protector �ǲ�ʹ��ջ�����ȼ��
C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include

#��������: -T scripts/kernel.ld ��ʹ���Լ����������ű�; 
#		   -m elf_i386 ������i386ƽ̨�µ�ELF��ʽ�Ŀ�ִ���ļ�������Linux�µĿ�ִ���ļ���ʽ
#		   -nostdlib �ǲ�����C���Եı�׼�⣬ԭ��ͬ��
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
	$(RM) $(S_OBJECTS) $(C_OBJECTS) TestOS_kernel

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
	bochs -f scripts/bochsrc.txt

.PHONY:debug
debug:
	# ��������:
	# -fda grub.img -boot a ��ָ�������ľ���
	# -s ��qemu����ʱ����1234�˿ڲ��ȴ�gdb����
	# -S ������ʱ���Զ���ʼ���У��ȴ�������ִ������
	# GDB������ĳ�ʼ���������scripts/gdbinit��
	# ��ʼ��������ش������ļ��ķ�����Ϣ
	#             ��kern_entry�����¶ϵ㲢ִ�е��ϵ㴦
	qemu -S -s -fda grub.img -boot a &
	sleep 1
	cgdb -x scripts/gdbinit
