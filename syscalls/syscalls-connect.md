# Linux系统调用：*connect*

[TOC]

## 1. 概要

```c
#include <sys/socket.h>

int connect(
    int sockfd
,   const struct sockaddr *addr
,   socklen_t addrlen
);
```



## 2. 描述

- 当套接字类型为 *SOCK_DGRAM* 时：

  **addr* 是：1）数据报发送的默认目的地址、2）数据报接收的唯一来源地址

- 当套接字类型 *SOCK_STREAM* 或 *SOCK_SEQPACKET* 时：

  函数尝试创建 *sockfd* 引用的套接字与 **addr* 绑定到的套接字之间的连接



## 3. 参数

### 3.1. *sockfd* < `int` >

套接字文件描述符

- 引用的套接字用于和 **addr* 绑定的套接字连接



### 3.2. *addr* <`const struct sockaddr *`>

指针，指向要与之建立连接的服务端地址



### 3.3. addrlen <`socklen_t `>

服务端地址数据宽度（Byte）



## 4. 返回值

- 函数执行成功后返回新建套接字的文件描述符

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[connect(2) — Linux manual page](https://man7.org/linux/man-pages/man2/connect.2.html)