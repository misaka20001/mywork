#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/stat.h>
#define READSIZE 100

int main()
{

    int socketfd;
    struct sockaddr_in add;
    struct stat stat_fd;
    add.sin_family=AF_INET;
    add.sin_port=htons(8082);
    add.sin_addr.s_addr=0;

    if ((socketfd=socket(AF_INET,SOCK_STREAM,0))<0)
        perror("sock error");

    if (bind(socketfd,(struct sockaddr *)&add,sizeof(add))<0)
        perror("bind error");

    listen(socketfd,10);
    bzero(&add,sizeof(add));
    int len=sizeof(add);

    int listenfd=accept(socketfd,(struct sockaddr *)&add,&len);
    char buf[100];
    if (inet_ntop(AF_INET,&add.sin_addr,buf,100)==0)
        perror("inet_ntop error");

    printf("accept from %s\n",buf);
    char buff[100];
    int l=recv(listenfd,buff,100,0);
    buff[l]=0;
    int fd=open(buff,O_RDONLY);
    if (fd<0)
        perror("open error");
    fstat(fd,&stat_fd);
    int size=stat_fd.st_size,nread;

    while (size>0)
    {
        if ((nread=read(fd,buf,READSIZE))<0)
            break;
        else if (nread==0)
            break;
        send(listenfd,buf,nread,0);
        size-=nread;
    }

    close(listenfd);
    close(socketfd);
    return 0;
}
