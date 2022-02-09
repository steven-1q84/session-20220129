# Linux系统调用：*send*

[TOC]

## 1. 概要

```c
#include <sys/socket.h>

ssize_t recv(     int sockfd, void          *buf, size_t len, int flags);
ssize_t recvmsg(  int sockfd, struct msghdr *msg,             int flags);
ssize_t recvfrom( int sockfd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict src_addr, socklen_t *restrict addrlen);

#include <sys/socket.h>

ssize_t send(   int sockfd, const void          *buf, size_t len, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg,             int flags);
ssize_t sendto( int sockfd, const void          *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
```



## 2. 描述

将消息发送到套接字：

- `send()` 与 `write()` 的区别在于多了 *flags* 参数
- `send()` 用于建立连接的套接字，`send(sockfd, buf, len, flags)` 等同于`sendto(sockfd, buf, len, flags, NULL, 0)`
- 当 `sendto()` 用于面向连接的套接字类型（*SOCK_STREAM*、*SOCK_SEQPACKET*）时，参数 *dest_addr* 和 *addrlen* 会被忽略；否则这两个参数会被用于给出目标网络地址和地址长度
- 对于 `sendmsg()`，目标地址和地址大小由 *msg.msg_name* 和 *msg.msg_namlen* 给出
- 对于 `send()` 和 `sendto()` 函数会从参数 *buf* 中寻找长度为 *len* 个字节的消息；对于`sendmsg()` ，消息缓冲区地址由 *msg.iov* 给出



## 3. 参数

### 3.1. *sockfd* < `int` >

套接字文件描述符



### 3.2. *buf* <`void *`>

指针，指向数据接收缓冲区



### 3.3. *len* <`size_t `>

需要发送的消息长度



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
|      |               |                                                              |                    |



### 3.5. *dest_addr* <struct sockaddr *> 和 *addrlen* <socklen_t>

用于函数`sendto()`

*dest_addr* 指向用户提供的目的地网络地址

*addrlen* 给出地址数据长度



## 4. 返回值

- 函数执行成功后返回发送的消息字节数

- 函数执行失败返回'-1'，错误类型记录在 *errono* 中



## 4. 参考

[send(2) — Linux manual page](https://man7.org/linux/man-pages/man2/send.2.html)