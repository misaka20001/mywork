#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>

int connect_retry(int socketfd,struct sockaddr *add,socklen_t len)
{
    #define MAX_SLEEP 100
    for (int i=1; i<MAX_SLEEP;i<<=1)
    {
        if (connect(socketfd,add,len)==0)
        {
            printf("accept success\n");
            return 0;
        }
        if (i<MAX_SLEEP/2)
            sleep(i);
    }
    return (-1);
}


int main()
{
    int socketfd;
    struct sockaddr_in add;
    add.sin_family=AF_INET;
    add.sin_port=htons(8082);
    inet_pton(AF_INET,"10.0.2.15",&add.sin_addr.s_addr);
    int fd=open("/home/shana/receive.c",O_WRONLY|O_CREAT);

    if ((socketfd=socket(AF_INET,SOCK_STREAM,0))<0)
        perror("sock error");

    if (connect_retry(socketfd,(struct sockaddr *)&add,sizeof(add))<0)
        perror("connect error");
    else{
        int n;
        char recvbuf[100],sendbuf[100];
        fgets(sendbuf,100,stdin);
        sendbuf[strlen(sendbuf)-1]=0;
        printf("%s\n",sendbuf);
        send(socketfd,sendbuf,strlen(sendbuf),0);
        printf("receive...\n");
        while ((n=recv(socketfd,recvbuf,100,0))>0)
            write(fd,recvbuf,n);

        if (n<0)
            perror("read error");
    }
    close(socketfd);
    return 0;
}
