#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int echo(int connfd,struct sockaddr_in addr);
int open_listenfd(int port);
void *thread(void *fd_addr);

typedef struct fd_addr{
    int connfd;
    struct sockaddr_in addr;
}*FdAddr;

int main(int argc,char **argv)
{
    int listenfd,port;
    int *connfd;
    int socklen=sizeof(struct sockaddr_in);
    struct sockaddr_in addr;
    struct sockaddr_in *connaddr;
    FdAddr fd_addr;
    pthread_t tid;

    if (argc<2){
        fprintf(stderr,"usage: %s <port>\n",argv[0]);
        exit(0);
    }
    port=atoi(argv[1]);
    listenfd=open_listenfd(port);

    while (1){
        connfd=malloc(sizeof(int));
        connaddr=malloc(sizeof(struct sockaddr_in));
        fd_addr=malloc(sizeof(struct fd_addr));

        *connfd=accept( listenfd, (struct sockaddr*)&addr, &socklen );
        *connaddr=addr;
        fd_addr->connfd=*connfd;
        fd_addr->addr=*connaddr;

        pthread_create(&tid,0,thread,fd_addr);
    }

    return 0;
}


int open_listenfd(int port)
{
    struct sockaddr_in addr;
    int socketfd,optval=1;

    if ((socketfd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket");
        return -1;
    }

    if (setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,\
                    (const void*)&optval,sizeof(int))<0){
        perror("setsockopt");
        return -1;
    }

    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=0;

    if (bind(socketfd, (struct sockaddr*)&addr, sizeof(addr))<0){
        perror("bind");
        return -1;
    }

    if (listen(socketfd,20)<0){
        perror("listen");
        return -1;
    }

    return socketfd;
}

int echo(int connfd,struct sockaddr_in addr)
{
    char ipaddr[20],recvbuf[100];
    int n;

    if (inet_ntop(AF_INET,&addr.sin_addr,ipaddr,20)==0){
        perror("inet_ntop");
        return -1;
    }

    printf("receive from %s...\n",ipaddr);
    while ((n=recv(connfd,recvbuf,100,0))>0)
        write(1,recvbuf,n);

    return 1;
}

void *thread(void *fd_addr)
{
    int connfd=((FdAddr)fd_addr)->connfd;
    struct sockaddr_in addr=((FdAddr)fd_addr)->addr;

    pthread_detach(pthread_self());
    free(fd_addr);

    echo(connfd,addr);
    close(connfd);

    return 0;
}



