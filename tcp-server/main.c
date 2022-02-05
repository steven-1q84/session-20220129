/*
** EPITECH PROJECT, 2022
** session-20220129
** File description: TCP套接字编程demo -- 服务端
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

/*
 *  描述TCP连接的结构体 
 *  */
typedef struct TCP_CONNECTION {
    /*
     *  网络IP地址：
     *      addrs[0] -- 服务端
     *      addrs[1] -- 客户端
     *  */
    struct {
        struct sockaddr_in  sock_addr;  //用于绑定套接字文件的地址结构体
        struct in_addr      ip;         //IP地址
        int                 port;       //端口号
    } addrs[2];

    int sock_fd;    //套接字文件描述符

} TCP_CONNECTION_t;

/*
 *  reactor 线程伺服函数，使用建立连接的套接字描述符和客户端通信
 *  */
static void* _ProcReactor(void *arg) {
    TCP_CONNECTION_t *p             = (TCP_CONNECTION_t *)arg;
    int              sock_fd        = p->sock_fd;

    struct           in_addr ips[2] = {
        p->addrs[0].sock_addr.sin_addr
    ,   p->addrs[1].sock_addr.sin_addr
    };

    in_port_t                ports[2] = {
        p->addrs[0].sock_addr.sin_port
    ,   p->addrs[1].sock_addr.sin_port
    };

    char buf[2][256];

    printf(
        "%s:%d is receiving data from: %s:%d\n"
    ,   inet_ntoa(ips[0])
    ,   ntohs(ports[0])
    ,   inet_ntoa(ips[1])
    ,   ntohs(ports[1])
    );

    while(1) {
        /* 接收数据 */
        int res = read(sock_fd, buf[0], sizeof(buf[0]) - 1);
        if(res < 0) {
            perror("read");
            continue;
        } else if (res == 0) {
            printf("client %s:%d closed connection.\n"
            ,   inet_ntoa(ips[1])
            ,   ntohs(ports[1])
            );
            break;
        }

        /*  打印接收到的消息 */
        buf[0][res] = '\0';
        printf(
            "message from %s:%d: %s\n"
        ,   inet_ntoa(ips[1])
        ,   ntohs(ports[1])
        ,   buf[0]
        );

        /* 发送反馈消息 */
        sprintf(buf[1], "%d bytes received", res);
        write(sock_fd, buf[1], strlen(buf[1]));

        #if 0
        if(!strcmp(buf[0], "quit")) {
            break;
        }
        #endif
    }

    if(close(sock_fd) == -1) {
        perror("close");
    }

    return NULL;
}

int main(int argc, char **argv) {
    TCP_CONNECTION_t tcp_param; //TCP连接信息
    struct sockaddr_in *p_addr_s = &tcp_param.addrs[0].sock_addr;  //服务端地址结构句柄
    struct in_addr     *p_ip_s   = &tcp_param.addrs[0].ip;         //服务端IP句柄
    int    *p_port_s             = &tcp_param.addrs[0].port;       //服务端端口号句柄
    int    sock_fd_l;                                              //用于监听的套接字描述符

    /*
     *  获取监听用套接字文件描述符
     *  地址类型:   AF_INET ------ IPV4
     *  套接字类型: SOCK_STREAM -- TCP字节流
     *  */
    sock_fd_l = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd_l < 0) {
        perror("socket");
        return 1;
    }

    /*  判断入口参数个数 */
    if(3 < argc) {
        /*
         *  获取服务端IP和端口号
         *  - 将第一个入口参数按点分十进制的格式转换为服务端IP变量
         *  - 将第二个入口参数转换为整形数，赋给端口号变量
         *  */
        inet_aton(argv[1], p_ip_s);
        *p_port_s = atoi(argv[2]);
        //printf("server_addr: %s:%d\n", inet_ntoa(*p_ip_s), *p_port_s);
    } else {
        printf("failed to create TCP server: not enough parameters.\n");
        exit(1);
    }

    /*
     *  初始化服务器地址结构体
     *  */
    memset(p_addr_s, sizeof(struct sockaddr_in), 0);
    p_addr_s->sin_family = AF_INET;
    p_addr_s->sin_port = htons(*p_port_s);
    p_addr_s->sin_addr.s_addr = p_ip_s->s_addr;

    /*
     *  将服务端套接字与服务端地址结构体绑定
     *  */
    int res = bind(sock_fd_l, (struct sockaddr *)p_addr_s, sizeof(struct sockaddr));
    if(res < 0) {
        perror("bind");
        return 1;
    }

    /*
     *  开始监听
     *  */
    res = listen(sock_fd_l, 5);
    if(res < 0) {
        perror("listen");
        return 1;
    }

    printf(
        "%s:%d is lisening: \n"
    ,   inet_ntoa(p_addr_s->sin_addr)
    ,   ntohs(p_addr_s->sin_port)
    );

    while(1) {
        socklen_t addr_len;

        /*
         *  阻塞等待客户端三次握手完成
         *  返回用于传输数据的套接字
         *  */
        tcp_param.sock_fd = accept(
            sock_fd_l
        ,   (struct sockaddr *)&tcp_param.addrs[1].sock_addr
        ,   &addr_len
        );
    
        if(tcp_param.sock_fd == -1) {
            perror("accept");
            continue;
        }

        /*  创建 reactor 线程 */
        pthread_t tid_reactor;
        pthread_create(&tid_reactor, NULL, _ProcReactor, &tcp_param);
    }

    exit(0);
}

//no more.
//----------------------------------------------------------------
