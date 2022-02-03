/*
** EPITECH PROJECT, 2022
** udp_client
** File description:
** UDP client
*/

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DEST_PORT 8000
#define DEST_IP_ADDRESS "127.0.0.1"

int main() {
    /* socket 文件描述符 */
    int sock_fd;

    /* 创建 UDP socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_fd < 0) {
        perror("socket");
        exit(1);
    }

    /* 设置address */
    struct sockaddr_in addr_serv;
    int len;
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family      = AF_INET;
    addr_serv.sin_port        = htons(DEST_PORT);
    addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDRESS);
    len                       = sizeof(addr_serv);

    int recv_num, send_num;
    char recv_buf[20], send_buf[20] = "hey, who are you?";

    printf("client send: %s\n", send_buf);

    send_num = sendto(
        sock_fd
    ,   send_buf
    ,   strlen(send_buf)
    ,   0
    ,   (struct sockaddr *)&addr_serv
    ,   len
    );

    if(send_num < 0) {
        perror("sendto error:");
        exit(1);
    }

    recv_num = recvfrom(
        sock_fd
    ,   recv_buf
    ,   sizeof(recv_buf)
    ,   0
    ,   (struct sockaddr *)&addr_serv
    ,   (socklen_t *)&len
    );

    if(recv_num < 0) {
        perror("recvfrom error:");
        exit(1);
    }

    recv_buf[recv_num] = '\0';
    printf("client receive %d bytes: %s\n", recv_num, recv_buf);

    close(sock_fd);

    return 0;
}

//no more.
//

