/*
http://blog.csdn.net/myarrow/article/details/8090504
http://www.makelinux.net/ldd3/chp-7-sect-6

https://01.org/linuxgraphics/gfx-docs/drm/core-api/workqueue.html

*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");

static struct work_struct work;
static struct workqueue_struct *queue = NULL;

static void work_handler(struct work_struct *data){
	printk("work handler function,%s\n",data->data);
}
static int __init func_init(void)
{
	printk("create single thread workqueue\n");
	queue  = create_singlethread_workqueue("hello_world");
	if (!queue){
		goto err;
	}
	printk("create single thread workqueue 11\n");
	//INIT_WORK(&work,work_handler);
	//or
	DECLARE_WORK(work,work_handler,"haha")
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