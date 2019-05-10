
kernel部分：

1，添加摄像头驱动：
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\media\platform\msm\camera_v2\sensor\gc2145_8909.c
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\media\platform\msm\camera_v2\sensor\gc2145_8909.h

2，修改Makefile：
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\media\platform\msm\camera_v2\sensor\Makefile

obj-$(CONFIG_GC2145_8909) += gc2145_8909.o

3，修改Kconfig：
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\media\platform\msm\camera_v2\Kconfig

config GC2145_8909
	bool "Sensor GC2145_8909 (YUV .3M)"
		depends on MSMB_CAMERA
		---help---
		GC2145_8909 is GalaxyCore YUV sensor. It supports VGA preview
		and snapshot. The snapshot resolution shall be
		1600 * 1200. It does not support auto focus. It supports
		few special effects like mono


4，在配置文件中添加摄像头的宏
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\configs\msm8909_defconfig
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\configs\msm8909-1gb_defconfig
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\configs\msm8909-1gb-perf_defconfig

CONFIG_GC2145_8909=y


5，添加摄像头设备节点：
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\boot\dts\qcom\msm8909-camera-sensor-mtp.dtsi

s03是在i2c_3中添加的

&i2c_3 {
	...
	qcom,camera@60 {
			compatible = "qcom,gc2145_8909";
			reg = <0x60 0x0>;
			qcom,slave-id = <0x78 0xf0 0x2145>;
			qcom,csiphy-sd-index = <0>;
			qcom,csid-sd-index = <0>;
			qcom,mount-angle = <0>;
			qcom,sensor-name = "gc2145_8909";
			cam_vdig-supply = <&pm8909_l2>;
			cam_vana-supply = <&pm8909_l17>;
			cam_vio-supply = <&pm8909_l6>;
			cam_vaf-supply = <&pm8909_l10>;
			qcom,cam-vreg-name = "cam_vdig", "cam_vio", "cam_vana",
								"cam_vaf";
			qcom,cam-custom-vreg-name = "cam_vdig", "cam_vio", "cam_vana",
								"cam_vaf";
			qcom,cam-vreg-type = <0 1 0 0>;
			qcom,cam-vreg-min-voltage = <1200000 0 2850000 0>;
			qcom,cam-vreg-max-voltage = <1200000 0 2850000 0>;
			qcom,cam-vreg-op-mode = <200000 0 80000 100000>;
			pinctrl-names = "cam_default", "cam_suspend";
			pinctrl-0 = <&cam_sensor_mclk1_default &cam_sensor_front_default>;
			pinctrl-1 = <&cam_sensor_mclk1_sleep &cam_sensor_front_sleep>;
			gpios = <&msm_gpio 27 0>,
				<&msm_gpio 28 0>,
				<&msm_gpio 33 0>;
			qcom,gpio-reset = <1>;
			qcom,gpio-standby = <2>;
			qcom,gpio-req-tbl-num = <0 1 2 >;
			qcom,gpio-req-tbl-flags = <1 0 0 >;
			qcom,gpio-req-tbl-label = "CAMIF_MCLK",
					"CAM_RESET1",
					"CAM_STANDBY";
			qcom,csi-lane-assign = <0x0004>;
			qcom,csi-lane-mask = <0x18>;
			qcom,sensor-position = <1>;
			qcom,sensor-mode = <1>;
			qcom,cci-master = <0>;
			status = "ok";
			clocks = <&clock_gcc clk_mclk1_clk_src>,
					<&clock_gcc clk_gcc_camss_mclk1_clk>;
			clock-names = "cam_src_clk", "cam_clk";
		};
	...
}

Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\boot\dts\qcom\msm8909.dtsi

确定有i2c_3节点

/ {
	...
	aliases {
		...
	    i2c5 = &i2c_5; /* I2c5 cntroller device */
		i2c3 = &i2c_3; /* I2C3 controller */
		i2c1 = &i2c_1; /* I2C1 controller */
		//i2c2 = &i2c_2; /* I2C2 NFC qup2 device */
		//i2c4 = &i2c_4; /* I2C4 controller device */
	};
}

&soc {
	i2c_3: i2c@78b7000 { /* BLSP1 QUP3 */
		compatible = "qcom,i2c-msm-v2";
		#address-cells = <1>;
		#size-cells = <0>;
		reg-names = "qup_phys_addr";
		reg = <0x78b7000 0x1000>;
		interrupt-names = "qup_irq";
		interrupts = <0 97 0>;
		clocks = <&clock_gcc clk_gcc_blsp1_ahb_clk>,
		         <&clock_gcc clk_gcc_blsp1_qup3_i2c_apps_clk>;
		clock-names = "iface_clk", "core_clk";
		qcom,clk-freq-out = <400000>;
		qcom,clk-freq-in  = <19200000>;
		pinctrl-names = "i2c_active", "i2c_sleep";
		pinctrl-0 = <&i2c_3_active>;
		pinctrl-1 = <&i2c_3_sleep>;
		qcom,noise-rjct-scl = <0>;
		qcom,noise-rjct-sda = <0>;
		dmas = <&dma_blsp1 8 64 0x20000020 0x20>,
			<&dma_blsp1 9  32 0x20000020 0x20>;
		dma-names = "tx", "rx";
		qcom,master-id = <86>;
	};
}

Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\boot\dts\qcom\msm8909-pinctrl.dtsi

&soc {
	pmx_i2c_3 {
                    /* CLK, DATA */
		qcom,pins = <&gp 29>, <&gp 30>;
		qcom,num-grp-pins = <2>;
		qcom,pin-func = <1>;
		label = "pmx_i2c_3";

		i2c_3_active: i2c_3_active {
			drive-strength = <2>; /* 2 MA */
			bias-disable = <0>; /* No PULL */
		};

		i2c_3_sleep: i2c_3_sleep {
			drive-strength = <2>; /* 2 MA */
			bias-pull-down; /* PULL DOWN */
		};
	};
}


vendor部分：

添加sensor libs代码
vendor\qcom\proprietary\mm-camera\mm-camera2\media-controller\modules\sensors\sensor_libs\gc2145_8909\Android.mk
vendor\qcom\proprietary\mm-camera\mm-camera2\media-controller\modules\sensors\sensor_libs\gc2145_8909\gc2145_8909_lib.c

添加sensor
vendor\qcom\proprietary\mm-camera\mm-camera2\media-controller\modules\sensors\module\sensor_init.c

	#define BOARD_SENSORS \
		...	
	  "gc2145_8909",
	#else

vendor\qcom\proprietary\common\config\device-vendor.mk

	MM_CAMERA += libmmcamera_gc2145_8909
	
