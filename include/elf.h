#ifndef INCLUDE_ELF_H_
#define INCLUDE_ELF_H_

#include"types.h"
#include"multiboot.h"

#define ELF32_ST_TYPE(i) ((i)&0xf)

// ELF ��ʽ����ͷ
typedef
struct elf_section_header_t {
	uint32_t name;
	uint32_t type;
	uint32_t flags;
	uint32_t addr;
	uint32_t offset;
	uint32_t size;
	uint32_t link;
	uint32_t info;
	uint32_t addralign;
	uint32_t entsize;
} __attribute__((packed)) elf_section_header_t;

// __attribute__((packed)) ���߱�����ȡ���ṹ�ڱ�������е��Ż�����
// ����ʵ��ռ���ֽ������ж��룬��GCC�����﷨

// ELF ��ʽ����
typedef
struct elf_symbol_t {
	uint32_t name;
	uint32_t value;
	uint32_t size;
	uint8_t info;
	uint8_t other;
	uint16_t shndx;
} __attribute__((packed)) elf_symbol_t;

// ELF��Ϣ
typedef
struct elf_t {
	elf_symbol_t *symtab;
	uint32_t symtabsz;
	const char *strtab;
	uint32_t strtabsz;
} elf_t;

// ��multiboot_t�ṹ��ȡELF��Ϣ
elf_t elf_from_multiboot(multiboot_t *mb);

// �鿴ELF�ķ�����Ϣ
const char *elf_lookup_symbol(uint32_t addr, elf_t *elf);

#endif // INCLUDE_ELF_H_
