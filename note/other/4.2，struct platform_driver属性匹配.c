/*
	平台驱动和设备树的节点建立联系
	通过compatible属性进行匹配(使用dts)
*/


Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\include\linux\platform_device.h

例如：

	static struct of_device_id sasin_gpio_dt_match[] = {
		{ .compatible = "sasin_gpio",},
		{ },
	};

	static struct platform_driver gpio_power_driver = {
		.driver = {
			.name = "sasin_gpio",
			.owner = THIS_MODULE,
			.of_match_table = of_match_ptr(sasin_gpio_dt_match),	//不知道为什么要调这个函数
			#ifdef CONFIG_PM
			.pm	= &sasin_pm_ops,
			#endif
		},
		.probe = sasin_gpio_probe,
		.remove = sasin_gpio_remove,
	};


#define of_match_ptr(_ptr)	(_ptr)

结构体分析：

struct platform_driver {
	int (*probe)(struct platform_device *);							//匹配
	int (*remove)(struct platform_device *);						//移除
	void (*shutdown)(struct platform_device *);						//关机
	int (*suspend)(struct platform_device *, pm_message_t state);	//挂起
	int (*resume)(struct platform_device *);						//恢复
	struct device_driver driver;									//driver里的probe，remove，shutdown和platform_driver的是一样的
	const struct platform_device_id *id_table;						//2.6版本使用该值匹配
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


Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\base\platform.c
匹配机制：使用设备树时，调用of_driver_match_device匹配

static int platform_match(struct device *dev, struct device_driver *drv)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct platform_driver *pdrv = to_platform_driver(drv);

	/* Attempt an OF style match first */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then try ACPI style match */
	if (acpi_driver_match_device(dev, drv))
		return 1;

	/* Then try to match against the id table */
	if (pdrv->id_table)
		return platform_match_id(pdrv->id_table, pdev) != NULL;

	/* fall-back to driver name match */
	return (strcmp(pdev->name, drv->name) == 0);
}


Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\include\linux\of_device.h

static inline int of_driver_match_device(struct device *dev,
					 const struct device_driver *drv)
{
	return of_match_device(drv->of_match_table, dev) != NULL;
}



Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\of\device.c

const struct of_device_id *of_match_device(const struct of_device_id *matches,
					   const struct device *dev)
{
	if ((!matches) || (!dev->of_node))
		return NULL;
	return of_match_node(matches, dev->of_node);
}
EXPORT_SYMBOL(of_match_device);



Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\of\base.c
const struct of_device_id *of_match_node(const struct of_device_id *matches,
					 const struct device_node *node)
{
	const struct of_device_id *match;
	unsigned long flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	match = __of_match_node(matches, node);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	return match;
}
EXPORT_SYMBOL(of_match_node);



Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\of\base.c
//一般只比较compatible字符串，name和type一般为空
static
const struct of_device_id *__of_match_node(const struct of_device_id *matches,
					   const struct device_node *node)
{
	if (!matches)
		return NULL;

	while (matches->name[0] || matches->type[0] || matches->compatible[0]) {
		int match = 1;
		if (matches->name[0])
			match &= node->name
				&& !strcmp(matches->name, node->name);
		if (matches->type[0])
			match &= node->type
				&& !strcmp(matches->type, node->type);
		if (matches->compatible[0])
			match &= __of_device_is_compatible(node,
							   matches->compatible);
		if (match)
			return matches;
		matches++;
	}
	return NULL;
}



Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\of\base.c
static int __of_device_is_compatible(const struct device_node *device,
				     const char *compat)
{
	const char* cp;
	int cplen, l;

	cp = __of_get_property(device, "compatible", &cplen);
	if (cp == NULL)
		return 0;
	while (cplen > 0) {
		if (of_compat_cmp(cp, compat, strlen(compat)) == 0)
			return 1;
		l = strlen(cp) + 1;
		cp += l;
		cplen -= l;
	}

	return 0;
}


static const void *__of_get_property(const struct device_node *np,
				     const char *name, int *lenp)
{
	struct property *pp = __of_find_property(np, name, lenp);

	return pp ? pp->value : NULL;
}


static struct property *__of_find_property(const struct device_node *np,
					   const char *name, int *lenp)
{
	struct property *pp;
	if (!np)
		return NULL;
	for (pp = np->properties; pp; pp = pp->next) {
		if (of_prop_cmp(pp->name, name) == 0) {
			if (lenp)
				*lenp = pp->length;
			break;
		}
	}
	return pp;
}


/*
定义函数：int strcasecmp (const char *s1, const char *s2);
函数说明：strcasecmp()用来比较参数s1 和s2 字符串，比较时会自动忽略大小写的差异。
返回值：若参数s1 和s2 字符串相同则返回0。s1 长度大于s2 长度则返回大于0 的值，s1 长度若小于s2 长度则返回小于0 的值。
*/
#define of_compat_cmp(s1, s2, l)	strcasecmp((s1), (s2))



#define of_prop_cmp(s1, s2)		strcmp((s1), (s2))
