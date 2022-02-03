#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SERV_PORT 8000

int main() {
    /* socket 文件描述符 */
    int sock_fd;

    /* 创建 UDP socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(1);
    }

    /* 设置 address */
    struct sockaddr_in addr_serv;
    int len;
    memset(&addr_serv, 0, sizeof(struct sockaddr_in));
    addr_serv.sin_family      = AF_INET;
    addr_serv.sin_port        = htons(SERV_PORT);
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    len                       = sizeof(addr_serv);

    /* 绑定socket */
    int res = bind(
        sock_fd
    ,   (struct sockaddr *)&addr_serv
    ,   sizeof(addr_serv)
    );

    if(res < 0) {
        perror("bind error:");
    exit(1);
    }

    int recv_num, send_num;
    char recv_buf[20], send_buf[20] = "i am a UDP server!";
    struct sockaddr_in addr_client;

    while(1){
        printf("server wait:\n");

        recv_num = recvfrom(
            sock_fd
        ,   recv_buf
        ,   sizeof(recv_buf)
        ,   0
        ,   (struct sockaddr *)&addr_client
        ,   (socklen_t *)&len
        );

        if(recv_num < 0) {
            perror("recvfrom error:");
            exit(1);
        }

        recv_buf[recv_num] = '\0';
        printf("server receive %d bytes: %s\n", recv_num, recv_buf);

        send_num = sendto(
                sock_fd
        ,   send_buf
        ,   recv_num
        ,   0
        ,   (struct sockaddr *)&addr_client
        ,   len
        );

        if(send_num < 0) {
            perror("sendto error:");
            exit(1);
        }
    }
}

/**
 * #inclde <stdio.h>
 * void perror(const char *s);
 */

/**
 * #include <sys/types.h>
 * #include <sys/socket.h>
 * int socket(int domain, int type, int protocol);
 */

/**
 * #include <unistd.h>
 * #include <stdlib.h>
 * void exit(int status);
 * void _exit(int status);
 */
