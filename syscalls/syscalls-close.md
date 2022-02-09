# Linux系统调用：*close*

[TOC]

## 1. 概要

```c
#include <unistd.h>

int close(int fd);
```



## 2. 描述

关闭文件描述符



## 3. 参数

### 3.1. *fd* < `int` >

文件描述符



## 4. 返回值

- 函数执行成功后返回新建套接字的文件描述符

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[close(2) — Linux manual page](https://man7.org/linux/man-pages/man2/close.2.html)