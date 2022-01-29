# 套接字编程——TCP、UDP、本地通信

[TOC]

## 1. 系统调用

### 1.1. socket

```C
int socket(int domain, int type, int protocal);
```

- domain 

  > - 用途：指定协议族
  > - 取值范围：{AF_INET, AF_INET6, AF_LOCAL/AF_UNIX}
  >   - AF_INET：用于IPV4
  >   - AF_INET：用于IPV6
  >   - AF_LOCAL/AF_UNIX：用于本机

  

- type

  > - 用途：指定通信特点
  > - 取值范围：{SOCK_STREAM, SOCK_DGRAM, SOCK_RAW}
  >   - SOCK_STREAM：字节流
  >   - SOCK_DGRAM：数据包
  >   - SOCK_RAW：原始套接字

  

- protocol

  > - 用途：原本用于指定通信协议，现在已废弃
  > - 取值范围：0

  

### 1.2. bind



### 1.3. listen



### 1.4. accept



### 1.5. read



### 1.6. write



### 1.7. close



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

<img src="D:\git_root\repos\session-20220129\pics\001.png" style="zoom: 75%;" />

### 2.2. UDP



### 2.3. 本地通信