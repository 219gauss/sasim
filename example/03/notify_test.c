/**
  * file : raw-notifer-chain.c  
  * owner: wuchengbing
  * data : 20190125 
  *
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/delay.h>
#include <linux/notifier.h>

// define notifier event type
#define EVENT_A 0x01    
#define EVENT_B 0x02

static RAW_NOTIFIER_HEAD(raw_chain_list);   //define notifer chain list

// define callback function
int raw_notifer_callback(struct notifier_block *nb, unsigned long event, void *v)
{
	switch (event) {
		case EVENT_A:
			printk("raw_notifer_callback running EVENT_A\n");
			break;
		case EVENT_B:
			printk("raw_notifer_callback running EVENT_B\n");
			break;
		default:
			break;
	}

	return NOTIFY_DONE;
}

// define notifier block
static struct notifier_block raw_notif = {
	.notifier_call = raw_notifer_callback,  //appoint notifier callback function
};

static int __init raw_notifier_init(void)
{
	printk("raw_notifier_chain_register\n\n");
	raw_notifier_chain_register(&raw_chain_list, &raw_notif);

	printk("raw_notifier call EVENT_A\n");
	raw_notifier_call_chain(&raw_chain_list, EVENT_A, NULL);

	printk("raw_notifier call EVENT_B\n");
	raw_notifier_call_chain(&raw_chain_list, EVENT_B, NULL);

	return 0;
}

static void __exit raw_notifier_exit(void)
{
	printk("raw_notifier_chain_unregister\n\n");
	raw_notifier_chain_unregister(&raw_chain_list, &raw_notif);
}

module_init(raw_notifier_init);
module_exit(raw_notifier_exit);

MODULE_AUTHOR("Wu_Being");
MODULE_LICENSE("GPL");



