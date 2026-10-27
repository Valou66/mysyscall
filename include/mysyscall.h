#ifndef MYSYSCALL_H
# define MYSYSCALL_H

typedef signed long ssize_t;
typedef unsigned long size_t;

ssize_t write(int fd, const void *buf, size_t nbyte);
ssize_t read(int fd, void *buf, size_t count);
void sys_exit(int code);

#endif