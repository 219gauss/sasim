/*
消息通知链调用流程

这个人很厉害：
https://www.cnblogs.com/armlinux/archive/2012/03/01/2396753.html

FBIOGET_VSCREENINFO: Used to get the variable screen information of the frame buffer
FBIOPUT_VSCREENINFO: Used to set variable screen parameters for the frame buffer
FBIOGET_FSCREENINFO: Used to get fixiable screen parameters for the frame buffer
FBIOPUTCMAP: 设置framebuffer的color map
FBIOGETCMAP: 获取framebuffer的color map
FBIOPAN_DISPLAY：按照参数var->xoffset 和var->yoffset平移frame buffer中的内容, 可以用在双buffer的切换
FBIOGET_CON2FBMAP和FBIOPUT_CON2FBMAP实在没看明白什么意思
FBIOBLANK：使能或者点亮frame buffer, 参数arg可以是POWERDOWN, NORMAL HSYNC_SUSPEND, VSYNC_SUSPEND UNBLANK



驱动层：fb_ioctl供用户空间使用

			do_fb_ioctl

				fb_blank

					fb_notifier_call_chain

						blocking_notifier_call_chain

							__blocking_notifier_call_chain

								notifier_call_chain

									nb->notifier_call(nb, val, v);	//提供了notifier_call接口（执行链表中所有notifier_call）



用户自己实现：							pdata->fb_notif.notifier_call = fb_notifier_callback;	//函数具体实现
										ret = fb_register_client(&pdata->fb_notif);				//将定义的fb_notif结构体添加到链表中


*/

/*

kernel\drivers\video\fbmem.c
				实现了供用户使用的各种接口

kernel\drivers\video\fb_notify.c
				对blocking消息通知链的封装

kernel\kernel\notifier.c
				提供了4种消息通知链的接口
											atomic_notifier_head
											blocking_notifier_head
											raw_notifier_head
											srcu_notifier_head

*/

#define FB_EARLY_EVENT_BLANK            0x10




static long fb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct fb_info *info = file_fb_info(file);

	if (!info)
		return -ENODEV;
	return do_fb_ioctl(info, cmd, arg);
}

static long do_fb_ioctl(struct fb_info *info, unsigned int cmd,
			unsigned long arg)
{
	...
	case FBIOBLANK:
		if (!lock_fb_info(info))
			return -ENODEV;
		console_lock();
		info->flags |= FBINFO_MISC_USEREVENT;
		ret = fb_blank(info, arg);
		info->flags &= ~FBINFO_MISC_USEREVENT;
		console_unlock();
		unlock_fb_info(info);
		break;
		...
}

int fb_blank(struct fb_info *info, int blank)
{	
	struct fb_event event;
	int ret = -EINVAL, early_ret;

 	if (blank > FB_BLANK_POWERDOWN)
 		blank = FB_BLANK_POWERDOWN;

	event.info = info;
	event.data = &blank;

	early_ret = fb_notifier_call_chain(FB_EARLY_EVENT_BLANK, &event);

	if (info->fbops->fb_blank)
 		ret = info->fbops->fb_blank(blank, info);

	if (!ret)
		fb_notifier_call_chain(FB_EVENT_BLANK, &event);	//遍历并执行链表中所有的的notifier_call
	else {
		/*
		 * if fb_blank is failed then revert effects of
		 * the early blank event.
		 */
		if (!early_ret)
			fb_notifier_call_chain(FB_R_EARLY_EVENT_BLANK, &event);
	}
 	return ret;
}


//往消息通知链中添加事件
int fb_notifier_call_chain(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(&fb_notifier_list, val, v);
}


int blocking_notifier_call_chain(struct blocking_notifier_head *nh,
		unsigned long val, void *v)
{
	return __blocking_notifier_call_chain(nh, val, v, -1, NULL);
}


int __blocking_notifier_call_chain(struct blocking_notifier_head *nh,
				   unsigned long val, void *v,
				   int nr_to_call, int *nr_calls)
{
	int ret = NOTIFY_DONE;

	/*
	 * We check the head outside the lock, but if this access is
	 * racy then it does not matter what the result of the test
	 * is, we re-check the list after having taken the lock anyway:
	 */
	if (rcu_dereference_raw(nh->head)) {
		down_read(&nh->rwsem);
		ret = notifier_call_chain(&nh->head, val, v, nr_to_call,
					nr_calls);
		up_read(&nh->rwsem);
	}
	return ret;
}


static int __kprobes notifier_call_chain(struct notifier_block **nl,
					unsigned long val, void *v,
					int nr_to_call,	int *nr_calls)
{
	int ret = NOTIFY_DONE;
	struct notifier_block *nb, *next_nb;

	nb = rcu_dereference_raw(*nl);

	while (nb && nr_to_call) {
		next_nb = rcu_dereference_raw(nb->next);

#ifdef CONFIG_DEBUG_NOTIFIERS
		if (unlikely(!func_ptr_is_kernel_text(nb->notifier_call))) {
			WARN(1, "Invalid notifier called!");
			nb = next_nb;
			continue;
		}
#endif
		ret = nb->notifier_call(nb, val, v);

		if (nr_calls)
			(*nr_calls)++;

		if ((ret & NOTIFY_STOP_MASK) == NOTIFY_STOP_MASK)
			break;
		nb = next_nb;
		nr_to_call--;
	}
	return ret;
}


static int fb_notifier_callback(struct notifier_block *self, unsigned long event, void *data)
{
	struct fb_event *evdata = data;
	int *blank;
	
	if (evdata && evdata->data && event == FB_EVENT_BLANK ){
		blank = evdata->data;
		printk("fb_notifier_callback blank=%d\n",*blank);
		if (*blank == FB_BLANK_UNBLANK) {			//屏幕唤醒时调用
			suspend_system = 0;
		}else if (*blank == FB_BLANK_POWERDOWN) {	//屏幕休眠时调用
			suspend_system = 1;
		}
	}
	return 0;
}

