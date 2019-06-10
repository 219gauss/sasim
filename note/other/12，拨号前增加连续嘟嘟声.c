/*
在拨号前增加连续的嘟嘟声，在拨号和通话时，声音取消。
思路：在启动APP之后，去判断拨号盘的文本框是否有号码填入，如果没有就播放音乐，没有就关闭音乐


*/
packages\apps\Dialer\src\com\android\dialer\DialtactsActivity.java

	private void showDialpadFragment(boolean animate) {	//当打开拨号盘时，判断文本框是否有内容，有就播放音乐
		if (mDialpadFragment.mDigits.getText().toString().equals("")) {
            mDialpadFragment.mToneGenerator.startTone(ToneGenerator.TONE_SUP_DIAL);
        }else{
            mDialpadFragment.mToneGenerator.stopTone();
        }
        ...
	}

    public void hideDialpadFragment(boolean animate, boolean clearDialpad) {	//隐藏拨号盘时要关闭声音
    	mDialpadFragment.stopTone();
    	...
    }	


packages\apps\Dialer\src\com\android\dialer\dialpad\DialpadFragment.java
//这个文件是弹出拨号盘Fragment的文件

    public ToneGenerator mToneGenerator;

    ...

    public void afterTextChanged(Editable input) {	//当文本框的内容发生变化时，该函数会被回调
    	...
    	//add by pzp 190517
        Log.i("pzp","start Dialpad");
        if (input.toString().equals("")) {	//如果内容为空，打开声音
            Log.i("pzp","play");
            mToneGenerator.startTone(ToneGenerator.TONE_SUP_DIAL);
        }else{
            Log.i("pzp","stop");
            mToneGenerator.stopTone();
        }
        ...
    }

    @Override
    public boolean onKey(View view, int keyCode, KeyEvent event) {
        if (view.getId() == R.id.digits) {
            if (keyCode == KeyEvent.KEYCODE_ENTER) {
                handleDialButtonPressed();

                //add by pzp 190517
                if (mDigits.getText().toString().equals("")) {
                    mToneGenerator.startTone(ToneGenerator.TONE_SUP_DIAL);
                }else{
                    mToneGenerator.stopTone();
                }

                return true;
            } else if (keyCode == KeyEvent.KEYCODE_REDIAL&& event.getAction() == KeyEvent.ACTION_DOWN) {
                Log.d("liao","start redial");
                handleDialButtonPressed();

                //add by pzp 190517
                if (mDigits.getText().toString().equals("")) {	//如果这里不加判断的话，当再次按下拨号键时，机器不播放声音
                    mToneGenerator.startTone(ToneGenerator.TONE_SUP_DIAL);
                }else{
                    mToneGenerator.stopTone();
                }

                return true;
            }

        }
        return false;
    }

    public void stopTone() {
        // if local tone playback is disabled, just return.
        if (!mDTMFToneEnabled) {
            return;
        }
        synchronized (mToneGeneratorLock) {
            if (mToneGenerator == null) {
                Log.w(TAG, "stopTone: mToneGenerator == null");
                return;
            }
            mToneGenerator.stopTone();
        }
    }

问题：之后测出一个问题，发现拨打电话被挂断，机器挂断返回拨号盘时，没有嘟嘟声

解决：在onResume方法之后添加一个判断，判断拨号盘是否有内容
packages\apps\Dialer\src\com\android\dialer\dialpad\DialpadFragment.java

    @Override
    public void onResume() {
        ...
        //add by pzp 190517
        if (mDigits.getText().toString().equals("")) {
             mToneGenerator.startTone(ToneGenerator.TONE_SUP_DIAL);
        }else{
             mToneGenerator.stopTone();
        }
    }

问题：在来电响铃时，连续嘟嘟声没有关闭

解决：看13篇，大致就是加一个响铃状态的监听
