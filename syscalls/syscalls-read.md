# Linux系统调用：*read*

[TOC]

## 1. 概要

```c
#include <unistd.h>

ssize_t read(
    int fd
,   void *buf
,   size_t count
);
```



## 2. 描述

尝试从文件描述符 *fd* 引用的文件中读取最多 *count* 个字节到以 *buf* 为开头的缓冲区中



## 3. 参数

### 3.1. *fd* < `int` >

文件描述符

- 要读取的文件



### 3.2. *buf* <`void *`>

指针，指向存放数据的缓冲区首地址



### 3.3. count <`size_t `>

最多读取的数据数量（Byte）



## 4. 返回值

- 函数执行成功后返回读到的数据数量（返回 ‘0’ 时表示读到文件结尾 ‘EOF’）

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[read(2) — Linux manual page](https://man7.org/linux/man-pages/man2/read.2.html)