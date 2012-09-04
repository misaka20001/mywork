#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_LED_ON    0
#define IOCTL_LED_OFF   1

void usage(char *exename)
{
    printf("Usage:\n");
    printf("    %s <led_no> <on/off>\n", exename);
    printf("    led_no = 1, 2, 3 or 4\n");
}

int main(int argc, char **argv)
{
    unsigned int led_no;
    int fd = -1;
    
    if (argc != 3)
        goto err;
        
    fd = open("/dev/leds", 0);  // 打开设备
    if (fd < 0) {
        printf("Can't open /dev/leds\n");
        return -1;
    }
    
    led_no = strtoul(argv[1], 0, 0) - 1;    // 操作哪个LED？
    if (led_no > 3)
        goto err;
    
    if (!strcmp(argv[2], "on")) {
        ioctl(fd, IOCTL_LED_ON, led_no);    // 点亮它
    } else if (!strcmp(argv[2], "off")) {
        ioctl(fd, IOCTL_LED_OFF, led_no);   // 熄灭它
    } else {
        goto err;
    }
    
    close(fd);
    return 0;
    
err:
    if (fd > 0) 
        close(fd);
    usage(argv[0]);
    return -1;
}

