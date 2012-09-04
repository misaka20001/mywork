#include "common.h"
#include "def.h"
#include "routine.h"
#include "debug.h"

static int recv_stream(int sock, void *buf, int size, int flag){

int current_len = 0, recvlen = 0;

while(current_len < size){
   recvlen = recv(sock, buf + current_len, size - current_len, flag);
   if(!recvlen){
    break;
   }
   else if(recvlen == -1){
    if(errno == EINTR) continue;
    fprintf(stderr, "Failed to recv() due to\n", strerror(errno));
    return -1;
   }
   current_len += recvlen;
}

return current_len;
}

int hget(int sock, struct sockaddr_in *servaddr, const char *dstpath, const char *servhost, const char *resurl){

int fd_dst;
char buf_recv[MAX_MSGLEN], buf_send[MAX_MSGLEN];
unsigned long len_curr = 0, len_total = 0, len_pack = 0;

/* now we have established the connection to serv
   * prepare to send download request
   */

memset(buf_send, MAX_MSGLEN, '\0');
sprintf(buf_send, "GET %s HTTP/1.0\r\nHost: %s:80\r\nAccept: */*\r\nUser-Agent: GeneralDownloadApplication\r\nConnection: close\r\n\r\n", resurl, servhost);
DEBUG_PRNF(("send:\n%s\n", buf_send));
if(send(sock, buf_send, strlen(buf_send), 0) == -1){
   perror("send");
   return -1;
}

/* here we check the destination path */
if(dstpath == NULL){
   if((fd_dst = open("./dlfile", O_RDWR | O_CREAT | O_EXCL, 00777)) == -1){
    printf("Failed to open destination file: %s\n", strerror(errno));
    return -1;
   }
}else{
   if((fd_dst = open(dstpath, O_RDWR | O_CREAT | O_EXCL, 00777)) == -1){
    printf("Failed to open destination file: %s\n", strerror(errno));
    return -1;
   }
}

memset(buf_recv, MAX_MSGLEN, 0);
len_pack = recv_stream(sock, buf_recv, MAX_MSGLEN, 0);

len_curr = header_scan(buf_recv, len_pack, MAX_MSGLEN, &len_total);
write(fd_dst, buf_recv + len_curr, len_pack - len_curr);

while(len_pack < len_total){
   memset(buf_recv, MAX_MSGLEN, '\0');
   if((len_curr = recv_stream(sock, buf_recv, MAX_MSGLEN, 0)) == -1)
    continue;
   write(fd_dst, buf_recv, len_curr);
   len_pack += len_curr;
}

close(fd_dst);

return 0;
}

unsigned long header_scan(const char *buf_recv, unsigned long len_curr, int max_buflen, unsigned long *len_total){

unsigned long len_header = 0, len_range = 0;
char buf_line[MAX_ARGLEN], buf_head[MAX_ARGLEN];
int match = 0;

memset(buf_line, MAX_ARGLEN, '\0');

while(match = sscanf(buf_recv + len_header, "%[=;\"A-Za-z0-9 /.:-]\r\n", buf_line)){
   DEBUG_PRNF(("line = %s, match = %d\n", buf_line, match));
   memset(buf_head, MAX_ARGLEN, '\0');
   len_header += strlen(buf_line) + 2;
   if(!len_range)
    sscanf(buf_line, "%s %ld", buf_head, &len_range);
   DEBUG_PRNF(("\thead = %s\n", buf_head));
   if(strcmp(buf_head, "Content-Length:"))
    len_range = 0;
   memset(buf_line, MAX_ARGLEN, '\0');
}

*len_total = len_range;
return len_header + 2;
}
