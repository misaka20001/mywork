#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
    int i;
    int ret;
    int fd;
    unsigned char press_cnt[6];
    
    fd = open("/dev/buttons", 0);  // ���豸
    if (fd < 0) {
        printf("Can't open /dev/buttons\n");
        return -1;
    }

    // ���Ǹ�����ѭ���������п�����read���������ߣ����а���������ʱ�����ŷ���
    while (1) {
        // �������������µĴ���
        ret = read(fd, press_cnt, sizeof(press_cnt));
        if (ret < 0) {
            printf("read err!\n");
            continue;
        } 

        for (i = 0; i < sizeof(press_cnt)/sizeof(press_cnt[0]); i++) {
            // ��������µĴ�����Ϊ0����ӡ����
            if ( press_cnt[i]-'0' )
                printf("K%d has been pressed %c times!\n", i+1, press_cnt[i]);
        }
    }
    
    close(fd);
    return 0;    
}

