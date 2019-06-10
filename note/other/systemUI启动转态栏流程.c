/*
参考：  https://www.jianshu.com/p/0ab1279465fa
        http://www.bokezhi.com/486.html

*/


	
	//当核心的系统服务启动完，会调用ActivityManagerService.systemReady方法通知AMS系统准备就绪
	mActivityManagerService.systemReady(new Runnable() {
		...
		Trace.traceBegin(Trace.TRACE_TAG_SYSTEM_SERVER, "StartSystemUI");
	                try {
	                    startSystemUi(context);
	                } catch (Throwable e) {
	                    reportWtf("starting System UI", e);
	                }
	    ...
	}


	static final void startSystemUi(Context context) {
        Intent intent = new Intent();
        intent.setComponent(new ComponentName("com.android.systemui",
                    "com.android.systemui.SystemUIService"));	//设置SystemUIService为启动目标
        intent.addFlags(Intent.FLAG_DEBUG_TRIAGED_MISSING);
        //Slog.d(TAG, "Starting service: " + intent);
        context.startServiceAsUser(intent, UserHandle.SYSTEM);
    }

    public class SystemUIService extends Service {

	    @Override
	    public void onCreate() {
	        super.onCreate();
	        ((SystemUIApplication) getApplication()).startServicesIfNeeded();
	    }
	}

	public void startServicesIfNeeded() {
        startServicesIfNeeded(SERVICES);
    }

    private final Class<?>[] SERVICES = new Class[] {	//这个数组定义了运行与SystemUIService中的子服务列表
    		...
            com.android.systemui.power.PowerUI.class,	//用于监控系统剩余电量并显示低电警告
            com.android.systemui.media.RingtonePlayer.class,	//向其他应用提供铃声播放功能
            ...
    };


    private void startServicesIfNeeded(Class<?>[] services) {

    	...
        final int N = services.length;
        for (int i=0; i<N; i++) {
            Class<?> cl = services[i];
            if (DEBUG) Log.d(TAG, "loading: " + cl);
            try {
                Object newService = SystemUIFactory.getInstance().createInstance(cl);
                mServices[i] = (SystemUI) ((newService == null) ? cl.newInstance() : newService);	//实例化服务并存于mServices中
            } catch (IllegalAccessException ex) {
                throw new RuntimeException(ex);
            } catch (InstantiationException ex) {
                throw new RuntimeException(ex);
            }

            mServices[i].mContext = this;
            mServices[i].mComponents = mComponents;
            if (DEBUG) Log.d(TAG, "running: " + mServices[i]);
            mServices[i].start();	//设置Context，并运行服务

            ...
        }
        ...
    }

//SystemUIService就是一个容器，它启动时，会实例化定义在SERVICES列表中的各个服务，在调用start方法后，便不做其他事情

	public class SystemBars extends SystemUI implements ServiceMonitor.Callbacks {
		...
		@Override
    	public void start() {
        	if (DEBUG) Log.d(TAG, "start");
        		mServiceMonitor = new ServiceMonitor(TAG, DEBUG,
                	mContext, Settings.Secure.BAR_SERVICE_COMPONENT, this);
        		mServiceMonitor.start();  // will call onNoService if no remote service is found
    	}
    	...
	}

	//如果服务没启动将调onNoService方法,(这是个回调函数，由系统直接调用)

	@Override
    public void onNoService() {
        if (DEBUG) Log.d(TAG, "onNoService");
        createStatusBarFromConfig();  // fallback to using an in-process implementation
    }

    private void createStatusBarFromConfig() {
        ...
        //config_statusBarComponent的值为 com.android.systemui.statusbar.phone.PhoneStatusBar
        final String clsName = mContext.getString(R.string.config_statusBarComponent);	//1，获取字符串com.android.systemui.statusbar.phone.PhoneStatusBar
        ...
        Class<?> cls = null;
        try {
            cls = mContext.getClassLoader().loadClass(clsName);	//通过反射，获取com.android.systemui.statusbar.phone.PhoneStatusBar类
        } catch (Throwable t) {
            ...
        }
        try {
            mStatusBar = (BaseStatusBar) cls.newInstance();	//通过反射机制得到BaseStatusBar对象(BaseStatusBar是PhoneStatusBar的父类)
        } catch (Throwable t) {								//从cls里面获取子类实例，然后强转成父类类型
            ...
        }
        mStatusBar.mContext = mContext;
        mStatusBar.mComponents = mComponents;
        mStatusBar.start();	//先调用子类的方法，最终调回父类BaseStatusBar的start
        ...
    }

    @Override
    public void start() {
    	...
    	super.start(); // calls createAndAddWindows()	//调用父类的方法
    	...
    	startKeyguard();	//初始化了锁屏相关，以后后空再看
    }

    public void start() {
        mWindowManager = (WindowManager)mContext.getSystemService(Context.WINDOW_SERVICE);
        mWindowManagerService = WindowManagerGlobal.getWindowManagerService();
        mDisplay = mWindowManager.getDefaultDisplay();
        mDevicePolicyManager = (DevicePolicyManager)mContext.getSystemService(
                Context.DEVICE_POLICY_SERVICE);

        mNotificationData = new NotificationData(this);

        mAccessibilityManager = (AccessibilityManager)
                mContext.getSystemService(Context.ACCESSIBILITY_SERVICE);

        mDreamManager = IDreamManager.Stub.asInterface(
                ServiceManager.checkService(DreamService.DREAM_SERVICE));
        mPowerManager = (PowerManager) mContext.getSystemService(Context.POWER_SERVICE);

        ...
        //实例化了许多systemui常用的对象，服务，Manager，Observer等等，(具体没看)
        ...
        createAndAddWindows();	//创建并添加视图
      	...
    }

    protected abstract void createAndAddWindows();	//是一个抽象方法，去调用了子类的方法，即PhoneStatusBar的createAndAddWindows():


    //PhoneStatusBar类的
    @Override
    public void createAndAddWindows() {
        addStatusBarWindow();
    }

    private void addStatusBarWindow() {
        makeStatusBarView();	//重点，创建StatusBarView
        mStatusBarWindowManager = new StatusBarWindowManager(mContext);
        mRemoteInputController = new RemoteInputController(mStatusBarWindowManager,
                mHeadsUpManager);
        mStatusBarWindowManager.add(mStatusBarWindow, getStatusBarHeight());	//添加
    }


    protected PhoneStatusBarView makeStatusBarView() {
    	...
    	inflateStatusBarWindow(context);
    	...
    }

    //顶部状态栏布局
    protected void inflateStatusBarWindow(Context context) {
        mStatusBarWindow = (StatusBarWindowView) View.inflate(context,R.layout.super_status_bar, null);
    }


    //加载这个布局文件(包含所有状态栏布局的"超级状态栏")
    <com.android.systemui.statusbar.phone.StatusBarWindowView
	    ...
	    <include layout="@layout/status_bar"/>	//状态栏布局
	    ...
	    <include layout="@layout/status_bar_expanded" />	//下拉状态栏时的布局
	    ...
	</com.android.systemui.statusbar.phone.StatusBarWindowView>


	/*
						状态栏
		通知图标(左边)			系统图标+电池电量+时间(右边)
	*/
	<com.android.systemui.statusbar.phone.PhoneStatusBarView
		...
	    <LinearLayout android:id="@+id/status_bar_contents">	//状态栏内容
	        
	        <com.android.systemui.statusbar.AlphaOptimizedFrameLayout android:id="@+id/notification_icon_area"/>	//状态栏左边通知的图标

	        <com.android.keyguard.AlphaOptimizedLinearLayout android:id="@+id/system_icon_area">	//状态栏右边系统的图标

	            <include layout="@layout/system_icons" />	//系统图标

	            <com.android.systemui.BatteryLevelTextView android:id="@+id/battery_level_text"/>	//电池电量显示

	            <com.android.systemui.statusbar.policy.Clock android:id="@+id/clock"/>	//时间显示

	        </com.android.keyguard.AlphaOptimizedLinearLayout>
	    </LinearLayout>
	    ...
	</com.android.systemui.statusbar.phone.PhoneStatusBarView>




	//下拉状态栏

	<com.android.systemui.statusbar.phone.NotificationPanelView >
		...
	    <include
	        layout="@layout/keyguard_status_view"/>	//下拉状态栏的时间显示

	    <com.android.systemui.statusbar.phone.NotificationsQuickSettingsContainer
	        android:id="@+id/notification_container_parent">

	        <com.android.systemui.AutoReinflateContainer
	            android:id="@+id/qs_auto_reinflate_container"/>

	        <com.android.systemui.statusbar.stack.NotificationStackScrollLayout
	            android:id="@+id/notification_stack_scroller"/>	//下拉状态栏的消息框

	        <include
	            layout="@layout/keyguard_status_bar"/>	//下拉状态栏时的消息栏
	        ...
	    </com.android.systemui.statusbar.phone.NotificationsQuickSettingsContainer>

	    <include
	            layout="@layout/keyguard_bottom_area"/>
	    ...
	</com.android.systemui.statusbar.phone.NotificationPanelView><!-- end of sliding panel -->



