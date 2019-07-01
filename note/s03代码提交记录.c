

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



8909旧模块提交记录：
1，2019-05-07
2，2019-05-16：移植SIMCOM模块补丁
3，2019-05-25：修复来电led闪烁问题，添加拨号前提醒拨号功能(连续的嘟嘟声)
4, 2019-05-30：增加手柄拿起，启动拨号APP，放下，关闭APP功能(主要修改了驱动，framework，和dialer)
			   取消屏幕解锁功能
			   