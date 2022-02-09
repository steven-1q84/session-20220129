# Linux系统调用：*htonl*

[TOC]

## 1. 概要

```c
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```



## 2. 描述

将32-bit和16-bit的数值在网络字节序和主机字节序之间转换

- `htonl()`、`htons()` 将输入参数转换为网络字节序返回
- `ntohl()`、`ntohs()`将输入参数转换为主机字节序返回



## 3. 参数

...



## 4. 返回值

...



## 4. 参考

[htonl(3p) — Linux manual page](https://www.man7.org/linux/man-pages/man3/htonl.3p.html)

