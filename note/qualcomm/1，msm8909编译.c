1,安装编译环境

sudo apt-get install git-core gnupg flex bison gperf build-essential zip curl zlib1g-dev libc6-dev
lib32ncurses5-dev x11proto-core-dev libx11-dev lib32readline-gplv2-dev lib32z1-dev libgl1-mesa-dev
g++-multilib mingw32 tofrodos python-markdown libxml2-utils xsltproc

sudo apt-get install openjdk-7-jdk

//编译
source build/envsetup.sh
lunch msm8909-userdebug
make –jn (“n” means the thread numbers of CPU)

2，编译android的不同部分

编译lk：
make aboot -j8

路径：out/target/product/msm8909/
目标：emmc_appsboot.mbn


编译kernel：
make bootimage -j8	/	make kernel -j8(一般用这个)

路径：out/target/product/msm8909 
目标：boot.img


编译system：
make systemimage -jn

路径：out/target/product/msm8909
目标：system.img


编译userdata
make userdataimage -j8

路径：out/target/product/msm8909
目标：userdata.img


编译recovery
make recoveryimage -j8

路径：out/target/product/msm8909
目标：recovery.img
