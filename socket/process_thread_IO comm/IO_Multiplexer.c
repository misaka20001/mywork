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

#define MAX_CONNSIZE 1000
typedef struct{
    int clientfd[MAX_CONNSIZE];
    struct sockaddr_in addr[MAX_CONNSIZE];
    fd_set read_set;
    fd_set ready_set;
    int maxfd;
    int maxi;
    int nready;
}pool;


int echo(int connfd,struct sockaddr_in addr);
int open_listenfd(int port);
void init_pool(int listenfd, pool *p);
void add_client(int connfd, struct sockaddr_in addr, pool *p);
void check_client(pool *p);

int main(int argc,char **argv)
{
    int listenfd,connfd,port;
    int socklen=sizeof(struct sockaddr_in);
    struct sockaddr_in addr;
    static pool pool;

    if (argc<2){
        fprintf(stderr,"usage: %s <port>\n",argv[0]);
        exit(0);
    }
    port=atoi(argv[1]);
    listenfd=open_listenfd(port);
    init_pool(listenfd,&pool);

    while (1){
        pool.ready_set=pool.read_set;
        pool.nready=select(pool.maxfd+1,&pool.ready_set,0,0,0);

        if ( FD_ISSET(listenfd,&pool.ready_set) ){
            connfd=accept(listenfd,(struct sockaddr*)&addr,&socklen);
            add_client(connfd,addr,&pool);
        }

        check_client(&pool);
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
    if ((n=recv(connfd,recvbuf,100,0))>0){
        write(1,recvbuf,n);
        return 1;
    }

    return -2;
}

void init_pool(int listenfd, pool *p)
{
    for (int i=0;i<MAX_CONNSIZE;i++){
        p->clientfd[i]=-1;
        bzero(p->addr[i]);
    }

    p->maxfd=listenfd;
    p->maxi=-1;

    FD_ZERO(&p->read_set);
    FD_SET(listenfd,&p->read_set);

}

void add_client(int connfd, struct sockaddr_in addr, pool *p)
{
    int i;
    (p->nready)--;

    for (i=0;i<MAX_CONNSIZE;i++){
        if ( p->clientfd[i]<0 ){
            p->clientfd[i]=connfd;
            p->addr[i]=addr;

            if (connfd>p->maxfd)
                    p->maxfd=connfd;

            if (i>p->maxi)
                    p->maxi=i;

            FD_SET(connfd,&p->read_set);
            break;
        }
    }
    if (i==MAX_CONNSIZE)
        perror("too many client");
}

void check_client(pool *p)
{
    int connfd;
    for (int i=0;(i<p->maxi && p->nready>0);i++){
        if ( (connfd=p->clientfd[i])>0 ){
            if ( FD_ISSET(connfd,&p->read_set) ){
                (p->nready)--;

                if (echo(connfd,p->addr[i])<0){
                    close(connfd);
                    FD_CLR(connfd,&p->read_set);
                    p->clientfd[i]=-1;
                    bzero(p->addr[i]);
                }
            }
        }
    }
}






