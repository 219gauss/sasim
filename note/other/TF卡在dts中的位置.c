
在kernel\arch\arm\boot\dts\qcom\msm8909-mtp.dtsi文件中

&sdhc_2 {
	 #address-cells = <0>;
	interrupt-parent = <&sdhc_2>;
	interrupts = <0 1 2>;
	#interrupt-cells = <1>;
	interrupt-map-mask = <0xffffffff>;
	interrupt-map = <0 &intc 0 125 0
			1 &intc 0 221 0
			2 &msm_gpio 38 0>;
	interrupt-names = "hc_irq", "pwr_irq", "status_irq";
	cd-gpios = <&msm_gpio 38 0x1>;

	vdd-supply = <&pm8909_l11>;
	qcom,vdd-voltage-level = <1800000 2950000>;
	qcom,vdd-current-level = <15000 400000>;

	vdd-io-supply = <&pm8909_l12>;
	qcom,vdd-io-voltage-level = <1800000 2950000>;
	qcom,vdd-io-current-level = <200 50000>;

	pinctrl-names = "active", "sleep";
	pinctrl-0 = <&sdc2_clk_on &sdc2_cmd_on &sdc2_data_on &sdc2_cd_on>;
	pinctrl-1 = <&sdc2_clk_off &sdc2_cmd_off &sdc2_data_off &sdc2_cd_off>;

	status = "ok";
};
