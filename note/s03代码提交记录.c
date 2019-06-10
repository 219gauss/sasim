

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
					4, 2019-06-10  合并msm8909分支(2019-06-06 的提交)



8909旧模块提交记录：
1，2019-05-07
2，2019-05-16：移植SIMCOM模块补丁
3，2019-05-25：修复来电led闪烁问题，添加拨号前提醒拨号功能(连续的嘟嘟声)
4, 2019-05-30：增加手柄拿起，启动拨号APP，放下，关闭APP功能(主要修改了驱动，framework，和dialer)
			   取消屏幕解锁功能
			   