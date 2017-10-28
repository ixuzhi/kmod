/*
http://blog.csdn.net/myarrow/article/details/8090504
http://www.makelinux.net/ldd3/chp-7-sect-6

https://01.org/linuxgraphics/gfx-docs/drm/core-api/workqueue.html
http://www.cnblogs.com/joseph-linux/archive/2012/08/17/linux_workqueue.html

https://www.safaribooksonline.com/library/view/understanding-the-linux/0596005652/ch04s08.html

http://nano-chicken.blogspot.com/2010/12/linux-modules73-work-queue.html

https://www.ibm.com/developerworks/library/l-tasklets/index.html

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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");



static struct work_struct work;
static struct workqueue_struct *queue = NULL;

static void work_handler(struct work_struct *data){
	printk("work handler function\n");
}
static int __init func_init(void)
{
	printk("create single thread workqueue\n");
	queue  = create_singlethread_workqueue("hello_world");
	if (!queue){
		goto err;
	}
	printk("create single thread workqueue 11\n");
	INIT_WORK(&work,work_handler);
	//or
	
	printk("create single thread workqueue 22\n");
	schedule_work(&work);
	printk("create single thread workqueue 33\n");
	printk("create single thread workqueue end\n");
	return 0;
err:
	return -1;
}

static void __exit func_exit(void)
{
	destroy_workqueue(queue);
}


module_init(func_init);
module_exit(func_exit)