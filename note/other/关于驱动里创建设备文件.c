
在驱动的probe函数中，一般会有这几个函数
class_create(owner, name):
	在/sys/class目录下回创建一个名为name的类（目录）

device_create
struct device *device_create(struct class *class, struct device *parent,
			     dev_t devt, void *drvdata, const char *fmt, ...)
在/sys/class/类/目录下创建一个设备（目录）

sysfs_create_group	或	device_creat_file
在/sys/class/类/设备/创建一些设备的属性（文件）
