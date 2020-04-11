
方法一：
	1，准备一张和lcd分辨率一样的图片logo.png
	2，在代码里device\qcom\common\display\logo目录下有一个脚本和readme文件，
		readme文件：

			The steps to generate a splash.img:
			1 sudo apt-get install python-imaging
			2 python ./logo_gen.py snapdragon.png
	3，把图片拷到当前目录，执行 python ./logo_gen.py snapdragon.png (当前目录会生成splash.img文件)
	4，用fastboot刷机

		adb reboot bootloader
		fastboot flash splash splash.img
		fastboot reboot

	4.1，或者把splash.img添加到刷机包里，修改rawprogram_unsparse.xml

	<program SECTOR_SIZE_IN_BYTES="512" file_sector_offset="0" filename="" label="splash"
	改成：
	<program SECTOR_SIZE_IN_BYTES="512" file_sector_offset="0" filename="splash.img" label="splash"



开机关机动画的修改：
vendor\qcom\proprietary\qrdplus\Extension\apps\BootAnimation