/*
问题：在系统超时的时候，屏幕由亮变暗，发现屏幕在休眠前，有几秒的时间会停留在很暗很暗的界面

分析：机器本身在背光等级很小(如50)的时候，会出现屏幕几乎是黑的情况，
	  在系统超时的时候，屏幕由亮变暗，系统会停留几秒钟，告知用户屏幕快熄灭了

解决：取消屏幕由亮变暗，让系统时间一到直接休眠

*/


frameworks\base\services\core\java\com\android\server\power\PowerManagerService.java

    private int getScreenDimDurationLocked(int screenOffTimeout) {
		//add by pzp
		mMaximumScreenDimDurationConfig = 0;
		
        return Math.min(mMaximumScreenDimDurationConfig,
                (int)(screenOffTimeout * mMaximumScreenDimRatioConfig));
    }

/*这个函数是比较mMaximumScreenDimDurationConfig 和 mMaximumScreenDimRatioConfig变量的大小来决定使用哪个值来作为等待休眠时间
  返回的是屏幕由亮变暗到息屏的时间，返回0表示直接息屏，不等待
*/

    mMaximumScreenDimDurationConfig = resources.getInteger(
                com.android.internal.R.integer.config_maximumScreenDimDuration);


    <integer name="config_maximumScreenDimDuration">7000</integer>			//默认是7秒

    screenOffTimeout	//参数传进来的休眠时间


    mMaximumScreenDimRatioConfig = resources.getFraction(
                com.android.internal.R.fraction.config_maximumScreenDimRatio, 1, 1);

    <fraction name="config_maximumScreenDimRatio">20%</fraction>			//这个是取设置里休眠时间的20%

