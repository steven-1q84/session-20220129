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

int main(int argc, char **argv) {

    /*
     *  套接字文件描述符：
     *  sockfd[0] -- 用于监听
     *  sockfd[1] -- 用于传输数据
     *  */
    int sockfd[2];

    /*
     *  网络地址结构体：
     *  addr[0]: 服务端
     *  addr[1]: 客户端
     *  */
    struct sockaddr_in addr[2];

    /*
     *  服务端IP和端口号
     *  */
    struct in_addr server_ip;
    int server_port;

    /*
     *  发送和接收缓冲
     *      buf[0] -- 发送缓冲
     *      buf[1] -- 接收缓冲
     *  */
    char buf[2][200];

    /*
     *  获取监听用套接字文件描述符
     *  地址类型:   AF_INET ------ IPV4
     *  套接字类型: SOCK_STREAM -- TCP字节流
     *  */
    sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd[0] < 0) {
        perror("socket");
        return 1;
    }

    /*
     *  获取服务端IP和端口号
     *  - 将第一个入口参数按点分十进制的格式转换为服务端IP变量
     *  - 将第二个入口参数转换为整形数，赋给端口号变量
     *  */
    inet_aton(argv[1], &server_ip);
    server_port = atoi(argv[2]);
    printf("server_addr: %s:%d\n", inet_ntoa(server_ip), server_port);

    /*
     *  初始化服务器地址结构体
     *  */
    memset(&addr[0], sizeof(struct sockaddr_in), 0);
    addr[0].sin_family = AF_INET;
    addr[0].sin_port = htons(server_port);
    addr[0].sin_addr.s_addr = server_ip.s_addr;

    /*
     *  将服务端套接字与服务端地址结构体绑定
     *  */
    int res = bind(sockfd[0], (struct sockaddr *)&addr[0], sizeof(struct sockaddr));
    if(res < 0) {
        perror("bind");
        return 1;
    }

    /*
     *  开始监听
     *  */
    res = listen(sockfd[0], 5);
    if(res < 0) {
        perror("listen");
        return 1;
    }

    while(1) {
        printf("lisening on: %s:%d\n", inet_ntoa(addr[0].sin_addr), ntohs(addr[0].sin_port));

        socklen_t addr_len;

        /*
         *  阻塞等待客户端三次握手完成
         *  返回用于传输数据的套接字
         *  */
        sockfd[1] = accept(
            sockfd[0]
        ,   (struct sockaddr *)&addr[1]
        ,   &addr_len
        );
    
        if(sockfd[1] == -1) {
            perror("accept");
            continue;
        }

        printf("receiving data from: %s:%d\n", inet_ntoa(addr[1].sin_addr), ntohs(addr[1].sin_port));

        while(1) {
            /* 接收数据 */
            int res = read(sockfd[1], buf[0], sizeof(buf[0]) - 1);
            if(res < 0) {
                perror("read");
                continue;
            }

            buf[0][res] = '\0';
            printf("received: %s\n", buf[0]);

            /* 发送数据 */
            sprintf(buf[1], "%d bytes received\n", res);
            write(sockfd[1], buf[1], strlen(buf[1]));

            if(!strcmp(buf[0], "quit")) {
                break;
            }
        }

        if(close(sockfd[1]) == -1) {
            perror("close");
            continue;
        }
    }

    exit(0);
}

//no more.
//----------------------------------------------------------------
