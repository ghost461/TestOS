#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include"types.h"

// ��src��ָ���ڴ��ַ��ʼ����len���ֽڵ�dest��ָ�ĵ�ַ��
static inline void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
	for(; len > 0; len--)
	{
		*dest++ = *src++;
	}
}

// ��dest��ָ�ĵ�ַ���len���ֽ���val�滻
static inline void memset(void *dest, uint8_t val, uint32_t len)
{
	uint8_t *dst = (uint8_t *)dest;

	for(; len > 0; len--)
	{
		*dst++ = val;
	}
}

// ��dest��ָ�ĵ�ַ���len���ֽ�����
static inline void bzero(void *dest,uint32_t len)
{
	memset(dest, 0, len);
}

// �Ƚ������ַ���
// ��ͬʱ����0
// str1����str2ʱ��������
// str1����str2ʱ���ظ���
static inline int strcmp(const char *str1, const char *str2)
{
	while(*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

// ��srcָ����ַ������Ƶ�dest��ָ�ĵ�ַ�ռ���
char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while(*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return tmp;
}

// ��src��ָ����ַ�����ӵ�dest��β��
char *strcat(char *dest, const char *src)
{
	char *cp = dest;

	while(*cp)
	{
		cp++;
	}

	while((*cp++ = *src++));

	return dest;
}

// ��������ַ����ĳ��ȣ�������������
static inline int strlen(const char *src) {
	const char *eos = src;

	while(*eos++);

	return (eos - src - 1);
}

#endif // INCLUDE_STRING_H_
