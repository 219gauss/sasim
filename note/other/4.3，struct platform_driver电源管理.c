/*
platform_driver和platform_driver里的driver 都有suspend，resume函数
*/


例子：

static const struct dev_pm_ops sasin_pm_ops = {
	.suspend	= sasin_gpio_suspend,
	.resume		= sasin_gpio_resume,
};

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



int platform_driver_register(struct platform_driver *drv)
{
	drv->driver.bus = &platform_bus_type;
	if (drv->probe)
		drv->driver.probe = platform_drv_probe;
	if (drv->remove)
		drv->driver.remove = platform_drv_remove;
	if (drv->shutdown)
		drv->driver.shutdown = platform_drv_shutdown;

	return driver_register(&drv->driver);
}
EXPORT_SYMBOL_GPL(platform_driver_register);

struct bus_type platform_bus_type = {
	.name		= "platform",
	.dev_attrs	= platform_dev_attrs,
	.match		= platform_match,
	.uevent		= platform_uevent,
	.pm		= &platform_dev_pm_ops,
};
EXPORT_SYMBOL_GPL(platform_bus_type);

static const struct dev_pm_ops platform_dev_pm_ops = {
	.runtime_suspend = pm_generic_runtime_suspend,
	.runtime_resume = pm_generic_runtime_resume,
	.runtime_idle = pm_generic_runtime_idle,
	USE_PLATFORM_PM_SLEEP_OPS
};

#ifdef CONFIG_PM_SLEEP
#define USE_PLATFORM_PM_SLEEP_OPS \
	.suspend = platform_pm_suspend, \
	.resume = platform_pm_resume, \
	.freeze = platform_pm_freeze, \
	.thaw = platform_pm_thaw, \
	.poweroff = platform_pm_poweroff, \
	.restore = platform_pm_restore,
#else
#define USE_PLATFORM_PM_SLEEP_OPS
#endif

//如果driver的pm定义了，就使用pm的suspend，否则就调用platform_driver的suspend
int platform_pm_suspend(struct device *dev)
{
	struct device_driver *drv = dev->driver;
	int ret = 0;

	if (!drv)
		return 0;

	if (drv->pm) {
		if (drv->pm->suspend)
			ret = drv->pm->suspend(dev);
	} else {
		ret = platform_legacy_suspend(dev, PMSG_SUSPEND);
	}
	return ret;
}


static int platform_legacy_suspend(struct device *dev, pm_message_t mesg)
{
	struct platform_driver *pdrv = to_platform_driver(dev->driver);
	struct platform_device *pdev = to_platform_device(dev);
	int ret = 0;

	if (dev->driver && pdrv->suspend)
		ret = pdrv->suspend(pdev, mesg);

	return ret;
}

