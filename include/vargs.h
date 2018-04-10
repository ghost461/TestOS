#ifndef INCLUDE_VARGS_H_
#define INCLUDE_VARGS_H_

/*
 * �ɱ��βα���صĺ궨��
 * 
 */

typedef __builtin_va_list va_list;

#define va_start(ap, last)        (__builtin_va_start(ap, last))
#define va_arg(ap, type)          (__builtin_va_arg(ap, type))
#define va_end(ap)

/*
 * va_list��gcc�ڽ�
 * ����ĺ궨��������ȼ�
 * 
 * #define va_list            char *
 * 
 * #define va_start(p, first) (p = (va_list)&first + sizrof(first))
 * #define va_arg(p, next)    (*(next*)((p += sizeof(next)) - sizeof(next)))
 * #define va_end(p)          (p = (va_list)NULL)
 * 
 */

#endif // INCLUDE_VARGS_H_
