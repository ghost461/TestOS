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

	/**
	 * ELF格式内核影响的section头表、每项的大小、一共有几项以及作为名字索引的字符串表。
	 * 他们对应于可执行连接格式（ELF）的program头中的shdr_*项（shdr_num等）。
	 * 所有i的section都会被载入，ELF section头的物理地址域指向所有的section在内存中的位置。
	 */
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;

	/**
	 * 以下两项指出保存由BIOS提供的内存分布的缓冲区的地址和长度
	 * mmap_addr是缓冲区的地址，mmap_length是缓冲区的总大小
	 * 缓冲区由一个或者多个下面的大小/结构对mmap_entry_t（size实际上是用来跳过下一个对的）组成
	 */
	uint32_t mmap_length;
	uint32_t mmap_addr;

	uint32_t drives_length;        // 指出第一个驱动器结构的物理大小
	uint32_t drives_addr;          // 指出第一个驱动器这个结构的地址
	uint32_t config_table;         // ROM配置表
	uint32_t boot_loader_name;     // boot loader的名字
	uint32_t apm_table;            // APM表
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint32_t vbe_mode;
	uint32_t vbe_interface_seg;
	uint32_t vbe_interface_off;
	uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;

/**
 * size是相关结构的大小，单位是字节，它可能大于最小值20
 * base_addr_low是启动地址的低32为，base_addr_high是高32位，启动地址总共有64位
 * length_low是内存区域大小的低32位，length_high是内存区域大小的高32位，总共是64位
 * type是相应地址区间的类型，1代表可用RAM，所有其他的值代表保留区域
 */
typedef struct mmap_entry_t {
	uint32_t size;        // 留意size是不含size自身变量的大小
	uint32_t base_addr_low;
	uint32_t base_addr_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
} __attribute__((packed)) mmap_entry_t;

// 声明全局变量的multiboot_t * 指针
extern multiboot_t *glb_mboot_ptr;

#endif // INCLUDE_MULTIBOOT_H_
