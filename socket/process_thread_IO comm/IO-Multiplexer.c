#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/types.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int echo(int connfd,struct sockaddr_in addr);
int open_listenfd(int port);
void command();

int main(int argc,char **argv)
{
    int listenfd,connfd,port;
    struct sockaddr_in addr;
    fd_set read_set,ready_set;
    int socklen=sizeof(struct sockaddr_in);

    if (argc<2){
        fprintf(stderr,"usage: %s <port>\n",argv[0]);
        exit(0);
    }
    port=atoi(argv[1]);
    listenfd=open_listenfd(port);

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO,&read_set);
    FD_SET(listenfd,&read_set);

    while (1){
        ready_set=read_set;
        select(listenfd+1,&ready_set,0,0,0);
        if ( FD_ISSET(STDIN_FILENO,&ready_set ) )
            command();
        if ( FD_ISSET(listenfd,&ready_set) ){
            connfd=accept(listenfd,(struct sockaddr*)&addr,&socklen);
            echo(connfd,addr);
        }
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

void command()
{
    char buf[100];

    if (fgets(stdin,buf,100)!=0){
        printf("%s",buf);
        return;
    }

    exit(0);
}
