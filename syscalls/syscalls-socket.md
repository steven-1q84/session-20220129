# Linux系统调用：*socket*

[TOC]

## 1. 概要

```c
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```



## 2. 描述

创建通信端点，返回套接字文件描述符



## 3. 参数

### 3.1. *domain* < `int` >

定义用于通信的协议族，这些协议族定义在*<sys/socket.h>*中；

| No.  | 取值              | 用途         | 备注 |
| ---- | ----------------- | ------------ | ---- |
| 1    | AF_UNIX, AF_LOCAL | 本地通信     |      |
| 2    | AF_INET           | IPV4网络协议 |      |
| 3    | AF_INET6          | IPV6网络协议 |      |
| 4    | ...               | ...          |      |



### 3.2. *type* < `int` >

定义通信语义（semantics）

| No.  | 取值          | 用途                                 | 备注                     |
| ---- | ------------- | ------------------------------------ | ------------------------ |
| 1    | SOCK_STREAM   | 基于连接的、可靠的、双向的字节流队列 | TCP                      |
| 2    | SOCK_DGRAM    | 不依赖连接的、不可靠的、定长数据报   | UDP                      |
| 3    | SOCK_RAW      | 网络协议原始数据                     |                          |
| 4    | SOCK_NONBLOCK | 设置新文件描述符标识位*O_NONBLOCK*   | 使用时与本表中其它项位与 |
| 5    | SOCK_CLOEXEC  | 设置新文件描述符标识位*O_CLOEXEC*    | （同上）                 |
| 6    | ...           | ...                                  | ...                      |



### 3.3. *protocol* < `int` >

定义具体的协议；常用的协议族仅提供一种协议，因此这一项通常定义为0

## 4. 返回值

函数执行成功后返回新建套接字的文件描述符；函数执行失败返回'-1'，并将错误类型记录在*errono*中

## 4. 参考

[socket(2) — Linux manual page](https://man7.org/linux/man-pages/man2/socket.2.html)