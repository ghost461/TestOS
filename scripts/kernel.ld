
/**
 * 
 * 首先，我们声明了内核程序的入口地址是符号“start”
 * 这个脚本告诉 ld 程序如何构造内核映像文件
 * 然后，声明了第一段 .text 段(代码段)以及它的起始地址 0x100000 (1MB)
 * 接着是已初始化数据段 .data 和未初始化数据段 .bss 以及它们采用的4096的页对齐方式
 * Linux GCC 增加了额外的数据段 .rodata, 这是一个只读的已初始化数据段，放置常量等
 * 简单起见，就把它和 .data 段放在一起了
 * 
 */

ENTRY(start)
SECTIONS
{
	PROVIDE( kern_start = 0xC0100000);
	. = 0x100000;
	.init.text :
	{
		*(.init.text)
		. = ALIGN(4096);
	}
	.init.data :
	{
		*(.init.data)
		. = ALIGN(4096);
	}

	. += 0xC0000000;
	.text : AT(ADDR(.text) - 0xC0000000)
	{
		*(.text)
		. = ALIGN(4096);
	}
	.data : AT(ADDR(.data) - 0xC0000000)
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.bss : AT(ADDR(.bss) - 0xC0000000)
	{
		*(.bss)
		. = ALIGN(4096);
	}
	.stab : AT(ADDR(.stab) - 0xC0000000)
	{
		*(.stab)
		. = ALIGN(4096);
	}
	.stabstr : AT(ADDR(.stabstr) - 0xC0000000)
	{
		*(.stabstr)
		. = ALIGN(4096);
	}
	PROVIDE( kern_end  = . );

	/DISCARD/ : { *(.comment) *(.eh_frame) }
}
