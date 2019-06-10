/*
    这个来电接听流程要搞一下
*/


增加功能：机器在来电时led要闪烁

方法一：在framework里增加对来电的监听，

frameworks\base\services\core\java\com\android\server\policy\PhoneWindowManager.java
	
	import android.telephony.TelephonyManager;

	private TelephonyManager telephonyManager ;

    @Override
    public void init(Context context, IWindowManager windowManager,WindowManagerFuncs windowManagerFuncs) {
    	...
    	telephonyManager = (TelephonyManager)mContext.getSystemService(Context.TELEPHONY_SERVICE);
    	...
    	telephonyManager.listen(mPhoneStateListener, PhoneStateListener.LISTEN_CALL_STATE);
    	...
    }
    /*获取服务并启动监听*/


    SPhoneStateListener mPhoneStateListener = new SPhoneStateListener();

    private class SPhoneStateListener extends PhoneStateListener{

	    LedControlRunable mLedControlRunable = new LedControlRunable();
	    Thread mThread;

	    @Override
	    public void onCallStateChanged(int state, String incomingNumber) {

	        super.onCallStateChanged(state, incomingNumber);

	        switch (state) {
	            case TelephonyManager.CALL_STATE_IDLE:      // 电话挂断

	                if(mLedControlRunable.getledRunState()) {
	                    mLedControlRunable.setledRunState(false);
	                }
	                break;

	            case TelephonyManager.CALL_STATE_RINGING:   // 电话响铃

	                mLedControlRunable.setledRunState(true);
	                mThread = new Thread(mLedControlRunable);
	                mThread.start();
	                break;

	            case TelephonyManager.CALL_STATE_OFFHOOK:   // 来电接通 或者 去电，去电接通  但是没法区分

	                if(mLedControlRunable.getledRunState()) {
	                    mLedControlRunable.setledRunState(false);
	                }
	                break;
	        }
	    }
    };

    /*实现监听来电的逻辑，这里是启动一个线程去让灯闪烁*/


//出现的问题：使用这种方法后发现有个问题，在机器使用usb启动动的时候，来电灯能闪烁，当使用电源键启动的时候，来电灯没闪烁。(未知原因)


方法二：在拨号app里加监听

packages\apps\Dialer\InCallUI\src\com\android\incallui\TelecomAdapter.java

    LedControlRunable mLedControlRunable = new LedControlRunable();

    @Override
    public void setInCallService(InCallService inCallService) {
        mInCallService = inCallService;
        TelephonyManager tManager = (TelephonyManager) inCallService.getSystemService(Context.TELEPHONY_SERVICE);
        if(tManager.getCallState() == TelephonyManager.CALL_STATE_RINGING) {	//判断当前是否响铃，如果响铃则开启线程
            mLedControlRunable.setledRunState(true);
            (new Thread(mLedControlRunable)).start();
        }
        Log.e(TAG, "setInCallService");
    }

    然后再这些方法clearInCallService，answerCall，rejectCall，disconnectCall后加上

    	mLedControlRunable.setledRunState(false);	//停止线程里的循环

//使用此方法为发现上述问题

============================================================================================

/*两个方法使用的线程代码*/

    //add by pzp
    public void restoreDeviceValue(final File file, final String value) {
        if (file.exists()) {
            try {
                Log.d(TAG, "restoreDeviceValue value:"+value);
                RandomAccessFile rdf = null;
                rdf = new RandomAccessFile(file, "rw");
                rdf.writeBytes(value);
                rdf.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        } else {
            Log.e(TAG, "File:" + file + "not exists");
        }       
    }

    class LedControlRunable implements Runnable {
        LedControlRunable(){

        };
        private boolean ledRun = true;
        private boolean ledflag = true;
        public boolean getledRunState()
        {
            return ledRun;
        }
        public void setledRunState(boolean state) {
            ledRun = state;
        }
        @Override
        public void run() {
            while(ledRun) {
                restoreDeviceValue(new File("/sys/class/sasin_gpios/sasin_gpio92/ledctrl"), ledflag ? "0x1" : "0x0");
                ledflag = !ledflag;
                Log.e(TAG, "restoreDeviceValue ledflag:"+ledflag);
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {

                }
            }
            restoreDeviceValue(new File("/sys/class/sasin_gpios/sasin_gpio92/ledctrl"), "0x0");
        }
    }
