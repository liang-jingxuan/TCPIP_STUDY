#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch[1024] = "GET / HTTP/1.1\n";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);//本机SOCKE,使用IPV4(AF_INET)，TCP协议（SOCK_STREAM）
    address.sin_family = AF_INET;//和对方通信时使用IPV4
    address.sin_addr.s_addr = htonl(INADDR_ANY);//对方的IP地址
    address.sin_port = htons(4000);//对方的端口号
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1)
    {
        perror("oops: client1");
        exit(1);
    }
    printf("Connect success!");
    write(sockfd, &ch, strlen(ch));
    printf("Write \"%s\" to %s\n",ch,inet_ntoa(address.sin_addr));
    read(sockfd, &ch, 1024);
    printf("char from server = %s\n", ch);
    close(sockfd);
    exit(0);
}
