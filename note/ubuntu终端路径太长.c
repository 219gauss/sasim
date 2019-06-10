
ubuntu 14.04终端路径太长

sxcompany@jianghuifeng:~/phy/sdk/msm8909_7.0_ch/Android$

解决：修改.bashrc

vim ~/.bashrc

PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
改为：
PS1='[${debian_chroot:+($debian_chroot)}\u@\h:\W]\$ '

修改后：[sxcompany@jianghuifeng:Android]$ 	//(只显示当前所在的目录)
