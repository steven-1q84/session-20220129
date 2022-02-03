/*
** EPITECH PROJECT, 2022
** session-20220129
** File description: TCP套接字编程demo -- 客户端
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
     *  客户端套接字文件描述符，只需要一个，用于连接和通信
     *  */
    int client_sockfd;

    /*
     *  服务器端网络地址结构体
     *  */
    struct sockaddr_in server_addr;

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
     *  获取套接字文件描述符
     *  地址类型:   AF_INET ------ IPV4
     *  套接字类型: SOCK_STREAM -- TCP字节流
     *  */
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_sockfd == -1) {
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

    /*
     *  初始化服务器地址结构体
     *  */
    memset(&server_addr, sizeof(struct sockaddr_in), 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = server_ip.s_addr;

    /*
     *  连接
     *  */
    if(
        connect(
            client_sockfd
        ,   (struct sockaddr *)&server_addr
        ,   sizeof(struct sockaddr_in)
        ) == -1
    ) {
        perror("connect");
        return 1;
    }

    printf(
        "connecting host: %s:%d\n"
    ,   inet_ntoa(server_addr.sin_addr)
    ,   ntohs(server_addr.sin_port)
    );

    while(1) {
        printf("input your words here:");
        scanf("%s", buf[0]);
        printf("\n");

        /* 发送消息 */
        if(
            write(client_sockfd, buf[0], strlen(buf[0]))
            == -1 
        ){
            perror("write");
            continue;
        }

        /* 接收消息 */
        int res = read(client_sockfd, buf[1], sizeof(buf[1]) - 1);
        if(res == -1) {
            perror("read");
            continue;
        } else if (res == 0) {
            printf("server closed tcp connection.\n");
            break;
        }

        buf[1][res] = '\0';

        printf("server replied: %s\n", buf[1]);

        if(!strcmp(buf[0], "quit")) {
            break;
        }
    }

    /* 关闭连接 */
    if(close(client_sockfd) == -1) {
        perror("close");
        return 1;
    }

    exit(0);
}

//no more.
//----------------------------------------------------------------
