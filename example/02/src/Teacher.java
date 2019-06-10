
package pzp;

public class Teacher extends People{
	private String subject = null;

	public Teacher(String subject,int high,int weigh){
		super(high,weigh);
		this.subject = subject;
	}

	void setSubject(String subject){
		this.subject = subject;
	}

	String getSubject(){
		return this.subject;
	}
}
