/*************************************************************************
> File Name: server_1.c
> Author: 
> Mail: 
> Created Time: 2018年09月25日 星期二 21时38分54秒
************************************************************************/

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#define MAX_SIZE 1000

int socket_create(int port) {
    char *host;
    int socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Create");
        return -1;
    }
    struct sockaddr_in sever_addr;
    sever_addr.sin_family = AF_INET;
    sever_addr.sin_port = htons(port);
    sever_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (struct sockaddr *)&sever_addr, sizeof(sever_addr)) < 0) {
        perror("Bind");
        return -1;
    }
    if (listen(socket_fd, 20) < 0) {
        perror("Listen");
        return -1;
    }
    return socket_fd;
}

int main(int argc, char **argv) {
    int socket_fd = socket_create(6906), sockfd, pid;
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t len;
        if ((sockfd = accept(socket_fd, (struct sockaddr *)&client_addr, &len)) < 0) {
            perror("Accept");
            return -1;
        }
        /*
        accept接受链接,没接受到返回-1, 接收到后用进行fork()分身
        fork()返回值 == 0时, 表示他是子进程(sockfd)
        fork()返回值 > 0时, 表示他是父进程(socket_fd)
        */
        pid = fork();
        if (pid == 0) {
            close(socket_fd);
            while (1) {
                char buffer[MAX_SIZE] = {0};
                int cnt = recv(sockfd, buffer, sizeof(buffer), 0);
                /*
                recv返回值 == 0时, 表示客户端链接关闭
                recv返回值 < 0时, 出错
                recv返回值 > 0时, 接收到数据大小
                */
                if (cnt == 0) break;
                else if (cnt < 0) printf("Recv failed");
                else printf("%s\n", buffer);
            }
            close(sockfd);
            exit(1);//结束进程
        }
        else {
            close(sockfd);
        }
    }
    close(socket_fd);
    close(sockfd);

    return 0;
}
