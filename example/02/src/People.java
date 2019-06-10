
package pzp;

public class People{
	private int high = 0;
	private int weigh = 0;

	public People(int high,int weigh){
	this.high = high;
	this.weigh = weigh;
	}

	void setHigh(int high){
		this.high = high;
	}

	int getHigh(){
		return this.high;
	}

	void setWeigh(int weigh){
		this.weigh = weigh;
	}

	int getWeigh(){
		return this.weigh;
	}
}
