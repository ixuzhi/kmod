#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");



static struct workqueue_struct *queue = NULL;

typedef struct {
	struct work_struct my_work;
	int data;
} my_work_t;

static void work_handler(struct work_struct *data){
	my_work_t *my_work = (my_work_t *)data;
	printk("work handler function,%d\n",my_work->data);
	kfree( (void *)data );
}
static int __init func_init(void)
{
	my_work_t *work1,*work2;
	printk("create single thread workqueue\n");
	queue  = create_singlethread_workqueue("hello_world");
	if (!queue){
		goto err;
	}
	
	work1 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
    if (work1) { 
      INIT_WORK( (struct work_struct *)work1, work_handler ); 
      work1->data = 1;
 
      queue_work( queue, (struct work_struct *)work1 );
 
    }
 
    /* Queue some additional work (item 2) */
    work2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
    if (work2) {
 
      INIT_WORK( (struct work_struct *)work2, work_handler );
 
      work2->data = 2;
 
      queue_work(queue, (struct work_struct *)work2 );
 
    }
	printk("create single thread workqueue 22\n");
	//schedule_work(&(work1.my_work));
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