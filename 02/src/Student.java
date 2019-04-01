/**		Student[] student = new Student[2];              //声明两个对象
		student[0] = new Student("",124,"","","","");    //实例化对象（赋值）

		Student student = new Student();                 //声明对象并实例化

*/


package pzp;

public class Student extends People{

	private String name = null;
	private int age = 0;
	private String gender = null;
	private String phone = null;
	private String address = null;
	private String email = null;

	public Student(){
		super(0,0);
	}
	
	public Student(String name,int age,String gender,String phone,String address,String email,int high,int weigh){
		super(high,weigh); //子类的构造方法第一行一定是父类的构造方法
		this.name = name;
		this.age = age;
		this.gender = gender;
		this.phone = phone;
		this.address = address;
		this.email = email;
	}

	void setName(String name){
		this.name = name;
	}

	String getName(){
		return this.name;
	}

	void setAge(int age){
		this.age = age;
	}

	int getAge(){
		return this.age;
	}

	void setGender(String gender){
		this.gender = gender;
	}

	String getGender(){
		return this.gender;
	}

	void setPhone(String phone){
		this.phone = phone;
	}

	String getPhone(){
		return this.phone;
	}	

	void setAddress(String address){
		this.address = address;
	}

	String getAddress(){
		return this.address;
	}

	void setEmail(String email){
		this.email = email;
	}

	String getEmail(){
		return this.email;
	}

	public void eat(){
		System.out.println("吃");
	}

	public void drink(){
		System.out.println("喝");
	}

	public void play(){
		System.out.println("玩");
	}

	public void sleep(){
		System.out.println("睡");
	}
}

