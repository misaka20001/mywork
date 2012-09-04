#ifndef ROUTINE_H_INCLUDED
#define ROUTINE_H_INCLUDED

static int recv_stream(int sock, void *buf, int size, int flag);
int hget(int sock, struct sockaddr_in *servaddr, const char *dstpath, const char *servhost, const char *resurl);
unsigned long header_scan(const char *buf_recv, unsigned long len_curr, int max_buflen, unsigned long *len_total);

#endif // ROUTINE_H_INCLUDED
