# Linux系统调用：*accept*

[TOC]

## 1. 概要

```c
#include <sys/socket.h>

int accept(
    int sockfd
,   struct sockaddr *restrict addr
,   socklen_t *restrict addrlen
);
```

```C
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sys/socket.h>

int accept4(
    int sockfd
,   struct sockaddr *restrict addr
,   socklen_t *restrict addrlen
,   int flags
);
```



## 2. 描述

接收客户端发起的套接字连接（*connection*）请求：

- 套接字为基于连接的类型：*SOCK_STREAM*、*SOCK_SEQPACKET*
- 从“监听”套接字（*sockfd* 引用的套接字）的等待连接队列中取出最早的请求
- 创建新的“连接”套接字，返回因为该套接字的文件描述符
- 函数返回后“监听”套接字不会受到影响 

- 是否阻塞
  - 当等待连接队列**非空**，或套接字定义为**阻塞**时
    - 线程被阻塞，知道新的连接出现
  - 当等待连队列**空**，且套接字定义为**非阻塞**时
    - 线程继续执行
    - 置位错误信息：*EAGAIN* 或 *EWOULDBLOCK*



## 3. 参数

### 3.1. *sockfd* < `int` >

套接字文件描述符，满足以下条件：

- 使用 *socket* 创建
- 使用 *bind* 与本地地址绑定
- 使用 *listen* 监听连接请求



### 3.2. *addr* <`struct sockaddr *restrict`>

指针，指向客户端地址结构数据

- 用于写入发起连接请求的客户端套接字地址信息
- 当使用 *NULL* 时，不会有任何信息填入，此时 *addrlen* 也应使用 *NULL*



### 3.3. addrlen <`socklen_t *restrict`>

指针，指向保存 *addr* 长度的变量

- 由用户申请地址空间
- 函数调用完后，该地址空间为 *addr* 的实际长度



### 3.4. flags <`int`>

设置新建套接字文件描述符的标志位，当取值为 ‘0’ 时，*accept4( )* 退化为 *accept( )*

| No.  | 取值          | 用途                    | 备注                     |
| ---- | ------------- | ----------------------- | ------------------------ |
| 1    | SOCK_NONBLOCK | 置位标识位 *O_NONBLOCK* | 使用时与本表中其它项位与 |
| 2    | SOCK_CLOEXEC  | 置位标识位 *O_CLOEXEC*  | （同上）                 |
| 3    | ...           | ...                     |                          |



## 4. 返回值

- 函数执行成功后返回新建套接字的文件描述符

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[accept(2) — Linux manual page](https://man7.org/linux/man-pages/man2/accept.2.html)