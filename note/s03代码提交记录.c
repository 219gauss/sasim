

SIMCOM模块提交记录：
	
	分支：msm8909
					1，2019-04-13 屏，tp，摄像头驱动等等(太多了记不清)
					2，2019-05-25 修改来电led闪烁，TF识别
					3，2019-05-25 添加拨号前提醒拨号功能(连续的嘟嘟声)
					4, 2019-05-30 增加手柄拿起，启动拨号APP，放下，关闭APP功能(主要修改了驱动，framework，和dialer)
								  删除自注册软件
								  /*
								  device/qcom/msm8909/
								  frameworks/base/
								  kernel/
								  packages/apps/Dialer/
								  vendor/qcom/proprietary/
								  */
					5，2019-06-06 修复下拉状态栏的wifi信号强度与设置里wifi信号强度不同
								  修复快捷拨号M1~M4,重播键连续按下出现的bug
								  修复拨号键按下拨号，拨号apk出现崩溃现象
								  /*
									frameworks/base/
									packages/apps/Dialer/
									packages/apps/Settings/
									vendor/qcom/proprietary/
								  */
					6, 2019-06-26 /*
									device/qcom/msm8909/		修改视频通话接收不到对方视频(未完成)(system.prop)
									kernel/						优化了手柄键抬起放下的响应时间(sasin_gpio.c)
									packages/apps/Dialer/		修改点击视频通话图标时免提图标显示错误(CallButtonFragment.java)
																修改通话apk的通讯录不能保存联系人的bug(DialtactsActivity.java)
									vendor/qcom/proprietary/	修改自注册软件发送数据的编码(DeviceInfoPool.java)
																修改通话时喇叭和手柄的音频参数(原厂提供)(Handset_cal.acdb)(Speaker_cal.acdb)
								  */
					7，2019-07-03 /*(合并分支：s03_with_auto 0627和0701的补丁)
									build/						修改系统版本号(buildinfo.sh)
									device/qcom/msm8909/		添加系统测试apk/S03SystemTest		
									packages/apps/Settings/		修改系统内核版本
																在系统中增加S03SystemTest的SIM测试(AndroidManifest.xml)					
									frameworks/base/			在系统中增加S03SystemTest的TP测试(PhoneWindowManager.java)
									vendor/qcom/proprietary/	修改机器视频通话时接收不到数据的BUG(mct_pipeline.c)
								 */
					8，2019-07-03 /*
									build/						修改设备型号(改为默认型号)
									vendor/qcom/proprietary/	优化了在音量调大时对方免提通话时手柄出现的回声问题
								  */
					9，2019-07-10 /*
									frameworks/base/			添加快捷拨号键无号码是的提示
																添加按键音(按键按下时)
																修改系统默认声音
									packages/apps/Dialer/		优化视频通话时图形不能全屏问题
								  */
					10, 2019-08-16 /*(合并分支：s03_with_auto分支2019-07-27,2019-08-6的补丁)
									device/qcom/common/
									device/qcom/msm8909/
									frameworks/base/
									hardware/qcom/camera/
									kernel/
									packages/apps/Browser2/
									packages/apps/Dialer/
									packages/apps/FMRadio/
									packages/apps/Launcher3/
									packages/apps/MusicFX/
									packages/apps/QuickSearchBox/
									packages/apps/Settings/
									packages/apps/SnapdragonGallery/
									packages/services/Telephony/
									vendor/qcom/proprietary/
									*/
					11. 2019-09-06 /*
									packages/apps/Launcher3/	修复Launcher3设置壁纸崩溃问题
									*/

	分支：s03_with_auto(带自注册APP)
					1, 2019-05-30 合并msm8909分支(2019-05-30 的提交)
					2, 2019-05-30 添加自注册apk
								  /*
								  	device/qcom/msm8909/
								  	vendor/qcom/proprietary/
								  */
					3，2019-06-10 修复自注册apk AutoRegistration上报机器型号出现乱码的现象
								  /*
									vendor/qcom/proprietary/
								  */
					4, 2019-06-10 合并msm8909分支(2019-06-06 的提交)
					5，2019-06-12 修改系统默认设置中文，修改连接wifi时wifi图标出现的x号(国内版)
								  /*
									device/qcom/msm8909/
									frameworks/base/
									vendor/qcom/proprietary/
								  */
					6, 2019-06-26 /*
									device/qcom/msm8909/		修改系统默认中文设置，(msm8909.mk)
																修改视频通话接收不到对方视频(未完成)(system.prop)
									frameworks/base/			修改wifi图标出现的x号(NetworkMonitor.java)
									kernel/						优化了手柄键抬起放下的响应时间(sasin_gpio.c)
									packages/apps/Dialer/		修改点击视频通话图标时免提图标显示错误(CallButtonFragment.java)
																修改通话apk的通讯录不能保存联系人的bug(DialtactsActivity.java)
									vendor/qcom/proprietary/	修改自注册软件发送数据的编码(DeviceInfoPool.java)
																修改通话时喇叭和手柄的音频参数(原厂提供)(Handset_cal.acdb)(Speaker_cal.acdb)
								  */
					7，2019-06-27 /*
									build/						修改系统版本号(buildinfo.sh)
									device/qcom/msm8909/		添加系统测试apk/S03SystemTest		
									packages/apps/Settings/		修改系统内核版本					
								  */
					8,2019-07-01 /*
									device/qcom/msm8909/		去除之前添加的摄像头调试代码(system.prop)
									frameworks/base/			在系统中增加S03SystemTest的TP测试(PhoneWindowManager.java)
									packages/apps/Settings/		在系统中增加S03SystemTest的SIM测试(AndroidManifest.xml)
									vendor/qcom/proprietary/	修改机器视频通话时接收不到数据的BUG(mct_pipeline.c)
								 */
					9，2019-07-03 /*
									build/						修改设备型号(去掉中间的中文点)
									vendor/qcom/proprietary/	优化了在音量调大时对方免提通话时手柄出现的回声问题
								  */
					10，2019-07-10 /*(合并msm8909分支(2019-07-10 的提交)
									frameworks/base/			添加快捷拨号键无号码是的提示
																添加按键音(按键按下时)
																修改系统默认声音
									packages/apps/Dialer/		优化视频通话时图形不能全屏问题
								  */
					11, 2019-07-27 /*
									device/qcom/common/			去除收音机apk

									device/qcom/msm8909/		修改方向左键为左键功能(原为删除功能)
																预置谷歌输入法，谷歌浏览器

									frameworks/base/			快捷拨号键4:修改为删除和返回功能(只针对Activity)--->Activity.java
																谷歌输入法:系统中所有的输入法设置为可用--->InputMethodUtils.java
																wifi热点:设置热点按键广播诶受保护的广播--->AndroidManifest.xmls
																谷歌输入法:设置默认输入法为谷歌输入法--->defaults.xml,DatabaseHelper.java
																在状态栏显示通话音量图标--->VolumeDialog.java
																禁止输入法随语言切换而改变--->InputMethodManagerService.java
																(为了兼容sip版Launcher，屏蔽部分按键，暂定)PhoneWindowManager.java

									hardware/qcom/camera/		摄像头的拍照录像的预览左右镜像(前摄改成后摄)--->QCamera2Factory.cpp

									kernel/						0310和2145摄像头改为后摄配置--->msm8909-camera-sensor-mtp.dtsi
																修改方向左键键值为左键(原删除),增加敦泰tp节点--->msm8909-mtp.dtsi
																增加敦泰Tp驱动--->Makefile (新增加)drivers/input/touchscreen/ft6336/

									packages/apps/Browser2/		删除默认浏览器的Android.mk--->Android.mk

									packages/apps/Dialer/		快捷拨号键4:增加对快捷拨号设置dialog的监听--->SpeedDialListActivity.java
																修复搜索联系人时输入法动隐藏的BUG--->DialpadFragment.java

									packages/apps/FMRadio/		去除收音机apk

									packages/apps/Launcher3/	去除搜索框--->qsb_default_view.xml,QsbContainerView.java,Workspace.java

									packages/apps/QuickSearchBox/去除搜索apk--->Android.mk

									packages/apps/Settings/		(已撤回)
																注册两个静态广播(打开热点，修改系统字体)--->AndroidManifest.xml
																修改系统字体--->DisplaySettings.java,AccessibilitySettings.java,ToggleFontSizePreferenceFragment.java,FontScaleReceiver.java
																快捷拨号键4:增加对wifi热点设置dialog的监听--->WifiApDialog.java
																快捷拨号键4:增加对wifimima设置dialog的监听--->WifiConfigController.java,WifiConfigUiBase.java,WifiDialog.java
																打开热点--->WifiApReceiver.java

									vendor/qcom/proprietary/	去除安全中心apk--->csm/Android.mk
																0310摄像头改为后摄配置--->gc0310_lib.c
																2145摄像头改为后摄配置--->gc2145_8909_lib.c
																去除移动更新客户端--->prebuilt_HY11/target/product/msm8909/Android.mk
																						qrdplus/Global/Regional/EUCommon/products.mk
																						qrdplus/Global/Regional/LatamAMX/products.mk
																						qrdplus/Global/Regional/LatamTelefonica/products.mk
																去除记事本apk--->qrdplus/Extension/apps/NotePad/Android.mk
									*/
					12，2019-08-6 /*
									frameworks/base/			优化删除返回键功能
																优化默认字体最大功能

									packages/apps/MusicFX/		修改音效布局为横屏

									packages/apps/Settings/		优化上一版的默认字体功能

									packages/apps/SnapdragonGallery/	优化长按图片程序崩溃问题

									packages/services/Telephony/	去除设置总的运营商设置选项(点击会崩溃)

									vendor/qcom/proprietary/	优化M4键对来电转接对话框的支持
									*/
					13. 2019-08-16 /*(暂时提交)
									device/qcom/common/
									device/qcom/msm8909/
									frameworks/base/
									frameworks/opt/net/ethernet/
									kernel/
									packages/apps/Launcher3/
									packages/apps/Settings/
									vendor/qcom/proprietary/
									*/
					14. 2019-09-06 /*
									kernel/						修复摄像头预览方向
									packages/apps/Launcher3/	修复Launcher3设置壁纸崩溃问题
									*/
					15. 2019-10-08 /*
									development/				去除home(apk)
									device/qcom/msm8909/		添加Launcher(4G+VOIP)和墨迹天气
									frameworks/base/			更换系统默认壁纸--->default_wallpaper.png
																默认打开apk所有权限--->DefaultPermissionGrantPolicy.java
																去除按键功能--->PhoneWindowManager.java
									hardware/qcom/camera/		修改摄像头左右预览镜像
									kernel/						gc0310和gc2145节点改回前摄配置
									packages/apps/Dialer/		增加广播，4G通话时，VOIP来电，放下手柄挂断电话
									packages/apps/Launcher2/	去除Launcher2(apk)
									packages/apps/Launcher3/	去除Launcher3(apk)
									vendor/qcom/proprietary/	gc0310和gc2145节点改回前摄配置
									*/
					16. 2019-10-09 /*
									frameworks/base/			SystemUI添加截图功能
									*/
					17. 2019-10-10 /*
									device/qcom/common/			修改蓝牙默认名称
									frameworks/base/			重新排列SystemUI的状态栏的快捷图标
									vendor/qcom/proprietary/	去除MBN测试apk
									*/
					18. 2019-10-14 /*
									frameworks/base/			修改4G+VOIP的包名
									*/
					19, 2019-10-18 /*
									device/qcom/msm8909/		修改4G+VOIP的文件名和去除自注册apk
									frameworks/base/			默认打开设置->安全->未知来源
									vendor/qcom/proprietary/	去除自注册apk
									*/
					20，2019-10-24 /*
									packages/inputmethods/LatinIME	去除android默认的输入法
									*/
					21，2019-10-29 /*
									hardware/qcom/camera/
									kernel/
									vendor/qcom/proprietary/	新板子摄像头修改(以后的版本都使用新板子后摄摄像头)
									packages/apps/Dialer/		修改拨号设置的提示音和震动点击没反应的现象-->AndroidManifest.xml
																去除拨号测试apk-->Android.mk
									*/
					22, 2019-11-05 /*
									packages/apps/SnapdragonGallery	修复在骁龙图库编辑图片弹出的提示框不能取消的问题(BUG)
									*/
					23, 2019-11-12 /*
									frameworks/base/			修复开机时出现的概率触摸卡死(使用了自己编写的Launcher)(无效)
									*/
					24，2019-12-11	/*
									device/qcom/common/			修复TP卡死问题
									frameworks/base/			取消对拨号apk的操作，按下按键发出广播
																取消上一个提交
									kernel/						修复TP卡死问题
									vendor/qcom/proprietary/	添加一个apn
									*/
					25，2019-12-12	/*
									device/qcom/common/			兼容TP(修改节点权限)
									frameworks/base/			跟换Launcher包名
																修改一个语法错误
									hardware/qcom/camera/		兼容TP(判断是否有摄像头)
									kernel/						兼容TP(根据是否有摄像头调整TP方向)
									*/
					26，2019-12-19 /*
									frameworks/base/			恢复手柄键对拨号apk的操作，取消按键音
									*/
					27, 2019-12-25 /*
									device/qcom/msm8909/		增加壁纸apk
									packages/apps/Contacts/		优化联系人选择4G/VOIP拨号
									packages/apps/ContactsCommon/修改联系人选项高度
									packages/apps/WallpaperPicker/增加默认壁纸
									*/
					28，2019-12-25 /*
									返回/删除键(M4)改为快捷拨号4键
									frameworks/base/
									packages/apps/Dialer/
									packages/apps/Settings/
									*/
					29，2019-12-28 /*
									device/qcom/common/			温度节点，手柄节点处理
									frameworks/base/			修改默认壁纸
									hardware/qcom/sensors/		增加温度sensor
									kernel/						手柄兼容gpio99口，上报温度sensor数据
									packages/apps/WallpaperPicker/修改壁纸
									vendor/qcom/proprietary/	去掉没有SIM卡提示
									*/
					30，2019-12-30 /*
									packages/apps/DeskClock/	修改时钟小部件字体大小
									*/
					31，2020-01-09 /*
									frameworks/base/			手柄和按键接听时发送广播(接听并关闭led灯)
																增加免提键的挂断功能
									packages/apps/Dialer/		接收广播(接听并关闭led灯)
									packages/apps/PhoneCommon/	修改拨号盘的字体大小
									vendor/qcom/proprietary/	更换开机动画
									*/
					32, 2020-01-10 /*
									packages/apps/Dialer/		4G通话时默认打开拨号盘
									*/
					31, 2020-01-10 /*
									packages/apps/Dialer/		优化通话界面布局
									*/
					32, 2020-01-11 /*
									frameworks/base/			设置4G通话声音最大
									*/

	分支：s03_with_ethernet_ch /*带以太网2019-08-31*/
					1，2019-09-05 /*(暂时提交)
									device/qcom/common/
									device/qcom/msm8909/
									frameworks/base/
									frameworks/opt/net/ethernet/
									kernel/
									packages/apps/Launcher3/
									packages/apps/Settings/
									vendor/qcom/proprietary/
									*/
	分支：s03_4G /*同步分支s03_with_auto*/
					1，2019-10-14 /*合并s03_with_auto分支(日期：2019-10-14)*/
					2，2019-10-18 /* 
									device/qcom/msm8909/		添加纯4G launcher
									frameworks/base/			launcher添加WRITE_SECURE_SETTINGS权限
																按键默认纯4G配置
									packages/apps/Dialer/		去掉默认的快速拨号选项
									*/
					3, 2019-10-19 /*
									device/qcom/msm8909/		去除自注册apk
									frameworks/base/			默认打开设置->安全->未知来源
									vendor/qcom/proprietary/	去除自注册apk
									*/
					4, 2019-10-23 /*
									packages/apps/Dialer/		修改快捷拨号界面的启动方式-->AndroidManifest.xml(4G)
																增加快捷拨号功能，修改快捷拨号数量-->SpeedDialListActivity.java(4G)
																打开快速拨号选项-->DialerSettingsActivity.java(4G)
									packages/apps/Stk/			去掉联通的SIM服务apk（不然launcher——4G会崩溃）(4G)
									*/
					5， 2019-10-24 /*
									frameworks/base/			声明一个受保护的广播-->AndroidManifest.xml(4G)
																增加4G_launcher apk的权限-->DefaultPermissionGrantPolicy.java(4G)
																没有设置快捷号码时按下快捷拨号发送广播-->PhoneWindowManager.java(4G)
									packages/inputmethods/LatinIME	去除android默认的输入法
									*/
					6， 2019-10-28 /*
									frameworks/base/			跟换默认壁纸(4G)
									*/
					7， 2019-10-29 /*
									hardware/qcom/camera/
									kernel/
									vendor/qcom/proprietary/	新板子摄像头修改(以后的版本都使用新板子后摄摄像头)
									packages/apps/Dialer/		修改拨号设置的提示音和震动点击没反应的现象-->AndroidManifest.xml
																增加功能：在launcher界面按数字键视为拨号-->DialtactsActivity.java(4G)
																同上-->DialpadFragment.java(4G)
																去除拨号测试apk-->Android.mk
									*/
					8, 2019-11-05 /*
									packages/apps/SnapdragonGallery	修复在骁龙图库编辑图片弹出的提示框不能取消的问题(BUG)
									*/
					9, 2019-11-12 /*已撤销
									frameworks/base/			修复开机时出现的概率触摸卡死(使用了自己编写的Launcher)
									*/
					10，2019-12-11	/*
									device/qcom/common/			修复TP卡死问题
									kernel/						修复TP卡死问题
									*/
					11，2019-12-12	/*
									device/qcom/common/			兼容TP(修改节点权限)
									hardware/qcom/camera/		兼容TP(判断是否有摄像头)
									kernel/						兼容TP(根据是否有摄像头调整TP方向)
									*/
					12，2019-12-28 /*(合并s03_with_auto分支：12-25,12-28)
									device/qcom/common/
									device/qcom/msm8909/
									frameworks/base/
									hardware/qcom/sensors/
									kernel/
									packages/apps/ContactsCommon/
									packages/apps/Dialer/
									packages/apps/Settings/
									packages/apps/WallpaperPicker/
									*/
					12，2019-12-28 /*
									frameworks/base/			4G的Launcher更换包名
									*/
					13，2019-12-30 /*
									packages/apps/DeskClock/	修改时钟小部件字体大小
									*/
					14，2019-12-31 /*
									frameworks/base/			更换默认壁纸
																按键功能优化
									packages/apps/Dialer/		增加快捷拨号4
																修复退出设置播出声音BUG
									*/
					15，2020-01-04 /*
									packages/apps/Dialer/		修复光标位置不对的问题
									*/
					16，2020-01-06 /*
									frameworks/base/			增加免提键的挂断功能
									packages/apps/PhoneCommon/	修改拨号盘的字体大小
									*/
					17，2020-01-07 /*
									frameworks/base/			手柄和按键接听时发送广播(接听并关闭led灯)
									packages/apps/Dialer/		接收广播(接听并关闭led灯)
									vendor/qcom/proprietary/	更换开机动画
									*/
					18, 2020-01-10 /*
									packages/apps/Dialer/		4G通话时默认打开拨号盘
									*/
					19, 2020-01-10 /*
									packages/apps/Dialer/		优化通话界面布局
									*/
					20, 2020-02-17 /*
									packages/apps/Dialer/		修复播放tone音时休眠唤醒不播放问题(修复退出设置播出声音BUG 引起的)
									*/
					21, 2020-02-17 /*
									packages/apps/Dialer/		优化连续按免提键概率出现不能关闭apk问题
									*/




	分支：s03_VOIP /*同步分支s03_with_auto*/
					1，2019-10-14 /*合并s03_with_auto分支(日期：2019-10-14)*/
					2, 2019-10-14 /*
									frameworks/base/			修改按键的设置
									*/
					3, 2019-10-21 /*
									device/qcom/msm8909/		去除自注册apk
									frameworks/base/			默认打开设置->安全->未知来源
									vendor/qcom/proprietary/	去除自注册apk
									*/
					4，2019-10-24 /*
									packages/inputmethods/LatinIME	去除android默认的输入法
									*/
					5, 2019-10-29 /*
									hardware/qcom/camera/
									kernel/
									vendor/qcom/proprietary/	新板子摄像头修改(以后的版本都使用新板子后摄摄像头)
									*/
					3，2019-10-29 /*
									frameworks/base/			修改按键的一个语法错误
									*/
					4, 2019-11-05 /*
									packages/apps/SnapdragonGallery	修复在骁龙图库编辑图片弹出的提示框不能取消的问题(BUG)
									*/
					5, 2019-11-12 /*已撤销
									frameworks/base/			修复开机时出现的概率触摸卡死(使用了自己编写的Launcher)
									*/
					6，2019-12-11	/*
									device/qcom/common/			修复TP卡死问题
									kernel/						修复TP卡死问题
									*/

	分支：s03_VOIP_army /*同步分支s03_VOIP*/
					1, 2019-10-29 /*合并s03_VOIP分支(日期：2019-10-29)*/
					2, 2019-10-29 /*
									frameworks/base/			在状态栏添加剩余电量百分比显示
									*/
					3，2019-10-29 /*
									frameworks/base/			修改按键的一个语法错误
									*/
					4, 2019-11-04 /*临时提交
									build/					(提交)
									device/qcom/msm8909/	(提交)
									frameworks/base/		(提交)
									packages/apps/Dialer/	(提交)
									packages/apps/Settings/	(提交)
									vendor/qcom/proprietary/(提交)
									*/
					5, 2019-11-05 /*
									packages/apps/SnapdragonGallery	修复在骁龙图库编辑图片弹出的提示框不能取消的问题(BUG)
									*/
					6, 2019-11-12 /*已撤销
									frameworks/base/			修复开机时出现的概率触摸卡死(使用了自己编写的Launcher)
									*/
					7,2019-11-14 /*
									vendor/qcom/proprietary/	修改开机动画
									*/
					8，2019-12-11	/*
									device/qcom/common/			修复TP卡死问题
									kernel/						修复TP卡死问题
									*/

	
	分支：s03_test /*用于测试 合并s03_with_auto分支(日期：2019-10-14)*/
					1, 2019-10-15 /*
									frameworks/base/			修改息屏前变暗时间	
									*/
					2, 2019-10-15 /*
									frameworks/base/			默认打开设置->安全->未知来源
									*/



8909旧模块提交记录：(s03_in分支)
1，2019-05-07

2，2019-05-16：/*
				移植SIMCOM模块补丁
				*/

3，2019-05-25：/*
				修复来电led闪烁问题，添加拨号前提醒拨号功能(连续的嘟嘟声)
				*/

4, 2019-05-30：/*
				增加手柄拿起，启动拨号APP，放下，关闭APP功能(主要修改了驱动，framework，和dialer)
				取消屏幕解锁功能*/

5, 2019-07-02：/*(合并msm8909分支2019-06-06的补丁)
				修复快捷拨号M1~M4,重播键连续按下出现的bug
				修复下拉状态栏的wifi信号强度与设置里wifi信号强度不同
				去除摄像头驱动的log
				修复拨号键按下拨号，拨号apk出现崩溃现象
				*/

7，2019-07-12  /*(合并msm8909分支2019-06-26，2019-07-03的补丁)
				build/						修改系统版本号(buildinfo.sh)
				device/						去除自注册apk
				frameworks/base/			恢复wifi连接时出现的x符号
				kernel/						优化了手柄键抬起放下的响应时间(sasin_gpio.c)
				packages/apps/Dialer		修改点击视频通话图标时免提图标显示错误(CallButtonFragment.java)
											修改通话apk的通讯录不能保存联系人的bug(DialtactsActivity.java)
				packages/apps/Settings/		在系统中增加S03SystemTest的SIM测试(AndroidManifest.xml)
											修改系统内核版本
				vendor/qcom/proprietary/	修改通话时喇叭和手柄的音频参数(原厂提供)(Handset_cal.acdb)(Speaker_cal.acdb)
											修改机器视频通话时接收不到数据的BUG(mct_pipeline.c)
											添加自注册apk，未打包到systemimage中
				*/

8，2019-09-20 /*(合并msm8909分支2019-07-03，2019-07-10，2019-08-16的补丁)

				*/

9，2019-09-20 /*(合并msm8909分支2019-09-06的补丁)

				*/
10,2019-11-14 /*
				(合并s03_with_auto分支2019-10-08的补丁)
				*/
11,2019-11-14 /*
				(合并s03_with_auto分支2019-10-09的补丁)
				*/
12,2019-11-14 /*
				(合并s03_with_auto分支2019-10-10的补丁)
				*/
13,2019-11-14 /*
				(合并s03_with_auto分支2019-10-14的补丁)
				*/


	分支：s03_in_with_ethernet /*合并之前的补丁*/

	1，2019-10-14 /*
						添加以太网功能
						在设置-->声音中增加通话声音音量调
						修改来电呼叫转移编辑框的退出方式
					*/
	2，2019-10-14 /*
						修改设置-->声音中通话声音的图标
					*/


	分支：s03_VOIP /*合并s03_in分支(日期：2019-11-14)*/

			1，2019-11-14 /*合并s03_in分支(日期：2019-11-14)*/

			2, 2019-11-14 /*
							(合并s03_VOIP分支2019-10-14的补丁) s03_VOIP分支:另一代码分支
							*/
			3, 2019-11-14 /*
							(合并s03_VOIP分支2019-10-21的补丁) s03_VOIP分支:另一代码分支
							*/
			4, 2019-11-14 /*
							(合并s03_VOIP分支2019-10-24的补丁) s03_VOIP分支:另一代码分支
							*/
			5, 2019-11-14 /*
							(合并s03_VOIP分支2019-10-29的补丁) s03_VOIP分支:另一代码分支
							*/
			6, 2019-11-14 /*
							(合并s03_VOIP分支2019-11-05的补丁) s03_VOIP分支:另一代码分支
							*/
			7, 2019-11-14 /*
							(合并s03_VOIP分支2019-11-12的补丁) s03_VOIP分支:另一代码分支
							*/

	分支：s03_VOIP_army /*合并s03_VOIP分支(日期：2019-11-14)*/

			1，2019-11-14 /*合并s03_in分支(日期：2019-11-14)*/

			2, 2019-11-14 /*
							(合并s03_VOIP_army分支2019-10-29的补丁) s03_VOIP_army分支:另一代码分支
							*/
			3, 2019-11-14 /*
							(合并s03_VOIP_army分支2019-11-04的补丁) s03_VOIP_army分支:另一代码分支
							*/
			4, 2019-11-15 /*
							增加百度输入法，谷歌浏览器，墨迹天气apk
							*/
			5, 2019-11-27 /*
							增加网卡功能
							*/
			6, 2019-11-27 /*
							优化dm9051驱动（网卡网速）
							去除拨号apk
							*/
			7, 2019-11-28 /*
							 优化以太网使其默认开启
							*/
			8, 2019-11-28 /*
							 添加VOIP Launcher，去除sim，流量功能
							*/
			9, 2019-12-02 /*
							 移植mtk的以太网应用，去除设置更多选项的热点和移动网络等
							 修改设备型号
							*/
			10, 2019-12-04 /*
							 取消设置中的无线，手机，振动，短信，SIM卡字样
							 去掉短信，音乐，视频，电子邮件，Chrome，录音机，文件管理，下载，墨迹天气，S03Test
							 增加插入网线系统不进入深度休眠功能
							 修复TP卡死问题
							*/
			11, 2019-12-05 /*
							 增加来电led灯闪烁（吴凯）
							 更新应用图标排列
							 修复视频会议手柄奔溃BUG
							*/
			12, 2019-12-10 /*
							去除以太网和noSIM图标(SignalClusterView.java)
							去除以太网快捷方式设置--->packages/apps/Settings/AndroidManifest.xml
							去除wifi快捷方式设置--->packages/apps/Settings/res/xml/shortcuts.xml
							去除主屏幕设置apk(Protips)
							*/
			12, 2019-12-11 /*
							统一手柄接口(陈工)
							*/
			13, 2019-12-11 /*
							撤销之前的TP卡死修改
							*/
			14, 2019-12-13 /*
							拔插网线状态栏显示图标
							*/
			15，2020-01-03 /*
							VOIP的apk更新
							*/



			   