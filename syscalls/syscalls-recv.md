# Linux系统调用：*recv*

[TOC]

## 1. 概要

```c
#include <sys/socket.h>

ssize_t recv(     int sockfd, void          *buf, size_t len, int flags);
ssize_t recvmsg(  int sockfd, struct msghdr *msg,             int flags);
ssize_t recvfrom( int sockfd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict src_addr, socklen_t *restrict addrlen);
```



## 2. 描述

从套接字中接收消息：

- 套接字可以是面向连接的也可以是无连接的

- `recv()` 与 `read()` 的区别在于多了 *flags* 参数

- `recv()` 通常用于建立连接的套接字，`recv(sockfd, buf, len, flags)` 等同于`recvfrom(sockfd, buf, len, flags, NULL, NULL)`

- 接收成功后返回数据字节数，缓冲区中不能接收的字节会根据套接字类型选择是否丢弃

- 如果没有消息线程会被阻塞，除非套接字是“非阻塞”类型的，后者函数返回 -1，并置位 *EAGAIN* 或 *EWOULDBLOCK* 错误

- `recvmsg()`使用结构体 *msghdr* 以减少直接提供的参数数量

  ...



## 3. 参数

### 3.1. *sockfd* < `int` >

套接字文件描述符



### 3.2. *buf* <`void *`>

指针，指向数据接收缓冲区



### 3.3. *len* <`size_t `>

需要接收的消息长度



### 3.4. *flags* <`int`>

 以下各项中的**一个**或**多个的位或**

| No.  | 取值          | 用途                                                         | 备注               |
| ---- | ------------- | ------------------------------------------------------------ | ------------------ |
| 1    | MSG_CONFIRM   | 告诉链路层你已经从另一端获得了答复，不用ARP重复探测相邻节点；仅对 **SOCK_DGRAM** 和 **SOCK_RAW** 有效 | since Linux 2.3.15 |
| 2    | MSG_DONTROUTE | 不使用网关发送数据包，通常用于诊断程序                       |                    |
| 3    | MSG_DONTWAIT  | 使能非阻塞操作，用于非阻塞套接字                             | since Linux 2.2    |
| 4    | MSG_EOR       | 终结一条记录？                                               | since Linux 2.2    |
| 5    | MSG_MORE      | ...                                                          | since Linux 2.4.4  |
| 6    | MSG_NOSIGNAL  | 在当面向字节流的套接字中，当另一端关闭连接时的不产生 **SIGPIPE** 信号 | since Linux 2.2    |
| 7    | MSG_OOB       | 发送带外（*out-of-band*）数据，用于 **SOCK_STREAM**          |                    |
| 8    | MSG_PEEK      | 从消息队列开头返回消息后将消息保留在队列中                   |                    |
| 9    | MSG_WAITALL   | 线程一直阻塞，直到接收到消息字节数达到参数 *len* 指定的数量  | since Linux 2.2    |
| 10   | MSG_TRUNC     | 返回接受到的数据报真实长度，即便数据报超出缓冲区大小         |                    |
|      |               |                                                              |                    |



### 3.5. *src_addr* <struct sockaddr *> 和 *addrlen* <socklen_t *>

用于函数`recvfrom()`

*src_addr* 指向用户提供的缓冲区，用于保存消息源地址

*addrlen* 指向用户提供的缓冲区，用于保存消息源地址数据的长度



## 4. 返回值

- 函数执行成功后返回接收到的消息字节数

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[recv(2) — Linux manual page](https://man7.org/linux/man-pages/man2/recv.2.html)