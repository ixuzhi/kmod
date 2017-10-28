#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");


static void work_handler1(struct work_struct *data);
static void work_handler2(struct work_struct *data);
static void work_handler3(struct work_struct *data);

DECLARE_WORK(work1,work_handler1);
DECLARE_WORK(work2,work_handler2);

DECLARE_DELAYED_WORK(work3,work_handler3);
static struct workqueue_struct *queue1 = NULL;

static void work_handler1(struct work_struct *data){
	printk("work_handler1 function\n");
}

static void work_handler2(struct work_struct *data){
	printk("work_handler2 function\n");
}

static void work_handler3(struct work_struct *data){
	printk("work_handler3 function\n");
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
	//schedule_work(&work1);
	//schedule_work(&work2);
	queue_work(queue1,&work1);	
	queue_delayed_work(queue1,&work3,3);
	queue_work(queue1,&work2);
	//schedule_delayed_work
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