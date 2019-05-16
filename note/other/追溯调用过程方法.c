
在函数里添加这一段：

	printk(KERN_ALERT"--------------[fyl] dump_stack start----------------");
	dump_stack();
	printk(KERN_ALERT"--------------[fyl] dump_stack end----------------");


