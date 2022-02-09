# Linux系统调用：*read*

[TOC]

## 1. 概要

```c
#include <unistd.h>

ssize_t write(
    int fd
,   const void *buf
,   size_t count
);
```



## 2. 描述

将 *buf* 指向的缓冲区中最多 *count* 个字节的数据写入文件描述符 *fd* 引用的文件中



## 3. 参数

### 3.1. *fd* < `int` >

文件描述符

- 应用要写的文件



### 3.2. *buf* <`const void *`>

指针，指向存放数据的缓冲区首地址



### 3.3. count <`size_t `>

要写入的数据数量（Byte）



## 4. 返回值

- 函数执行成功后返回写入的数据字节数

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[write(2) — Linux manual page](https://man7.org/linux/man-pages/man2/write.2.html)