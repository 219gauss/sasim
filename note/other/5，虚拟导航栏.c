https://www.jianshu.com/p/adeb5a2ccfbf


显示虚拟导航栏（在左边）
Z:\phy\sdk\qualcomm\device\qcom\msm8909\system.prop

--- a/Android/device/qcom/msm8909/system.prop
+++ b/Android/device/qcom/msm8909/system.prop
@@ -168,6 +168,9 @@ audio.dolby.ds2.enabled=true
 #property to change touch screen resolution
 persist.sys.synaptics_dsx.qhd=false
 
+#NavigationBar Display
+qemu.hw.mainkeys=0
+
 #HWUI properties
 ro.hwui.text_large_cache_height=2048
 
 删除out目录重新编译，重新刷机后发现只有一个home键


--- a/Android/frameworks/base/packages/SystemUI/src/com/android/systemui/statusbar/phone/NavigationBar
+++ b/Android/frameworks/base/packages/SystemUI/src/com/android/systemui/statusbar/phone/NavigationBar
@@ -115,7 +115,8 @@ public class NavigationBarInflaterView extends FrameLayout implements TunerServi
 
     private void inflateChildren() {
         removeAllViews();
-        mRot0 = (FrameLayout) mLayoutInflater.inflate(R.layout.navigation_layout, this, false);
+        //mRot0 = (FrameLayout) mLayoutInflater.inflate(R.layout.navigation_layout, this, false);
+        mRot0 = (FrameLayout) mLayoutInflater.inflate(R.layout.navigation_layout_rot90, this, false);
         mRot0.setId(R.id.rot0);
         addView(mRot0);
         mRot90 = (FrameLayout) mLayoutInflater.inflate(R.layout.navigation_layout_rot90, this,

3个虚拟键有了

出现个bug：由于没有做强制APP横屏操作，导致打开某些竖屏APP时，出现导航栏只有一个home键


解决：强制所有APP横屏
--- a/Android/frameworks/base/services/core/java/com/android/server/wm/WindowManagerService.java
+++ b/Android/frameworks/base/services/core/java/com/android/server/wm/WindowManagerService.java
@@ -3856,7 +3856,8 @@ public class WindowManagerService extends IWindowManager.Stub
     boolean updateOrientationFromAppTokensLocked(boolean inTransaction) {
         long ident = Binder.clearCallingIdentity();
         try {
-            int req = getOrientationLocked();
+            //int req = getOrientationLocked();
+                       int req = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE; //add by pzp
             if (req != mLastOrientation) {
                 mLastOrientation = req;
                 //send a message to Policy indicating orientation change to take


================================================================
未用到：

eng版本出现屏幕红框现象：

其实这个红框不是android的bug，把编译模式从eng改成user就可以了，
红框只是eng模式debug的时候提示你系统busy，红框越久说明你的系统或应用运行卡顿越久，
这个时候系统可能会挂掉，仅此而已！

解决：
persist.sys.strictmode.disable=true

或者：（未尝试）
注释掉文件frameworks\base\services\java\com\android\server\wm\WindowManagerService.java的函数
showStrictModeViolation()的如下行：

mStrictModeFlash.setVisibility(on);

================================================================