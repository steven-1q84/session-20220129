/*
** EPITECH PROJECT, 2022
** session-20220129
** File description: UDP套接字编程demo -- 服务端/客户端
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

#define _UDP_SERVER_ 10000
#define _UDP_CLIENT_ 10001

int main(int argc, char **argv) {

    /*
     *  套接字文件描述符：
     *  */
    int sockfd;

    /*
     *  服务端网络地址结构体
     *  */
    struct sockaddr_in addr_s[3];

    /*
     *  客户端网络地址结构体
     *  */
    struct sockaddr_in addr_c[3];

    /*
     *  服务器IP和端口号:
     *  */
    struct in_addr addr_sip[3];
    int addr_sport[3];

    /*
     *  发送和接收缓冲
     *      buf[0] -- 发送缓冲
     *      buf[1] -- 接收缓冲
     *  */
    char buf[2][200];

    /*
     *  UDP节点类型
     *  */
    int utype = 0;

    /*
     *  判断是否至少有3个入口参数
     */
    if(3 < argc) {
        /*
         *  根据第一个入口参数判断UPD节点类型
         *  */
        if(!strcmp(argv[1], "server")) {
            utype = _UDP_SERVER_;
        } else if (!strcmp(argv[1], "client")) {
            utype = _UDP_CLIENT_;
        } else {
            printf("failed to creadt udp node: \"%s\" is unrecognized, input \"server\" or \"client\" instead.\n", argv[1]);
            exit(1);
        }

        /*
         *  获取服务端IP和端口号:
         *    第二个入口参数按点分十进制的格式转换为服务端IP
         *    第三个入口参数转换为服务端端口号
         *  */
        inet_aton(argv[2], &addr_sip[0]);
        addr_sport[0] = atoi(argv[3]);

        #if 0
        if(5 < argc) {
            utype = 1000;
        }
        #endif
    } else {
        printf("failed to creadt udp node: not enough parameters.\n");
        exit(1);
    }

    /*
     *  获取套接字
     *  */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1) {
        perror("socket");
        exit(1);
    }

    /*
     *  设置服务器地址
     *  */
    memset(&addr_s[0], 0, sizeof(struct sockaddr_in));
    addr_s[0].sin_family      = AF_INET;
    addr_s[0].sin_port        = htons(addr_sport[0]);
    addr_s[0].sin_addr.s_addr = addr_sip[0].s_addr;

    if(utype == _UDP_SERVER_) {
        if(
            bind(
                sockfd
            ,   (struct sockaddr *)&addr_s[0]
            ,   sizeof(struct sockaddr)
            ) == -1
        ) {
            perror("bind");
            exit(1);
        }

        printf("udp server \"%s:%d\" is online.\n", inet_ntoa(addr_s[0].sin_addr), ntohs(addr_s[0].sin_port));
    } else if(utype == _UDP_CLIENT_) {
        printf("udp client to server \"%s:%d\" is online.\n", inet_ntoa(addr_s[0].sin_addr), ntohs(addr_s[0].sin_port));
    }

    while(1) {
        if(utype == _UDP_SERVER_) {
            int addr_len = sizeof(struct sockaddr_in);

            int res = recvfrom(
                sockfd
            ,   buf[1]
            ,   sizeof(buf[1]) - 1
            ,   0
            ,   (struct sockaddr *)&addr_c[0]
            ,   (socklen_t *)&addr_len
            );

            if(res == -1) {
                perror("recvfrom");
                exit(1);
            }

            buf[1][res] = '\0';
            printf("received from client \"%s:%d\": %s\n", inet_ntoa(addr_c[0].sin_addr), ntohs(addr_c[0].sin_port), buf[1]);

            sprintf(buf[0], "received %d bytes.", res);
            res = sendto(
                sockfd
            ,   buf[0]
            ,   strlen(buf[0])
            ,   0
            ,   (struct sockaddr *)&addr_c[0]
            ,   sizeof(struct sockaddr_in)//(socklen_t *)&addr_len
            );

            if(res == -1) {
                perror("sendto");
                exit(1);
            }

            if(!strcmp(buf[1], "quit")) {
                printf("client terminated session.\n");
                break;
            }
        } else if(utype == _UDP_CLIENT_) {
            int addr_len = sizeof(struct sockaddr_in);

            printf("input your words here: ");
            scanf("%s", buf[0]);
            printf("\n");
            
            int res = sendto(
                sockfd
            ,   buf[0]
            ,   strlen(buf[0])
            ,   0
            ,   (struct sockaddr *)&addr_s[0]
            ,   sizeof(struct sockaddr_in)//(socklen_t *)&addr_len
            );

            if(res == -1) {
                perror("sendto");
                exit(1);
            }

            res = recvfrom(
                sockfd
            ,   buf[1]
            ,   sizeof(buf[1]) - 1
            ,   0
            ,   (struct sockaddr *)&addr_s[0]
            ,   (socklen_t *)&addr_len
            );

            if(res == -1) {
                perror("recvfrom");
                exit(1);
            }

            buf[1][res] = '\0';
            printf("received from server \"%s:%d\": %s.\n", inet_ntoa(addr_s[0].sin_addr), ntohs(addr_s[0].sin_port), buf[1]);

            if(!strcmp(buf[0], "quit")) {
                printf("terminate session.\n");
                break;
            }
        }
    }

    exit(0);
}

//no more.
//----------------------------------------------------------------
