
struct sasin_data {
	...
	struct notifier_block fb_notif;
	...
};

static int fb_notifier_callback(struct notifier_block *self, unsigned long event, void *data)
{
	struct fb_event *evdata = data;
	int *blank;
	
	if (evdata && evdata->data && event == FB_EVENT_BLANK ){
		blank = evdata->data;
		printk("fb_notifier_callback blank=%d\n",*blank);
		if (*blank == FB_BLANK_UNBLANK) {			
			suspend_system = 0;
		}else if (*blank == FB_BLANK_POWERDOWN) {
			suspend_system = 1;
		}
	}
	return 0;
}

static int sasin_gpio_probe(struct platform_device *pdev){

	...
	pdata->fb_notif.notifier_call = fb_notifier_callback;
	ret = fb_register_client(&pdata->fb_notif);
	if (ret) {
		dev_err(&pdev->dev, "Unable to register fb_notifier: %d\n", ret);
		goto err_fb_register;
	}
	...


err_fb_register:
	sysfs_remove_group(&dev->kobj, &sasin_attribute_group);
}

static int sasin_gpio_remove(struct platform_device *pdev)
{
	...
	if(fb_unregister_client(&pdata->fb_notif)) {
		dev_err(&pdev->dev, "Error occurred while unregistering fb_notifier.\n");
	}
	...
	return 0;
}

