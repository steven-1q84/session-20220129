# Linux系统调用：*listen*

[TOC]

## 1. 概要

```c
#include <sys/socket.h>

int listen(
    int sockfd
,   int backlog
);
```



## 2. 描述

监听套接字上的连接请求：

- 将文件描述符 *sockfd* 引用的套接字标记为被动类型
- i.e. 函数执行成功后*sockfd* 可接收（使用 *accept*）主动端（客户端）发送进来的连接请求 



## 3. 参数

### 3.1. *sockfd* < `int` >

套接字文件描述符

- 用于接收客户端连接请求

- 套接字为 *SOCK_STREAM* 或 *SOCK_SEQPACKET* 类型



### 3.2. *backlog* < `int` >

等待与服务端套接字连接的队列的最大长度

- 半连接（incomplete connection requests）队列长度

- `Linux 2.2. +` 等待“ *accept* ”的全连接（completely established）队列长度



## 4. 返回值

- 函数执行成功后返回新建套接字的文件描述符

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[listen(2) — Linux manual page](https://man7.org/linux/man-pages/man2/listen.2.html)