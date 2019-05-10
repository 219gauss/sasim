
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\boot\dts\qcom\msm8909-mtp.dtsi
在soc节点中添加

	matrix_keypad {
		compatible = "gpio-matrix-keypad";
		debounce-delay-ms = <5>;
		col-scan-delay-us = <2>;
		linux,wakeup;
		pinctrl-names = "matrix_keypad_active","matrix_keypad_suspend";
		pinctrl-0 = <&matrix_keypad_active>;
		pinctrl-1 = <&matrix_keypad_suspend>;

		row-gpios = <&msm_gpio 65 0
			     &msm_gpio 16  0
			     &msm_gpio 8 0
			     &msm_gpio 9 0
			     &msm_gpio 10 0>;

		col-gpios = <&msm_gpio 11 0
			     &msm_gpio 95 0
			     &msm_gpio 36 0
			     &msm_gpio 58 0
			     &msm_gpio 110 0>;

		linux,keymap = <0x000001ed
				0x010001ef
				0x020001e8
				0x030001ec
				0x040001ee
				0x0001006c
				0x0101006a
				0x02010067
				0x0301000e
				0x0401001c
				0x0002020b
				0x0102000a      
				0x02020007
				0x03020004
				0x040201e7
				0x0003000b
				0x01030009
				0x02030006
				0x03030003
				0x040301e6
				0x0004020a
				0x01040008
				0x02040005
				0x03040002
				0x040401e5>;
		keypad,num-rows = <5>;
		keypad,num-columns = <5>;
	};



再添加一个子节点

&tlmm_pinmux {
	matrix_keypad_gpio {
		qcom,pins = <&gp 65>, <&gp 16>, <&gp 8>, <&gp 9>, <&gp 10>,
					<&gp 11>, <&gp 95>, <&gp 36>, <&gp 58>, <&gp 110>;
		qcom,num-grp-pins = <10>;
		qcom,pin-func = <0>;
		label = "matrix_keypad_gpio";
		matrix_keypad_active: active {
			drive-strength = <8>;
			bias-pull-down;
		};
		matrix_keypad_suspend: suspend {
			drive-strength = <8>;	
			bias-pull-down;
		};
	};
};

Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\arch\arm\configs\msm8909-1gb_defconfig
项目的配置文件里添加宏

CONFIG_KEYBOARD_MATRIX=y