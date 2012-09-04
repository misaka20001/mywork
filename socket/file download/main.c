#include "common.h"
#include "def.h"
#include "protocol.h"
#include "routine.h"
#include "debug.h"

int main(int argc, char *argv[]){

struct hostent *target;
struct sockaddr_in servaddr;
int conn_fd;
char hostname[MAX_URLLEN], resurl[MAX_URLLEN], 
   sendbuf[MAX_MSGLEN], recvbuf[MAX_MSGLEN];
int flag_p;

if(argc < 2){
   printf("Usage: httpget {url}\n");
   exit(1);
}

memset(hostname, MAX_URLLEN, '\0');
memset(resurl, MAX_URLLEN, '\0');

sscanf(argv[1], "http://%[a-z0-9.]%s", hostname, resurl);

DEBUG_PRNF(("hostname = %s, resurl = %s\n", hostname, resurl));

if((target = gethostbyname(hostname)) == NULL){
   printf("DNS query of %s failed...abort.\n", hostname);
   exit(1);
}
DEBUG_PRNF(("hostaddr = %s\n", inet_ntoa(*(struct in_addr *)target -> h_addr)));

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)target -> h_addr));
servaddr.sin_port = htons(80);
bzero(&(servaddr.sin_zero), 8);

DEBUG_PRNF(("Verify = %s\n", inet_ntoa(servaddr.sin_addr)));

if((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
   perror("socket");
   exit(1);
}

if(connect(conn_fd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1){
   perror("connect");
   exit(1);
}

hget(conn_fd, &servaddr, (argc == 3) ? (argv[2]) : (NULL), hostname, resurl);
close(conn_fd);

return 0;
}
