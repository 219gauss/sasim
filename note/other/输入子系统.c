
	//系统服务启动
	public static void main(String[] args) {
        new SystemServer().run();
    }

    private void run() {
    	...
    	try {
    		...
            startOtherServices();
        } 
        ...
    }

    private void startOtherServices() {
    	...
    	inputManager = new InputManagerService(context);
    	...
    	ServiceManager.addService(Context.INPUT_SERVICE, inputManager);
    	...
    	inputManager.setWindowManagerCallbacks(wm.getInputMonitor());
        inputManager.start();
        ...
    }
