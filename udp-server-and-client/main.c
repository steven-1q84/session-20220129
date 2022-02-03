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

int server_main(int argc, char **argv) {
    /*
     *  发送和接收缓冲
     *      buf[0] -- 发送缓冲
     *      buf[1] -- 接收缓冲
     *  */
    char buf[2][256];

    /*  UDP网络连接元素 */
    TCP_CONNECTION_t udp_server;

    /*  获取套接字 */
    udp_server.sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_server.sock_fd == -1) {
        perror("socket");
        return 1;
    }

    /*
     *  获取服务端IP和端口号:
     *    第二个入口参数按点分十进制的格式转换为服务端IP
     *    第三个入口参数转换为服务端端口号
     *  */
    inet_aton(argv[2], &udp_server.addrs[0].ip);
    udp_server.addrs[0].port = htons(atoi(argv[3]));

    /*
     *  设置服务器地址
     *  */
    memset(&udp_server.addrs[0].sock_addr, 0, sizeof(struct sockaddr_in));
    udp_server.addrs[0].sock_addr.sin_family      = AF_INET;
    udp_server.addrs[0].sock_addr.sin_port        = udp_server.addrs[0].port;
    udp_server.addrs[0].sock_addr.sin_addr.s_addr = udp_server.addrs[0].ip.s_addr;

    if(
        bind(
            udp_server.sock_fd
        ,   (struct sockaddr *)&udp_server.addrs[0].sock_addr
        ,   sizeof(struct sockaddr)
        ) == -1
    ) {
        perror("bind");
        return 1;
    }

    printf(
        "udp server \"%s:%d\" is online.\n"
    ,   inet_ntoa(udp_server.addrs[0].ip)
    ,   ntohs(udp_server.addrs[0].port)
    );

    while(1) {
        int addr_len = sizeof(struct sockaddr_in);

        /*  阻塞等待客户端的消息 */
        int res = recvfrom(
            udp_server.sock_fd
        ,   buf[1]
        ,   sizeof(buf[1]) - 1
        ,   0
        ,   (struct sockaddr *)&udp_server.addrs[1].sock_addr
        ,   (socklen_t *)&addr_len
        );

        if(res == -1) {
            perror("recvfrom");
            return 1;
        }

        /*  打印消息 */
        buf[1][res] = '\0';
        printf(
            "received from client \"%s:%d\": %s\n"
        ,   inet_ntoa(udp_server.addrs[1].sock_addr.sin_addr)
        ,   ntohs(udp_server.addrs[1].sock_addr.sin_port)
        ,   buf[1]
        );

        /*  反馈消息给客户端 */
        sprintf(buf[0], "received %d bytes.", res);
        res = sendto(
            udp_server.sock_fd
        ,   buf[0]
        ,   strlen(buf[0])
        ,   0
        ,   (struct sockaddr *)&udp_server.addrs[1].sock_addr
        ,   sizeof(struct sockaddr_in)
        );

        if(res == -1) {
            perror("sendto");
            return 1;
        }

        #if 0
        if(!strcmp(buf[1], "quit")) {
            printf("client terminated session.\n");
            break;
        }
        #endif
    }

    return 0;
}

int client_main(int argc, char **argv) {
    /*
     *  发送和接收缓冲
     *      buf[0] -- 发送缓冲
     *      buf[1] -- 接收缓冲
     *  */
    char buf[2][256];

    /*  UDP网络连接元素 */
    TCP_CONNECTION_t udp_client;

    /*  获取套接字 */
    udp_client.sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_client.sock_fd == -1) {
        perror("socket");
        return 1;
    }

    /*
     *  获取服务端IP和端口号:
     *    第二个入口参数按点分十进制的格式转换为服务端IP
     *    第三个入口参数转换为服务端端口号
     *  */
    inet_aton(argv[2], &udp_client.addrs[0].ip);
    udp_client.addrs[0].port = htons(atoi(argv[3]));

    /*
     *  设置服务器地址
     *  */
    memset(&udp_client.addrs[0].sock_addr, 0, sizeof(struct sockaddr_in));
    udp_client.addrs[0].sock_addr.sin_family      = AF_INET;
    udp_client.addrs[0].sock_addr.sin_port        = udp_client.addrs[0].port;
    udp_client.addrs[0].sock_addr.sin_addr.s_addr = udp_client.addrs[0].ip.s_addr;

    if(5 < argc) {
        /*
         *  获取服务端IP和端口号:
         *    第二个入口参数按点分十进制的格式转换为服务端IP
         *    第三个入口参数转换为服务端端口号
         *  */
        inet_aton(argv[4], &udp_client.addrs[1].ip);
        udp_client.addrs[1].port = htons(atoi(argv[5]));

        /*
         *  设置客户端地址
         *  */
        memset(&udp_client.addrs[1].sock_addr, 0, sizeof(struct sockaddr_in));
        udp_client.addrs[1].sock_addr.sin_family      = AF_INET;
        udp_client.addrs[1].sock_addr.sin_port        = udp_client.addrs[1].port;
        udp_client.addrs[1].sock_addr.sin_addr.s_addr = udp_client.addrs[1].ip.s_addr;

        if(
            bind(
                udp_client.sock_fd
            ,   (struct sockaddr *)&udp_client.addrs[1].sock_addr
            ,   sizeof(struct sockaddr)
            ) == -1
        ) {
            perror("bind");
            return 1;
        }

        printf(
            "udp client \"%s:%d\" to server \"%s:%d\" is online.\n"
        ,   inet_ntoa(udp_client.addrs[1].ip)
        ,   ntohs(udp_client.addrs[1].port)
        ,   inet_ntoa(udp_client.addrs[0].ip)
        ,   ntohs(udp_client.addrs[0].port)
        );
    } else {

        printf(
            "udp client \"?:?\" to server \"%s:%d\" is online.\n"
        ,   inet_ntoa(udp_client.addrs[0].ip)
        ,   ntohs(udp_client.addrs[0].port)
        );
    }

    while(1) {
        int addr_len = sizeof(struct sockaddr_in);

        /*  等待用户输入消息 */
        printf("input your words here: ");
        scanf("%s", buf[0]);
        //printf("\n");
            
        /*  发送消息到服务器 */
        int res = sendto(
            udp_client.sock_fd
        ,   buf[0]
        ,   strlen(buf[0])
        ,   0
        ,   (struct sockaddr *)&udp_client.addrs[0].sock_addr
        ,   sizeof(struct sockaddr_in)
        );

        if(res == -1) {
            perror("sendto");
            return 1;
        }

        /*  阻塞等待服务端反馈 */
        res = recvfrom(
            udp_client.sock_fd
        ,   buf[1]
        ,   sizeof(buf[1]) - 1
        ,   0
        ,   (struct sockaddr *)&udp_client.addrs[0].sock_addr
        ,   (socklen_t *)&addr_len
        );

        if(res == -1) {
            perror("recvfrom");
            exit(1);
        }

        /*  打印反馈消息 */
        buf[1][res] = '\0';
        printf(
            "received from server \"%s:%d\": %s.\n"
        ,   inet_ntoa(udp_client.addrs[0].ip)
        ,   ntohs(udp_client.addrs[0].port), buf[1]
        );

        /*  结束客户端 */
        if(!strcmp(buf[0], "quit")) {
            printf("terminate session.\n");
            break;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    int retval = 0;

    /*
     *  判断是否至少有3个入口参数
     */
    if(3 < argc) {
        /*
         *  根据第一个入口参数判断UPD节点类型
         *  */
        if(!strcmp(argv[1], "server")) {
            retval = server_main(argc, argv);
        } else if (!strcmp(argv[1], "client")) {
            retval = client_main(argc, argv);
        } else {
            printf("failed to creadt udp node: \"%s\" is unrecognized, input \"server\" or \"client\" instead.\n", argv[1]);
            retval = 1;
        }
    } else {
        printf("failed to create udp node: not enough parameters.\n");
        retval = 1;
    }

    exit(retval);
}

//no more.
//----------------------------------------------------------------
