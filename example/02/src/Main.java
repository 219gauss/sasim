package pzp;
import pzp.*;

public class Main{

	public static void main(String[] args) {
		Student[] student = new Student[2];
		student[0] = new Student("小王",20,"男","123","##","@1",175,70);
		student[1] = new Student("小李",21,"女","456","**","@2",175,70);

		System.out.println(student[0].getName());
		System.out.println(student[1].getName());

		//student[0].setHigh(170);
		System.out.println(student[0].getHigh());
	}
}

