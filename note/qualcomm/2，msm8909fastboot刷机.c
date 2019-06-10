
1，刷lk
adb reboot bootloader
fastboot flash aboot <path to emmc_appsboot.mbn >
fastboot reboot

2，刷boot
adb reboot bootloader
fastboot flash boot <path to boot.img>
fastboot reboot

3，刷systemimage
adb reboot bootloader
fastboot flash system <path to system.img>
fastboot reboot

4，刷userdata
adb reboot bootloader
fastboot flash userdata <path to userdata.img>
fastboot reboot

5，recovery
adb reboot bootloader
fastboot flash recovery <path to recovery.img>
fastboot reboot

