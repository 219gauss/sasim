/*

PhoneWindowManager.java								DialtactsActivity.java				DialpadFragment.java
		(按键监听)										(拨号APP界面)						(拨号盘界面)


		抬起	启动apk
手柄键：
		放下	发一个广播			------>			收到广播：finish();
				(com.android.dialer.finish)



		获取电话号码																handleDialButtonPressed()
																					点击拨号盘拨号后，关闭APP
重播键：拨打电话															

		发一个广播								------>								收到广播：activity.finish();
		(DialpadFragment.phone.key)


																					
																					监听：
																						来电响铃：关闭连续 嘟嘟声
																									mToneGenerator.stopTone();

																						挂断(没响铃和通话走这个状态)：播放连续 嘟嘟声
																									mToneGenerator.startTone(ToneGenerator.TONE_SUP_DIAL);

																						通话：通话时关闭apk
																									activity.finish();
*/

frameworks\base\services\core\java\com\android\server\policy\PhoneWindowManager.java

    case KeyEvent.KEYCODE_DIAL:	//重播
        if(down){

            //  sendBoradcastReciver -> finish DialactsActivity
             Intent intent = new Intent("com.android.dialer.dialpad.DialpadFragment.phone.key");
             mContext.sendBroadcast(intent);
        }
        break;


     case KeyEvent.KEYCODE_HOLD:	//手柄
        boolean stats = getHookStatus();
        ...
        } else {

            if (stats) {
                // up start apk
                Intent intent = mContext.getPackageManager().getLaunchIntentForPackage("com.android.dialer");
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                mContext.startActivity(intent);

            } else{
                //down send broadcase to finish apk
                Intent intent =new Intent("com.android.dialer.finish");
                mContext.sendBroadcast(intent);
            } 
        }
        break;

packages\apps\Dialer\src\com\android\dialer\DialtactsActivity.java
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		...
		IntentFilter intentFilter = new IntentFilter("com.android.dialer.finish");
		registerReceiver(mFinishReceiver, intentFilter);
	}

	@Override
    public void onDestroy() {
		if (mFinishReceiver!=null) {
			unregisterReceiver(mFinishReceiver);  
		}
		super.onDestroy();
    }

	BroadcastReceiver mFinishReceiver = new BroadcastReceiver(){	//广播的具体实现
	@Override
		public void onReceive(Context context, Intent intent) {
			finish();
		}
	};

packages\apps\Dialer\src\com\android\dialer\dialpad\DialpadFragment.java

    //add by pzp
	private TelephonyManager mTelephonyManager;
	private PhoneStateListener mPhoneStateListener = new PhoneStateListener() {
		public void onCallStateChanged(int state, String incomingNumber) {
			switch (state){
				case TelephonyManager.CALL_STATE_RINGING:   //响铃
					if(mToneGenerator != null){
						mToneGenerator.stopTone();
					}
					break;
				case TelephonyManager.CALL_STATE_IDLE:	//挂断
					if(mToneGenerator != null){
						mToneGenerator.startTone(ToneGenerator.TONE_SUP_DIAL);
					}
					break;
				case TelephonyManager.CALL_STATE_OFFHOOK:	//通话
					final DialtactsActivity activity = (DialtactsActivity) getActivity();
					activity.finish();
					break;
			}
		}
	};

	@Override
	public void onCreate(Bundle state) {
		...
		//add by pzp
		IntentFilter intentFilter = new IntentFilter(mPhoneKeyAction);
		getContext().registerReceiver(mDialerReceiver, intentFilter);
		//listen the call state
		mTelephonyManager = getTelephonyManager();
		mTelephonyManager.listen(mPhoneStateListener, PhoneStateListener.LISTEN_CALL_STATE);
	}

	@Override
	public void onDestroy() {
		...
		if (mDialerReceiver!=null) {	//注销广播
			getContext().unregisterReceiver(mDialerReceiver);
		}
		((Context) getActivity()).unregisterReceiver(mCallStateReceiver);

		//取消来电的电话状态监听服务
		if (mTelephonyManager != null && mPhoneStateListener != null) {
			mTelephonyManager.listen(mPhoneStateListener, PhoneStateListener.LISTEN_NONE);
		}
	}

	private void handleDialButtonPressed() {
		...
		final DialtactsActivity activity = (DialtactsActivity) getActivity();
		activity.finish();
	}


	//add by pzp
	private final String mPhoneKeyAction = "com.android.dialer.dialpad.DialpadFragment.phone.key";
	BroadcastReceiver mDialerReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			if (intent.getAction().equals(mPhoneKeyAction)) {
				Log.e(TAG, "mDialerReceiver,mDialerReceiver");
				final DialtactsActivity activity = (DialtactsActivity) getActivity();
				activity.finish();
			}
		}
	};
