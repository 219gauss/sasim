
充电过程：(分四个阶段)

1，Trickle Charging(涓流充电)
	当电池电压低于3.2V时，进入涓流充电阶段，该阶段分两个部分。
	1，电池电压低于2.8V，电流为90mA
	2，电池电压大于2.8V小于3.2V时，充电电流为450mA
	由硬件控制这个充电行为

2，Constant Current Charging(恒流充电)
	软件系统再这个阶段启动，它控制着充电行为，usb充电电流为450mA，交流充电为1440mA

3，Constant Voltage Charging(恒压充电)
	当电池电压达到VDD试进入这个阶段

4，Charging Termination(充电结束)
	pm8909没有ADC检测电流功能，所以它是基于电池容量来判断充电状态，

设置关机电压：kernel\arch\arm\boot\dts\qcom\batterydata-palladium.dtsi
	qcom,v-cutoff-uv = <3400000>;