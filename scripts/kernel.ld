/*
 * kernel.ld -- 针对 kernel 格式所写的链接脚本
 * 告诉ld程序如何构造所需的内核映像文件
 */

/* 声明内核程序的入口地址是符号"start" */
ENTRY(start)
SECTIONS
{
	/* 段起始位置(1MB) */
	. = 0x100000;
	PROVIDE( kern_start = . );

	/* 代码段 */
	/* 采用4096的页对齐方式 */
	.text :
	{
		*(.text)
		. = ALIGN(4096);
	}

	/* 已初始化数据段 */
	/* 采用4096的页对齐方式 */
	.data :
	{
		*(.data)
		*(.rodata) /* 只读的已初始化数据段*/
		. = ALIGN(4096);
	}

	/* 未初始化数据段 */
	/* 采用4096的页对齐方式 */
	.bss :
	{
		*(.bss)
		. = ALIGN(4096);
	}

	/* 未初始化数据段 */
	.stab :
	{
		*(.stab)
		. = ALIGN(4096);
	}

	.stabstr :
	{
		*(.stabstr)
		. = ALIGN(4096);
	}
	PROVIDE( kern_end = . );

	/DISCARD/ : { *(.comment) *(.eh_frame)}
}
