#include"../include/console.h"
#include"../include/debug.h"
#include"../include/gdt.h"
#include"../include/idt.h"
#include"../include/timer.h"

int kern_entry() {
	init_debug();
	init_gdt();
	init_idt();

	console_clear();
	printk_color(rc_black, rc_green, "Hello, OS kernel!\n");

	init_timer(200);

	// ¿ªÆôÖÐ¶Ï
	asm volatile ("sti");

	/*
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
	*/

	return 0;
}
