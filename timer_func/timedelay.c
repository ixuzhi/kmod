#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

struct timer_list mytimer;
struct timeval tv;
struct s_ad_switch {
	uint32_t aa;
	struct timeval tv;
};
struct s_ad_switch ad_switch[256];

static void myfunc(unsigned long data)
{
	struct timeval *tv1;
	tv1 = (struct timeval *)data;	
	printk("%lu,%lu\n",tv1->tv_sec,tv1->tv_usec);
    mod_timer(&mytimer,jiffies+10*HZ);
	do_gettimeofday(&tv);
	mytimer.data = (unsigned long)&tv;
}

static int __init func_init(void)
{
/*
    setup_timer(&mytimer,myfunc,(unsigned long)"hello,world");
    mytimer.expires = jiffies + 10*HZ;
    add_timer(&mytimer);
    return 0;
*/
	init_timer(&mytimer);
	do_gettimeofday(&tv);
	memset(ad_switch,0,sizeof(struct s_ad_switch));
	mytimer.data = (unsigned long)&tv;
	mytimer.function = myfunc;	
   	mytimer.expires = jiffies + 10*HZ;
   	add_timer(&mytimer);
   	return 0;

}

static void __exit func_exit(void)
{
    del_timer(&mytimer);
    printk("exit\n");
}



module_init(func_init);
module_exit(func_exit)

