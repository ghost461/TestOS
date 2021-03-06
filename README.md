# TestOS
## 基于X86架构的初级操作系统内核
- 启动过程使用GURB引导，遵循multiboot标准(使用1.44MB软盘引导)
- 库函数:
- --------字符模式的显卡驱动(默认80x25大小)
- --------内核打印函数库(printk)
- --------字符串处理(string)
- --------ELF可执行文件支持(elf)
- 保护模式与全局段描述符表
- 中断描述符表
- 物理内存分页式管理(当前仅支持最大512MB)
## 目录结构
	.
	├── boot
	│   └── boot.s		// 计算机启动汇编码
	├── drivers
	│   ├── console.c	// 字符模式的显卡驱动
	│   └── timer.c		// 定时器驱动
	├── gdt			// 全局段描述符表实现
	│   ├── gdt.c	
	│   └── gdt_s.s
	├── grub.img		// 软盘镜像
	├── idt 		// 中断描述符表实现
	│   ├── idt.c
	│   └── idt_s.s
	├── include
	│   ├── common.h 	// 基础端口读写
	│   ├── console.h	// 字符模式的显卡驱动
	│   ├── debug.h 	// 相关调试函数声明
	│   ├── elf.h 		// ELF格式声明
	│   ├── gdt.h 		// 全局段描述符表声明
	│   ├── idt.h 		// 中断描述符表声明
	│   ├── multiboot.h	// Multiboot结构定义
	│   ├── pmm.h 		// 页式内存管理
	│   ├── string.h 	// 字符处理
	│   ├── timer.h 	// 定时器
	│   ├── types.h 	// 基础类型定义
	│   └── vargs.h 	// 可变形参相关
	├── init
	│   └── entry.c 	// 内核入口
	├── kernel
	│   └── debug
	│       ├── debug.c	// 相关调试函数实现
	│       └── printk.c	// 内核级打印函数
	├── libs
	│   ├── common.c	// 基础端口读写实现
	│   └── elf.c 		// ELF
	├── LICENSE
	├── Makefile
	├── mm
	│   └── pmm.c 		// 页式存储管理实现
	├── README.md
	└── scripts
	    ├── gdbinit		// debug模式gdb初始化
	    └── kernel.ld	// 链接器脚本
