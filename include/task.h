/**
 * 
 * ���̹�����صĶ���
 * 
 */

#ifndef INCLUDE_TASK_H_
#define INCLUDE_TASK_H_

#include"types.h"
#include"pmm.h"
#include"vmm.h"

// ����״̬����
typedef
enum task_state {
	TASK_UNINIT = 0,    // δ��ʼ��
	TASK_SLEEPING = 1,  // ˯����
	TASK_RUNNABLE = 2,  // ������(Ҳ����������)
	TASK_ZOMBIE = 3     // ��ʬ״̬
} task_state;

// �ں��̵߳��������л��������Ϣ
struct context {
	uint32_t esp;
	uint32_t ebp;
	uint32_t ebx;
	uint32_t esi;
	uint32_t edi;
	uint32_t eflags;
};

// �����ڴ��ַ�ṹ
struct mm_struct {
	pgd_t *pgd_dir;    // ����ҳ��
};

// ���̿��ƿ�PCB
struct task_struct {
	volatile task_state state;	      // ���̵�ǰ״̬
	pid_t    pid;			      // ���̱�ʶ��
	void    *stack;			      // ���̵��ں�ջ��ַ
	struct   mm_struct   *mm;	      // ��ǰ���̵��ڴ��ַӳ��
	struct   context      context;	      // �����л���Ҫ����������Ϣ
	struct   task_struct *next;           // ����ָ��
};

// ȫ�� pid ֵ
extern pid_t now_pid;

// �ں��̴߳���
int32_t kernel_thread(int (*fn)(void *), void  *arg);

// �߳��˳�����
void kthread_exit();

#endif // INCLUDE_TASK_H_
