# 套接字编程——TCP、UDP、本地通信

[TOC]

## 1. 系统调用

### 1.1. socket

- 原型

```C
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocal);
```



- 功能

  > 



- 参数

  - domain

    > 用途：指定协议族
    >
    > 取值范围：{AF_INET, AF_INET6, AF_LOCAL/AF_UNIX}
    >
    > - AF_INET：用于IPV4
    > - AF_INET：用于IPV6
    > - AF_LOCAL/AF_UNIX：用于本机

  

  - type

    > 用途：指定通信特点
    >
    > 取值范围：{SOCK_STREAM, SOCK_DGRAM, SOCK_RAW}
    >
    > - SOCK_STREAM：字节流
    > - SOCK_DGRAM：数据包
    > - SOCK_RAW：原始套接字

    

  - protocol

    > 用途：原本用于指定通信协议，现在已废弃
    >
    > 取值范围：0

    

### 1.2. bind



### 1.3. listen



### 1.4. accept



### 1.5. close



### 1.6. read



### 1.7. write



### 1.8. recv, send

- 原型

  ```C
  #include <sys/socket.h>
  ssize_t recv(int sockfd, void *buf, size_t len, int flags);
  ```



- 功能

  > 从已完成连接的（*conneted*）套接字文件描述符中读取信息，与下面的调用相同：
  >
  > ```c
  > recevfrom(fd, buf, len, flags, NULL, 0);
  > ```
  >
  > 



- *flags*

  > 以下各项中的**一个**或**多个的位或**
  >
  > - MSG_CMSG_CLOEXEC 
  >
  >   （仅用于recvmsg()...）
  >
  >   
  >
  > - MSG_DONTWAIT (Linux 2.2+)
  >
  >   使能非阻塞式操作
  >
  >   
  >
  > - MSG_ERRQUEUE (Linux 2.2+)
  >
  >   ...
  >
  >   
  >
  > - MSG_OOB
  >
  >   接受带外（*out-of-band*）数据，这些数据在常用的数据流中不会被接收
  >
  >   
  >
  > - MSG_PEEK
  >
  >   从接收队列顶端接收数据不将其从队列中移除
  >
  >   
  >
  > - MSG_TRUNC (Linux 2.2+)
  >
  >   返回接收数据的真实长度，不管缓冲区够不够长
  >
  >   
  >
  > - MSG_WAITALL (Linux 2.2+)
  >
  >   线程一直阻塞直到接收完要求的数据长度，除非收到异步信号；对 *DATAGRAM* 套接字不起作用
  >
  > 



### 1.9. send()

- 原型

  ```c
  #include <sys/socket.h>
  ssize_t send(int sockfd, const void *buf, size_t len, int flags);
  ```



- 功能

  > 用于已连接的套接字，当 *flags* 参数为0时，send() 与 write() 功能相同
  >
  > 



- *flags*

  > 以下各项中的**一个**或**多个的位或**
  >
  > - MSG_CONFIRM (since Linux 2.3.15)
  >
  >   告诉链路层你已经从另一端获得了答复，不用ARP重复探测相邻节点；仅对 **SOCK_DGRAM** 和 **SOCK_RAW** 有效
  >
  >   
  >
  > - MSG_DONTROUTE
  >
  >   不使用网关发送数据包，通常用于诊断程序
  >
  >   
  >
  > - MSG_DONTWAIT (since Linux 2.2)
  >
  >   使能非阻塞操作
  >
  >   
  >
  > - MSG_EOR (since Linux 2.2)
  >
  >   终结一条记录？
  >
  >   
  >
  > - MSG_MORE (since Linux 2.4.4)
  >
  >   ...
  >
  >   
  >
  > - MSG_NOSIGNAL (since Linux 2.2)
  >
  >   在当面向字节流的套接字中，当另一端关闭连接时的不产生 **SIGPIPE** 信号
  >
  >   
  >
  > - MSG_OOB
  >
  >   发送带外（*out-of-band*）数据，用于 **SOCK_STREAM**
  >
  > 





## 2. 基本编程模式

### 2.1.TCP

> 1. 服务端和客户端分别初始化 **socket**，得到【套接字文件描述符】
> 2. 服务端调用 **bind** ，绑定【服务端IP】和【服务端端口号】
> 3. 服务端调用 **listen**，开始监听
> 4. 服务端调用 **accept** ，等待客户端连接，进程阻塞等待
> 5. 客户端调用 **connect** ，向【服务端IP:端口号】发起连接请求
> 6. 三次握手后服务端，服务端进程被唤醒，**accept** 返回【套接字文件描述符】
>    - 三次握手后返回的套接字用于传输，初始化的套接字用于监听，二者不是同一个文件
> 7. 客户端调用**write**写数据，服务端调用**read**读数据
> 8. 客户端调用**close**发送**EOF**，服务端读到**EOF**待数据处理完后调用**close**关闭连接

<img src="/home/steven/Workspace/session-20220129/pics/001.png" style="zoom:75%;" />



### 2.2. UDP



### 2.3. 本地通信



## 3. 其他系统调用和数据结构

- struct sockaddr_in

  > 依赖的头文件：
  >
  > ```c
  > #include <sys/socket.h>
  > #include <netinet/in.h>
  > #include <arpa/inet.h>
  > ```
  > 结构体成员：
  >
  > - sin_family
  >
  >   用途：指定协议族
  >
  >   取值范围：{AF_INET, AF_INET6, AF_LOCAL/AF_UNIX}
  >
  > - sin_port
  >
  >   用途：端口号（网络字节序，大端模式）
  >
  > - sin_addr
  >
  >   用途：保存IP地址信息（网络字节序）
  >
  > - sin_zero
  >
  >   用途：...



- atof(), atoi(), atol(), strtod(), strtol(), strtoul()

  > 用途：
  >
  > ​	atof()：将字符串转换为双精度浮点型值
  > ​	atoi()：将字符串转换为整型值
  > ​	atol()：将字符串转换为长整型值
  > ​	strtod()：将字符串转换为双精度浮点型值，并报告不能被转换的所有剩余数字
  > ​	strtol()：将字符串转换为长整值，并报告不能被转换的所有剩余数字
  > ​	strtoul()：将字符串转换为无符号长整型值，并报告不能被转换的所有剩余数字
  >
  > 依赖的头文件：
  >
  > ```c
  > #include <stdio.h>
  > #include <stdlib.h>
  > ```

  

- perror()

  > 依赖的头文件：
  >
  > ```c
  > #include <stdio.h>
  > ```
  >



- htonl(), htons(), ntohl(), ntohs()

  > 用途：字节序（大小端）转换
  >
  > 依赖的头文件：
  >
  > ```c
  > #include <arpa/inet.h>
  > ```
  >
  > 



- inet_aton(), inet_ntoa()

  > 用途：
  >
  > ​	inet_aton()：将点分十进制的网络IP字符串转换为in_addr网络字节序的长整形数
  >
  > ​	inet_ntoa()：（与上函数功能相反）
  >
  > 依赖的头文件
  >
  > ```c
  > #include <arpa/inet.h>
  > #include <stdio.h>
  > #include <stdlib.h>
  > ```
  >
  > 
  
  
