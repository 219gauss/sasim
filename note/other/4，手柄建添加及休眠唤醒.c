驱动位于该目录下
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\misc

sasin_gpio.c


修改Makefile
--- a/Android/kernel/drivers/misc/Makefile
+++ b/Android/kernel/drivers/misc/Makefile
@@ -68,3 +68,4 @@ obj-$(CONFIG_QPNP_MISC) += qpnp-misc.o
 obj-$(CONFIG_QCOM_LIQUID_DOCK) += qcom_liquid_dock.o
 obj-y                          += qcom/
 obj-$(CONFIG_UID_CPUTIME)      += uid_cputime.o
+obj-y                          += sasin_gpio.o


===========================================================================

休眠唤醒功能添加

#include <linux/pm.h>

static int sasin_gpio_probe(struct platform_device *pdev)
{
	...
	device_init_wakeup(&pdev->dev, 1);	//初始化并设置设备能唤醒系统
	...
}

static int sasin_gpio_remove(struct platform_device *pdev)
{
	...
	device_init_wakeup(&pdev->dev, 0);	//初始化并设置设备不能唤醒系统
	...
}	
	

//系统休眠的时候被调用
static int sasin_gpio_suspend(struct device *dev)
{
	struct sasin_data *pdata = dev_get_drvdata(dev);
	if (device_may_wakeup(dev)) {     //判断系统是否可以休眠
		enable_irq_wake(pdata->hook_irq);	 //使能中断唤醒功能
	}
	return 0;
}

//休眠唤醒的时候被调用
static int sasin_gpio_resume(struct device *dev)
{
	struct sasin_data *pdata = dev_get_drvdata(dev);
	if (device_may_wakeup(dev)) {
		disable_irq_wake(pdata->hook_irq);	//关闭中断唤醒功能
	}
	return 0;
}

