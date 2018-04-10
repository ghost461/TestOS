#ifndef INCLUDE_MULTIBOOT_H_
#define INCLUDE_MULTIBOOT_H_

#include"types.h"

/*
 * 启动后，在32位内核进入点，机器状态如下：
 * 	1、CS指向基地址为0x00000000， 限长为4G - 1的代码段描述符。
 * 	2、DS, SS, ES, FS, 和GS指向基地址为0x00000000，限长为4G - 1的数据段描述符。
 * 	3、A20地址线已经打开。
 * 	4、页机制被禁止。
 * 	5、中断被禁止。
 * 	6、EAX = 0x2BADB002
 * 	7、系统信息和启动信息块的线性地址保存在EBX中(相当于一个指针)。
 * 	   以下即为这个信息块的结构
 * 
 */

typedef
struct multiboot_t {
	uint32_t flags;         // Mltiboot的版本信息
	/**
	 * 从BIOS获知的可用内存
	 * 
	 * mem_lower和mem_upper分别指出了低端和高端内存的大小, 单位是k。
	 * 低端内存首地址是0，高端内存首地址是1M。
	 * 低端内存的最大可能值是640k。
	 * 高端内存地址的最大可能值是最大值减去1M。但并不保证是这个值。
	 * 
	 */
	uint32_t mem_lower;
	uint32_t mem_upper;

	uint32_t boot_device;        // 指出引导程序从哪个BIOS磁盘设备载入的OS镜像
	uint32_t cmdline;            // 内核命令行
	uint32_t mods_count;         // boot模块列表
	uint32_t mods_addr;
};

#endif // INCLUDE_MULTIBOOT_H_
