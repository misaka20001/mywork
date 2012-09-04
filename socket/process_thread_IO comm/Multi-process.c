#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sigchild_handler(int sig);
int echo(int connfd,struct sockaddr_in addr);
int open_listenfd(int port);

int main(int argc,char **argv)
{
    int listenfd,connfd,port;
    struct sockaddr_in addr;
    int socklen=sizeof(struct sockaddr_in);
    pid_t pid;

    if (argc<2){
        fprintf(stderr,"usage: %s <port>\n",argv[0]);
        exit(0);
    }
    port=atoi(argv[1]);

    signal(SIGCHLD, sigchild_handler);
    listenfd=open_listenfd(port);

    while (1){
        connfd=accept( listenfd, (struct sockaddr*)&addr, &len );
        if ( (pid=fork())<0 ){
            perror("fork");
            exit(0);
        }else if ( pid==0 ){
            close(listenfd);

            if (echo(connfd,addr)<0){
                close(connfd);
                exit(0);
            }

            close(connfd);
            exit(0);
        }else{
            close(connfd);
        }
    }

    return 0;
}

void sigchild_handler(int sig)
{
    while ( waitpid(-1,0,WNOHANG)>0 );
    return;
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
