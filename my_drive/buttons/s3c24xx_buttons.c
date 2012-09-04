#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <mach/regs-gpio.h>
#include <mach/hardware.h>

#define DEVICE_NAME  "buttons"
#define DEVICE_MAJOR  222

struct buttons_irq_desc{
    int irq;
    int pin;
    int flag;
    char *name;
};

struct buttons_irq_desc buttons_irqs [] = {
    { IRQ_EINT8,  S3C2410_GPG(0),  IRQ_TYPE_EDGE_FALLING,  "button1" },
    { IRQ_EINT11, S3C2410_GPG(3),  IRQ_TYPE_EDGE_FALLING,  "button2" },
    { IRQ_EINT13, S3C2410_GPG(5),  IRQ_TYPE_EDGE_FALLING,  "button3" },
    { IRQ_EINT14, S3C2410_GPG(6),  IRQ_TYPE_EDGE_FALLING,  "button4" },
    { IRQ_EINT15, S3C2410_GPG(7),  IRQ_TYPE_EDGE_FALLING,  "button5" },
    { IRQ_EINT19, S3C2410_GPG(11), IRQ_TYPE_EDGE_FALLING,  "button6" },
};

static DECLARE_WAIT_QUEUE_HEAD( button_wait_queue );
static volatile int is_press = 0;
static volatile int press_cnt [] = {0, 0, 0, 0, 0, 0};

static struct file_operations s3c24xx_buttons_fops = {
    .owner     =     THIS_MODULE;
    .open      =     s3c24xx_buttons_open;
    .release   =     s3c24xx_buttons_close;
    .read      =     s3c24xx_buttons_read;
};

static int __init s3c24xx_buttons_init( void )
{
    int ret;
    ret = register_chrdev( DEVICE_MAJOR, DEVICE_NAME, &s3c24xx_buttons_fops );

    if ( ret < 0 ){
        printk(DEVICE_NAME " can't register major number\n");
        return ret;
    }

    printk(DEVICE_NAME " initialized\n");
    return 0;
}

static int __exit s3c24xx_buttons_exit( void )
{
    unregister_chrdev( DEVICE_MAJOR, DEVICE_NAME );
}

static irqreturn_t buttons_interrupt(int irq, void *dev_id)
{
    volatile int *press_cnt = (volatile int *)dev_id;
    
    *press_cnt = *press_cnt + 1;
    is_press = 1; 
    wake_up_interruptible( &button_wait_queue );

    return IRQ_RETVAL( IRQ_HANDLED );
}

static int s3c24xx_buttons_open(struct inode *inode, struct file *file)
{
    int i, err;

    for ( i = 0; i < sizeof( buttons_irqs ) / sizeof( buttons_irqs[0] ); i++ ){
        err = request_irq( buttons_irqs[i].irq, buttons_interrupt, buttons_irqs[i].flag, \
                            buttons_irqs[i].name, (void *)&press_cnt[i]);

        if ( err < 0 )  break;
    }

    if ( err ){
        for ( ; i >= 0; i-- )
            free_irqs( buttons_irqs[i].irq, (void *)&press_cnt[i] );
        
        return -EBUSY;
    }
    
    return 0;
}
                

static int s3c24xx_buttons_close(struct inode *inode, struct file *file)
{
    int i;

    for ( i = 0; i < sizeof( buttons_irqs ) / sizeof( buttons_irqs[0] ); i++ ){
        free_irqs( buttons_irqs[i].irq, (void *)&buttons_irqs[i].press_time );
    }
    
    return 0;
}

   
static int s3c24xx_buttons_read(struct file *filp, char __user *buff, 
                                         size_t count, loff_t *offp)
{
    int err;

    if ( is_press == 0 ){
        if ( filp->flags & O_NONBLOCK )
            return -EAGIN;
        else
            wait_event_interruptible( button_wait_queue, is_press );
    }
    
    is_press = 0;

    err = copy_to_user( buff, (const void *)press_cnt, min( sizeof(press_cnt), count ) );
    memset((void *)press_cnt, 0, sizeof(press_cnt));

    return err ? -EFAULT : 0;
}

module_init( s3c24xx_buttons_init );
module_exit( s3c24xx_buttons_exit );

MODULE_AUTHOR( "0xdeadbeef" );
MODULE_DESCRIPTION( "S3C24xx BUTTONS Driver" );
MODULE_LICENSE( "GPL" );
        
