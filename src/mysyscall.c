#include <mysyscall.h>

ssize_t write(int fd, const void *buf, size_t nbyte)
{
	ssize_t ret;

    asm volatile(
        "movq $1, %%rax\n\t"   // 0 = SYS_read
        "movq %1, %%rdi\n\t"   // fd
        "movq %2, %%rsi\n\t"   // buf
        "movq %3, %%rdx\n\t"   // count
        "syscall\n\t"
        "movq %%rax, %0\n\t"   // ret = rax
        : "=r"(ret)
        : "r"((long)fd), "r"(buf), "r"(nbyte)
        : "rax","rdi","rsi","rdx","rcx","r11","memory"
    );
    return ret;
}

ssize_t read(int fd, void *buf, size_t count)
{
	size_t ret;

    asm volatile(
        "movq $0, %%rax\n\t"   // 0 = SYS_read
        "movq %1, %%rdi\n\t"   // fd
        "movq %2, %%rsi\n\t"   // buf
        "movq %3, %%rdx\n\t"   // count
        "syscall\n\t"
        "movq %%rax, %0\n\t"   // ret = rax
        : "=r"(ret)
        : "r"((long)fd), "r"(buf), "r"(count)
        : "rax","rdi","rsi","rdx","rcx","r11","memory"
    );
    return ret;
}

void sys_exit(int code)
{
    asm volatile (
        "movq $60, %%rax\n\t"  // syscall number: 60 = exit
        "movq %0, %%rdi\n\t"   // arg1 = exit code
        "syscall\n\t"
        :
        : "r"((long)code)
        : "rax", "rdi"
    );
}

int strlen(const char *str)
{
	int i=0;
	while(str[i])
	{
		i++;
	}
	return i;
}

int main()
{
	char test[16]="three\n";
	write(1, test, 6);

	return 0;
}

void _start()
{
	main();
	sys_exit(0);
}