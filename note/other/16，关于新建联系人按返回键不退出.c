问题：在拨号apk的通讯里界面，点击右下角的新增联系人时，发现点击取消，保存，返回键界面都不退出

经检查，发现是之前，修改启动apk时默认打开拨号盘这个功能时，导致的
之前不管ListsFragment是设置，通话记录还是通讯录，都默认打开拨号盘，
但通讯录右下角是"添加联系人"，设置，通话记录右下角是"打开拨号盘"

修改如下

    private int mposition = 0;

    @Override
    public void onPageSelected(int position) {	//当切换页面时该方法会被回调，position为切换完成时当前页面的下标
    	...

        //add by pzp
        mposition = position;	//保存下标位置
    }

    @Override
    protected void onResume() {
    	...

    	if (!mIsDialpadShown && (mposition != 2)) {	//如果不是第三页(通讯录)，显示拨号盘
        	showMyDialpad();
        }
    }

扩展：ViewPager滑动事件

ViewPager在处理滑动事件的时候要实现OnPageChangeListener接口，实现三个方法：

1，onPageScrollStateChanged(int state)
此方法是在状态改变的时候调用，其中state这个参数有三种状态：
SCROLL_STATE_DRAGGING（1）表示用户手指“按在屏幕上并且开始拖动”的状态（手指按下但是还没有拖动的时候还不是这个状态，只有按下并且手指开始拖动后log才打出。）
SCROLL_STATE_IDLE（0）滑动动画做完的状态。
SCROLL_STATE_SETTLING（2）在“手指离开屏幕”的状态。

2，onPageScrolled(int position, float positionOffset, int positionOffsetPixels)
当页面在滑动的时候会调用此方法，在滑动被停止之前，此方法回一直得到调用。其中三个参数的含义分别为：
position :当前页面，即你点击滑动的页面（从A滑B，则是A页面的position。官方说明：Position index of the first page currently being displayed. Page position+1 will be visible if positionOffset is nonzero.）
positionOffset:当前页面偏移的百分比
positionOffsetPixels:当前页面偏移的像素位置


3，onPageSelected(int position)
此方法是页面跳转完后得到调用，position是你当前选中的页面的Position（位置编号）(从A滑动到B，就是B的position)