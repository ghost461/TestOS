#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include"types.h"

// 从src所指的内存地址开始拷贝len个字节到dest所指的地址中
static inline void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
	for(; len > 0; len--)
	{
		*dest++ = *src++;
	}
}

// 将dest所指的地址后的len个字节用val替换
static inline void memset(void *dest, uint8_t val, uint32_t len)
{
	uint8_t *dst = (uint8_t *)dest;

	for(; len > 0; len--)
	{
		*dst++ = val;
	}
}

// 将dest所指的地址后的len个字节置零
static inline void bzero(void *dest,uint32_t len)
{
	memset(dest, 0, len);
}

// 比较两个字符串
// 相同时返回0
// str1大于str2时返回正数
// str1大于str2时返回负数
static inline int strcmp(const char *str1, const char *str2)
{
	while(*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

// 把src指向的字符串复制到dest所指的地址空间内
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

// 把src所指向的字符串添加到dest结尾处
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

// 计算给定字符串的长度，不包括结束符
static inline int strlen(const char *src) {
	const char *eos = src;

	while(*eos++);

	return (eos - src - 1);
}

#endif // INCLUDE_STRING_H_
