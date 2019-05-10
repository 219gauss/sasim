
关于开机声音不根据手柄状态调整
（拿起手柄，声音从手柄出，放下手柄，手柄从喇叭出）


Z:\phy\sdk\qualcomm\device\qcom\common\rootdir\etc\init.qcom.rc

	on property:sys.boot_completed=1
	    write /sys/class/sasin_gpios/sasin_gpio92/state 0x100   

关于细节部分：
