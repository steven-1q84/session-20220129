# Linux系统调用：*inet*

[TOC]

## 1. 概要

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int inet_aton(const char *cp, struct in_addr *inp);
in_addr_t inet_addr(const char *cp);
in_addr_t inet_network(const char *cp);

char *inet_ntoa(struct in_addr in);
in_addr_t inet_lnaof(struct in_addr in);
in_addr_t inet_netof(struct in_addr in);
struct in_addr inet_makeaddr(in_addr_t net, in_addr_t host);

```



## 2. 描述

```c
int inet_aton(const char *cp, struct in_addr *inp);
```

- 将IPv4点分十进制格式的主机地址字符串 **cp* 转换为网络字节序的二进制数
- 转换结果存储在 *inp* 指向的结构体中 

- 转换成功函数返回 ‘1’，否则返回 ‘0’ 



```c
in_addr_t inet_addr(const char *cp);
```

- 功能类似`inet_aton()`
- 转换成功后返回网络字节序的二进制地址
- 转换失败时返回 ‘-1’， 而 ‘-1’ 是有效的IPv4地址（‘255.255.255.255’），会产生歧义，因此应避免此函数的使用



```c
in_addr_t inet_network(const char *cp);
```

- 功能类似`inet_aton()`
- 转换成功后返回**主机字节序**的二进制地址

- 该函数的问题同`inet_addr()`



```C
char *inet_ntoa(struct in_addr in);
```

- 将按网络字节序存储的主机地址 *in* 转换为IPv4点分十进制地址字符串
- 字符串分派在静态区，函数下次调用时会覆盖



```c
in_addr_t inet_lnaof(struct in_addr in);
```

- 将按网络字节序存储的主机地址 *in* 中的本地网络地址部分按主机字节序返回



```c
in_addr_t inet_netof(struct in_addr in);
```

- 将按网络字节序存储的主机地址 *in* 中的网络编号部分按主机字节序返回



```C
struct in_addr inet_makeaddr(in_addr_t net, in_addr_t host);
```

- `inet_lnaof()` 和 `inet_netof()` 的逆操作，将网络编号 *net* 和本地地址 *host* 合并后返回完整网络地址
- 返回值为网络字节序
- *net* 和 *host* 为主机字节序



## 3. 参数

### 3.1. *cp* < `const char * ` >

IPv4点分十进制地址字符串：

- *a.b.c.d*：四个数字从左到右依次对应32位二进制地址的每个字节
- *a.b.c*：*a*、*b* 对应二进制地址的前两个字节，*c* 是后两个字节对应的16位二进制数数值，用于定义B类网络地址
- *a.b*：*a* 对应第一个字节，*b* 是剩下的3个字节对应的24位二进制数数值，用于A类网络地址
- *a*：a被视作32位数值，直接存储到二进制地址中，不做字节序调整



### 3.2. *inp* <`struct in_addr *`>

指针，指向 32-bit 二进制网络地址

数据类型定义在`<netinet/in.h>`中:

```c
typedef uint32_t in_addr_t;

struct in_addr {
    in_addr_t s_addr;
};
```



### 3.3. ...



## 4. 返回值

...



## 4. 参考

[inet(3) — Linux manual page](https://man7.org/linux/man-pages/man3/inet_aton.3.html)