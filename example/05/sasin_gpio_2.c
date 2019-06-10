/*
 *
 * drivers/misc/sasin_gpio.c - sasin_gpio driver
 *
 * Copyright (C) 2016 sim Inc.
 * Author: chuanzheng.xue <chuanzheng.xue@sim.com>
 *
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/types.h>
#include <linux/pm.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fsl_devices.h>
#include <asm/setup.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/stat.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/spinlock.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/err.h>
#include <linux/regulator/consumer.h>
#include <linux/fb.h>
#include <linux/cdev.h>
#include <linux/delay.h>

int val_old = -1;

static int suspend_system = 0;


struct sasin_data {
	struct cdev cdev;
    dev_t dev_t;
	struct device *dev;
	struct class *class;
	struct input_dev *input;
	struct notifier_block fb_notif;
	struct delayed_work dwork;
	
	int hook_gpio;
	int hook_irq;
	int led_gpio;
};


#define CTL_POWER_ON    "1"
#define CTL_POWER_OFF   "0"



static int sasin_report_value(struct input_dev *input, int state)
{
	input_event(input, EV_KEY, 496, !!state);
	input_sync(input);
	//printk("report data : 496, state = %d\n",state);
	//msleep(100);
	//input_event(input, EV_KEY, 496, 0);
	//input_sync(input);
	printk("report data : 496, state = %d\n",state);
	return 0;
}

static ssize_t sasin_ledctrl_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sasin_data *pdata = dev_get_drvdata(dev);
	//int gpio_state = gpio_get_value(sasin_gpio92);
	return sprintf(buf, "%d\n", gpio_get_value(pdata->led_gpio));
}

static ssize_t sasin_ledctrl_store(struct device *dev,struct device_attribute *attr, const char *buf, size_t size) {
	struct sasin_data *pdata = dev_get_drvdata(dev);
	long val;
	val = simple_strtol(buf, NULL, 16);
	if (val >= 0) {
		gpio_set_value(pdata->led_gpio, !!val);	
	} 
	return size;
}

static struct device_attribute sasin_ledctrl_dev = {
	.attr = {
		.name = "ledctrl",
		.mode = S_IRWXU|S_IRWXG|S_IRWXO,
	},
	.show = sasin_ledctrl_show,
	.store = sasin_ledctrl_store,
};


static ssize_t sasin_hook_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	sprintf(buf, "%d\n", val_old);
	return strlen(buf);
}

static ssize_t sasin_hook_store(struct device *dev,struct device_attribute *attr, const char *buf, size_t size) {
	long val;
	int gpio_val;
	struct sasin_data *pdata = dev_get_drvdata(dev);
	val = simple_strtol(buf, NULL, 16);
	if (val >= 0 && val == 0x100) {
		gpio_val = gpio_get_value(pdata->hook_gpio);
		if (!gpio_val) {
			val_old = gpio_val;
			sasin_report_value(pdata->input, !gpio_val);
		}
	} 
	return size;
}


static struct device_attribute sasin_hook_dev = {
	.attr = {
		.name = "state",
		.mode = S_IRWXU|S_IRWXG|S_IRWXO,
	},
	.show = sasin_hook_show,
	.store = sasin_hook_store,
};


static struct attribute *sasin_attributes[] = {
	&sasin_hook_dev.attr,
	&sasin_ledctrl_dev.attr,
	NULL
};


static struct attribute_group sasin_attribute_group = {
	.attrs = sasin_attributes
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

static void gpio_det_work_func(struct work_struct *work)
{
	unsigned int irqflags = IRQF_ONESHOT;
	int i = 0;
	struct delayed_work *delaywork = container_of(work, struct delayed_work, work);
	struct sasin_data *data = container_of(delaywork, struct sasin_data, dwork);


	int val[3];
	for(i = 0; i<3; i++){
		val[i] = gpio_get_value(data->hook_gpio);
		msleep(5);
	}
	if(val[0] != val[1] || val[0] != val[2]) {
		goto out;
	} 
	
	if(val[0] == val_old) {
		goto out;
	}
	val_old = val[0];
	if (val[0])
		irqflags |= IRQ_TYPE_EDGE_FALLING;
	else
		irqflags |= IRQ_TYPE_EDGE_RISING;

	irq_set_irq_type(data->hook_irq, irqflags);

	sasin_report_value(data->input, !val[0]);
out:
	enable_irq(data->hook_irq);
}

static irqreturn_t gpio_det_interrupt(int irq, void *dev_id)
{
	struct sasin_data *data = (struct sasin_data *)(dev_id);
	disable_irq_nosync(irq);
	if(suspend_system) {
			suspend_system = 0;
			input_report_key(data->input, KEY_WAKEUP, 1);
			input_report_key(data->input, KEY_WAKEUP, 0);
	}
	schedule_delayed_work(&data->dwork, msecs_to_jiffies(30));

	return IRQ_HANDLED;
}

static int sasin_dev_dt_parse(struct device_node *np, struct sasin_data *data) {
	int gpio, irq;
	int ret;
	
	gpio = of_get_named_gpio(np, "qcom,sasin_gpio92", 0);
	if (gpio < 0) {
		printk(" hook_gpio is not available \n");
		return -1;
	}
	ret = gpio_request(gpio, "sasin_gpio92");
	if(0 != ret) {
		printk("gpio request %d failed.", gpio);
		return ret;
	}
	gpio_direction_input(gpio);
	irq = gpio_to_irq(gpio);
	if (irq < 0) {
		ret = irq;
		printk("irq for gpio %d error(%d)\n", gpio, ret);
		gpio_free(gpio);
		return ret;
	}
	data->hook_irq = irq;
	data->hook_gpio = gpio;
	
	
	gpio = of_get_named_gpio(np, "qcom,sasin_gpio98", 0);
	if (gpio < 0) {
		printk("gpio is not available \n");
		return -1;
	}
	ret = gpio_request(gpio, "sasin_gpio98");
	if(0 != ret) {
		printk("gpio request %d failed.", gpio);
		return ret;
	}
	gpio_direction_output(gpio, 0);
	data->led_gpio = gpio;
	
	return 0;
}

/*设备文件操作方法表*/
static struct file_operations sasin_fops = {
.owner = THIS_MODULE,
};

static int sasin_gpio_probe(struct platform_device *pdev)
{
	int ret = 0;
	int valdef;
	//int val;
	unsigned int irqflags = IRQF_ONESHOT;
	struct sasin_data *pdata = NULL;
	struct device_node *np = pdev->dev.of_node;
	struct input_dev *input = NULL;
	struct device *dev;

	printk("enter sasin_gpio_probe \n");
	pdata = kzalloc(sizeof(struct sasin_data), GFP_KERNEL);
	if (!pdata) {
		printk("no memory for state\n");
		ret = -ENOMEM;
		goto err_alloc;
	}
	
	ret = sasin_dev_dt_parse(np, pdata);
	if(ret < 0) {
		goto err_dt_parse;
	}
	
	ret = alloc_chrdev_region(&pdata->dev_t, 0, 1, "sasin_gpios");
	if (ret) {
		printk("alloc dev_t failed\n");
		goto chrdev_err;
	}
	
	printk("alloc %s:%d:%d\n", "sasin_gpios", MAJOR(pdata->dev_t), MINOR(pdata->dev_t));
	cdev_init(&pdata->cdev, &sasin_fops);
	pdata->cdev.owner = THIS_MODULE;
	pdata->cdev.ops = &sasin_fops;
	
	ret = cdev_add(&pdata->cdev, pdata->dev_t, 1);
	if (ret) {
		printk("add dev_t failed\n");
		goto cdev_err;
	}
	
	pdata->class = class_create(THIS_MODULE, "sasin_gpios");
	if (IS_ERR(pdata->class)) {
		ret = PTR_ERR(pdata->class);
		printk("class_create err:%d\n", ret);
		goto class_err;
	}

	dev = device_create(pdata->class, NULL, pdata->dev_t, NULL, "sasin_gpio92");
	if (IS_ERR(dev)) {
                ret = PTR_ERR(dev);
		printk("device_create err:%d\n", ret);
                goto device_err;
        }
	pdata->dev = dev;

	input = input_allocate_device();
	if (!input) {    
                printk(KERN_ERR" Not enough memory\n");    
                ret = -ENOMEM;    
                goto err_input_alloc;
	}
	pdata->input = input;
	input->id.bustype = BUS_I2C;

	input->name ="sasin-gpio";
	__set_bit(EV_KEY, input->evbit);		
	__set_bit(496, input->keybit);
	__set_bit(KEY_WAKEUP, input->keybit);
	input->dev.parent = &pdev->dev;
	
	ret = input_register_device(input);
	if (ret) {
		printk("Unable to register input device %s\n", input->name);
		goto err_input_register;
	}



	ret = sysfs_create_group(&dev->kobj, &sasin_attribute_group);
	if(ret < 0) {
		goto err_sysfs;
	}
	
	pdata->fb_notif.notifier_call = fb_notifier_callback;
	ret = fb_register_client(&pdata->fb_notif);
	if (ret) {
		dev_err(&pdev->dev, "Unable to register fb_notifier: %d\n", ret);
		goto err_fb_register;
	}

	device_init_wakeup(&pdev->dev, 1);
	
	
	INIT_DELAYED_WORK(&pdata->dwork, gpio_det_work_func);
	
	platform_set_drvdata(pdev, pdata);
	dev_set_drvdata(&pdev->dev, pdata);
	dev_set_drvdata(dev, pdata);
	valdef = gpio_get_value(pdata->hook_gpio);
	if  (valdef)
		irqflags |= IRQ_TYPE_EDGE_FALLING;
	else
		irqflags |= IRQ_TYPE_EDGE_RISING;

	ret = request_irq(pdata->hook_irq, gpio_det_interrupt, irqflags, "sasin-gpio", pdata);
	if (ret < 0) {
		goto err_request;
	}
	printk("enter sasin_gpio_probe, ok \n");
	return ret;

err_request:
	fb_unregister_client(&pdata->fb_notif);
err_fb_register:
	sysfs_remove_group(&dev->kobj, &sasin_attribute_group);
err_sysfs:
	input_unregister_device(input);
err_input_register:
	input_free_device(input);
err_input_alloc:
   	device_destroy(pdata->class, pdata->dev_t);
device_err:
	class_destroy(pdata->class);
class_err:
	cdev_del(&pdata->cdev);
cdev_err:
	unregister_chrdev_region(pdata->dev_t, 1);
chrdev_err:
err_dt_parse:
	kfree(pdata);
err_alloc:
	return ret;
	
}

static int sasin_gpio_remove(struct platform_device *pdev)
{
	struct sasin_data *pdata = platform_get_drvdata(pdev);
	device_init_wakeup(&pdev->dev, 0);

	if(fb_unregister_client(&pdata->fb_notif)) {
		dev_err(&pdev->dev, "Error occurred while unregistering fb_notifier.\n");
	}
	sysfs_remove_group(&pdata->dev->kobj, &sasin_attribute_group);
	device_destroy(pdata->class, 0);
	input_unregister_device(pdata->input);
	input_free_device(pdata->input);
	class_destroy(pdata->class);
	kfree(pdata);

	return 0;
}

#ifdef CONFIG_PM
static int sasin_gpio_suspend(struct device *dev)
{
	struct sasin_data *pdata = dev_get_drvdata(dev);
	if (device_may_wakeup(dev)) {
		enable_irq_wake(pdata->hook_irq);	
	}

	return 0;
}

static int sasin_gpio_resume(struct device *dev)
{
	struct sasin_data *pdata = dev_get_drvdata(dev);
	if (device_may_wakeup(dev)) {
		disable_irq_wake(pdata->hook_irq);
	}
	return 0;
}

static const struct dev_pm_ops sasin_pm_ops = {
	.suspend	= sasin_gpio_suspend,
	.resume		= sasin_gpio_resume,
};
#endif

static struct of_device_id sasin_gpio_dt_match[] = {
	{ .compatible = "sasin_gpio",},
	{ },
};
MODULE_DEVICE_TABLE(of, sasin_gpio_dt_match);

static struct platform_driver gpio_power_driver = {
	.driver = {
		.name = "sasin_gpio",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(sasin_gpio_dt_match),
		#ifdef CONFIG_PM
		.pm	= &sasin_pm_ops,
		#endif
	},
	.probe = sasin_gpio_probe,
	.remove = sasin_gpio_remove,
};

static __init int gpio_power_init(void)
{
	return platform_driver_register(&gpio_power_driver);
}

static void __exit gpio_power_exit(void)
{
	platform_driver_unregister(&gpio_power_driver);
}

module_init(gpio_power_init);
module_exit(gpio_power_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sasin_gpio Driver");
MODULE_AUTHOR("cheng.zhou <cheng.zhou@sim.com>");


