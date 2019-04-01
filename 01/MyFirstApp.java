/*
1、编写程序实现对给定的 4 个整数从大到小的顺序排列。
2、编写程序求一元二次方程的根。
3、编写程序，输入一个字符，判断它是否为小写字母，如果是，将它转换成大写字母，否则，不转换。
4、输入 3 个正数，判断能否构成一个三角形。
5、编写程序，对输入的年、月、日，给出该天是该年的第多少天？
6、编写程序，从键盘输入一个 0~99999 之间的任意数，判断输入的数是几位数？
7、编写程序，给定一个学生成绩，给出相应等级：

			90~100 优秀
			80~89 良好
			70~79 中等
			60~69 及格
			0~59 不及格

8、编写程序，对输入的一个整数，按相反顺序输出该数。例如，输入为 3578，

输出为 8753。
9、用 while 循环，计算 1~200 之间所有 3 的倍数之和。
10、编写程序，输出 200~500 之间的所有素数。
11、编写程序解决“百钱买百鸡”问题。公鸡五钱一只，母鸡三钱一只，小鸡
一钱三只，现有百钱欲买百鸡，共有多少种买法？
12、使用循环语句输出下面的图形。

#

# # #

# # # # #

# # # # # # #

# # # # # # # # #

13、验证“鬼谷猜想”：对任意自然数，若是奇数，就对它乘以 3 再加 1；若是

偶数，就对它除以 2，这样得到一个新数，再按上述计算规则进行计算，一直进

行下去，最终必然得到 1。
14、编程求 1~10000 之间的所有“完全数”，完全数是该数的所有因子之和等于该数的数。
例如，6 的因子有 1、2、3，且 6=1+2+3，所以 6 是完全数。
15、一个整数的各位数字之和能被 9 整除，则该数也能被 9 整除。编程验证给

定的整数能否被 9 整除。
16、猴子吃桃问题。猴子第一天摘下若干个桃子，当时就吃了一半，还不过瘾，

就又吃了一个。第二天又将剩下的桃子吃掉一半，又多吃了一个。以后每天都吃

前一天剩下的一半零一个。到第 10 天在想吃的时候就剩一个桃子了,求第一天共

摘下来多少个桃子？
17、水仙花数是指一个 n 位数 ( n≥3 )，它的每个位上的数字的 n 次幂之和等

于它本身。（例如：1^3 + 5^3 + 3^3 = 153）。编程求出所有三位的水仙花数。
18、已知 XYZ+YZZ=532，其中，X、Y、Z 为数字，编程求出 X、Y 和 Z 的值。

19、古典问题：有一对兔子，从出生后第 3 个月起每个月都生一对兔子，小兔

子长到第三个月后每个月又生一对兔子，假如兔子都不死，问每个月的兔子总数

为多少？
20、将一个正整数分解质因数。例如：输入 90，打印出 90=2*3*3*5。
*/


import java.util.Scanner;
import org.apache.commons.lang3.ArrayUtils;

public class MyFirstApp{
	public static void main(String[] arge){
		MyFirstApp myFirstApp = new MyFirstApp();
		Scanner scanner = new Scanner(System.in); //键盘输入

		//System.out.println("请输入4个数字！");
		//myFirstApp.sort(scanner.nextInt(),scanner.nextInt(),scanner.nextInt(),scanner.nextInt());

		//System.out.println("请依次输入一元二次方程的三个系数！");
		//myFirstApp.solveEquations(scanner.nextInt(),scanner.nextInt(),scanner.nextInt());

		//System.out.println("请输入一个小写字母！");
		//myFirstApp.changeChar(scanner.nextLine());

		//System.out.println("请输入三角形的三条边！");
		//myFirstApp.triangle(scanner.nextInt(),scanner.nextInt(),scanner.nextInt());

		//System.out.println("请输入年月日！");
		//myFirstApp.getDay(scanner.nextInt(),scanner.nextInt(),scanner.nextInt());

		//System.out.println("请输入0~99999之间的数！");
		//myFirstApp.countSize(scanner.nextInt());

		//System.out.println("请输入学生分数！");
		//myFirstApp.getLever(scanner.nextInt());

		//System.out.println("请输入一个整数！");
		//myFirstApp.sort2(scanner.nextInt());

		//System.out.println("请输入一个整数！");
		//myFirstApp.sum(scanner.nextInt());

		//System.out.println("请输入两个整数！");
		//myFirstApp.suSu(scanner.nextInt(),scanner.nextInt());

		//System.out.println("请输入金额和鸡的数量！");
		//myFirstApp.buyChicken(scanner.nextInt(),scanner.nextInt());

		//System.out.println("请输入三角形的层数：");
		//myFirstApp.drawTriange(scanner.nextInt());

		//myFirstApp.guiGuGuess(scanner.nextInt());

		//System.out.println("请输入完全数的范围：");
		//myFirstApp.perfectNumber(scanner.nextInt(),scanner.nextInt());

		//System.out.println("请输入一个数字：");
		//myFirstApp.func(scanner.nextInt());

		//myFirstApp.peachEatting(scanner.nextInt());

		//myFirstApp.flower();

		myFirstApp.xyz();
	}

	void sort(int a,int b,int c,int d){
		int sortArray[] = {a,b,c,d};
		int len = sortArray.length;

		//冒泡排序
		for(int i=0; i<len-1; i++){
			for (int j=0; j<len-i-1; j++) {
				if(sortArray[j]<sortArray[j+1]){
					int temp = sortArray[j];
					sortArray[j] = sortArray[j+1];
					sortArray[j+1] = temp;
				}
			}
		}

		//打印
		System.out.print("从大到小排序为：");
		for(int i=0; i<len; i++){
			System.out.print(sortArray[i] + " ");
		}
		System.out.print("\n");
	}

	void solveEquations(int a,int b,int c){
		System.out.println("求解：一元二次方程:"+a+"x^2+"+b+"x+"+c+"=0");
		float x1,x2;

		System.out.println("b^2-4ac = "+(b*b-4*a*c));

		if ((b*b-4*a*c)>=0) {
			x1 = (float)(-b+Math.sqrt(b*b-4*a*c))/(2*a);
			x2 = (float)(-b-Math.sqrt(b*b-4*a*c))/(2*a);
			System.out.println("x1 = "+x1);
			System.out.println("x2 = "+x2);
		}else
		System.out.println("无解");
	}

	void changeChar(String ch){

		//String转char[]
		char[] chArray = ch.toCharArray();

		if (chArray.length ==1) {
			char a = chArray[0];

			if (a>=97 && a<=122) {
				a-=32;
				System.out.println("大写字符为："+ a);
			}else
			System.out.println("不是英文小写字母！");
		}else
			System.out.println("输入不符合要求！");
			
	}

	void triangle(int a,int b,int c){

		if(a>=0 || b>=0 || c>=0){
			if (a+b>c || a+c>b || b+c>a) {
				System.out.println("构成三角形");
			}else
			System.out.println("不能构成三角形");
		}else
		System.out.println("参数不对！");
	}

	void getDay(int _year,int _moon,int _day){
		int[] leapYear = {31,29,30,31,30,31,30,31,30,31,30,31};   //闰年
		int[] commonYear = {31,28,30,31,30,31,30,31,30,31,30,31};  //平年
		int allDay = 0;
		int remainDay = 0;

		int year = _year;
		int moon = _moon;
		int day = _day;

		if(moon>0 && moon<=12){ //判断月份是否符合
			if ((year%400==0) || (year%4==0 && year%400!=0)) {   //判断是否闰年
				if(day>0 && day<=leapYear[moon]){	//判断天数是否符合
					for (int i=1; i<moon; i++) {
						allDay +=leapYear[i];
					}
					allDay += day;
				}
				remainDay = 366 -allDay;
			}else{
				if(day>0 && day<=commonYear[moon]){
					for (int i=1; i<moon; i++) {
						allDay +=commonYear[i];
					}
					allDay += day;
				}
				remainDay = 366 -allDay;
			}
		}
		System.out.println(year + "年"+ moon + "月" + day + "日是第" + allDay + "天!");
		System.out.println(year + "年"+ moon + "月" + day + "日剩下" + remainDay + "天!");
	}

	void countSize(int aInt){
		if(aInt>=0 && aInt<=99999){
			String aString = Integer.toString(aInt);
			char[] aArray = aString.toCharArray();
			int len = aArray.length;
			System.out.println("这是个" + len + "位数!");
		}else
		System.out.println("数据不对!");
	}

	void getLever(int score){
		if (score>=0 && score<=100) {
			int lever = score/10;
			switch(lever){
				case 10:
				case 9:
					System.out.println("优秀!");
					break;
				case 8:
					System.out.println("良好!");
					break;
				case 7:
					System.out.println("中等!");
					break;
				case 6:
					System.out.println("及格!");
					break;
				case 5:
				case 4:
				case 3:
				case 2:
				case 1:
				case 0:
					System.out.println("不及格!");
					break;

			}
		}else
		System.out.println("分数不对!");
	}

	void sort2(int aInt){
		String aString = Integer.toString(aInt);
		char[] aArray = aString.toCharArray();
		ArrayUtils.reverse(aArray);

		System.out.print("反序输出：");
		for (int i=0; i<aArray.length; i++) {
			System.out.print(aArray[i]);
		}
		System.out.print("\n");
	}

	void sum(int aInt){
		int sum = 0;
		while(aInt!=0){
			if((aInt%3)==0)
				sum +=aInt;
			aInt--;
		}
		System.out.println("和为：" + sum);
	}

	void suSu(int aInt,int bInt){

		System.out.print("素数有：");
		for (int i=aInt; i<=bInt; i++) {
			for (int j=2; j<i; j++) {
				if (i%j != 0) {
					if (j==i-1) {
						System.out.print(i + " ");
					}	
				}else
					break;
			}
		}
		System.out.print("\n");
	}

	void buyChicken(int money,int chicken){
		int sum = 0;
		System.out.println("买法如下：");
		for (int bigChicken=0; bigChicken<=chicken; bigChicken++) {
			for (int midChicken=0; midChicken<=chicken; midChicken++) {
				for (int smallChicken=0; smallChicken<=chicken; smallChicken++) {
					if (bigChicken*5+midChicken*3+smallChicken == money) {
						//System.out.println("公鸡:" + bigChicken + " " + "母鸡:" + midChicken + " " + "小鸡:" + smallChicken);
						sum++;
					}
				}
			}
		}
		System.out.println("共有" + sum + "种买法");
	}

	void drawTriange(int lever){
		for (int i=1; i<=lever; i++) {
			if(((i+2)%2) != 0){
				for (int j=1; j<=i; j++) {
					System.out.print("*");
				}
				System.out.print("\n");
			}else
				System.out.print("\n");
		}
	}

	void guiGuGuess(int aInt){
		do{
			if (((aInt+2)%2) == 0) {
				aInt/=2;
			}else{
				aInt = aInt*3+1;
			}
		}while(aInt != 1);
		System.out.println("鬼谷猜想成立！");
	}

	void perfectNumber(int min,int max){

		int perfectNum = 0;
		int j;

		System.out.print("完全数有：");

		for (int i=min; i<=max; i++) {
			for (j=1; j<i; j++) {
				if ((i%j) == 0) {
					perfectNum +=j;
				}
			}

			if (perfectNum == i) {
				System.out.print(i + " ");
			}
			perfectNum = 0;
		}
		System.out.print("\n");
	}

	void func(int aInt){
		int[] remain = {0,0,0,0,0};
		int result,temp = aInt,i = 0;
		int sum = 0;

		for(i=0; i<remain.length; i++){
			result = temp/10;     //取整
			remain[i] = temp%10;  //取余
			temp = result;

			//System.out.println("result " + result);
			//System.out.println( "remain " + remain[i]);
			
			if (result == 0) {
				break;
			}
		}

		//System.out.println("i= " + i);

		for (int j=0; j<=i; j++) {
			//System.out.println("remain[j]= " + remain[j]);
			sum +=remain[j];
		}

		if ((sum%9 == 0) && (aInt%9 ==0)) {
			System.out.println("结论成立！");
		}
	}

	void peachEatting(int aInt){
		int sum = 1;
		for (int i=0; i<aInt-1; i++) {
			sum =(sum+1)*2;
		}
		System.out.println("桃子数：" + sum);
	}

	void flower(){
		int[] number = {0,0,0};

		for(int i=100; i<1000; i++){
			number[0] = i/100;     //百位
			number[1] = (i/10)%10;  //十位
			number[2] = i%10;

			if (Math.pow(number[0],3) + Math.pow(number[1],3) +Math.pow(number[2],3) == i) {
					System.out.println(i + "是水仙花数！" );
			}
		}
	}

	void xyz(){
		for (int x=0; x<532; x++) {
			for (int y=0; y<532; y++) {
				for (int z=0; z<532; z++) {
					if (x*100+y*10+z+y*100+z*10+z == 532) {
						System.out.println("x=" + x + " y=" + y + " z=" + z);
					}
				}
			}
		}
	}

	void rabbitNum(int moon){
		int rabbitSum = 2;

		for (int i=0; i<moon && i%3==0; i++) {
			rabbitSum	=(rabbitSum)*2;
		}
	}
}


