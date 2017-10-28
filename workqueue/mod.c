/*
http://blog.csdn.net/myarrow/article/details/8090504
http://www.makelinux.net/ldd3/chp-7-sect-6

https://01.org/linuxgraphics/gfx-docs/drm/core-api/workqueue.html
http://www.cnblogs.com/joseph-linux/archive/2012/08/17/linux_workqueue.html

https://www.safaribooksonline.com/library/view/understanding-the-linux/0596005652/ch04s08.html

struct workqueue_struct *create_workqueue(const char *name);
struct workqueue_struct * workqueue_singlethread_workqueue(const char *name);

DECLARE_WORK(name,void(*function)(void *),void *data);
INIT_WORK(struct work_struct *work,void(*function)(void *),void *data);
PREPARE_WORK(struct work_struct *work,void(*function)(void *),void *data);

int queue_work(struct workqueue_struct *queue,struct work_struct *work);
int queue_delayed_work(struct workqueue_struct *queue,struct work_struct *work,unsigned long delay);

void destroy_workqueue(struct workqueue_struct *queue);

 对工作进行调度，即把给定工作的处理函数提交给缺省的工作队列和工作者线程。
 int schedule_work(struct work_struct *work);

 确保没有工作队列入口在系统中任何地方运行
 void flush_scheduled_work(void);

 延时执行一个任务
 int schedule_delayed_work(struct delayed_struct *work, unsigned long delay);

 从一个工作队列中去除入口;
 int cancel_delayed_work(struct delayed_struct *work);

*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");


static void work_handler1(struct work_struct *data);
DECLARE_WORK(work1,work_handler1);
DECLARE_DELAYED_WORK(work2,work2_handler)

static struct workqueue_struct *queue1 = NULL;

static void work_handler1(struct work_struct *data){
	printk("work_handler1\n");
}

static void work_handler2(struct work_struct *data){
	printk("work_handler2\n");
}


static int __init func_init(void)
{
	printk("create single thread workqueue\n");
	queue1  = create_singlethread_workqueue("hello_world");
	if (!queue1){
		goto err;
	}
	printk("create single thread workqueue 11\n");
	printk("create single thread workqueue 22\n");
	schedule_work(&work1);
	schedule_work(&work2);
	printk("create single thread workqueue 33\n");
	printk("create single thread workqueue end\n");
	return 0;
err:
	return -1;
}

static void __exit func_exit(void)
{
	destroy_workqueue(queue1);
}


module_init(func_init);
module_exit(func_exit)

/*

create workqueue:
编译时静态的创建
DECLARE_WORK(name,void(*func)(void *),void *data)
名称为name，带执行函数func，参数为data的work_struct

运行时通过指针创建
INIT_WORK(struct work_struct *work,void(*func)(void *),void *data)


schedule:
schedule_work
schedule_delayed_work

workqueue 初始化
create_workqueue
create_singlethread_workqueue
*/