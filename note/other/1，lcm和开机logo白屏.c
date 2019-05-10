diff --git a/Android/bootable/bootloader/lk/target/msm8909/include/target/display.h b/Android/bootable/bootloader/lk/target/msm8909/include/target/display.h
index bc5fbe0..300f0ca 100755
--- a/Android/bootable/bootloader/lk/target/msm8909/include/target/display.h
+++ b/Android/bootable/bootloader/lk/target/msm8909/include/target/display.h
@@ -51,12 +51,16 @@ static struct gpio_pin bkl_gpio = {
   "msmgpio", 31, 3, 1, 0, 1
 };
 
-/*static struct gpio_pin enp_gpio = {
-  "msmgpio", 97, 3, 1, 0, 1
+static struct gpio_pin vccio_gpio = {
+  "msmgpio", 0, 3, 1, 0, 1
+};
+
+static struct gpio_pin enp_gpio = {
+  "msmgpio", 11, 3, 1, 0, 1
 };
 
 static struct gpio_pin enn_gpio = {
-  "msmgpio", 32, 3, 1, 0, 1
+  "msmgpio", 10, 3, 1, 0, 1
 };
 
 static struct gpio_pin te_gpio = {
@@ -65,7 +69,7 @@ static struct gpio_pin te_gpio = {
 
 static struct gpio_pin pwm_gpio = {
   0, 0, 0, 0, 0, 0
-};*/
+};
 
 /*---------------------------------------------------------------------------*/
 /* Target Physical configuration                                             */
diff --git a/Android/bootable/bootloader/lk/target/msm8909/oem_panel.c b/Android/bootable/bootloader/lk/target/msm8909/oem_panel.c
index 2ea4436..fd00cf9 100755
--- a/Android/bootable/bootloader/lk/target/msm8909/oem_panel.c
+++ b/Android/bootable/bootloader/lk/target/msm8909/oem_panel.c
@@ -50,6 +50,7 @@
 #include "include/panel_auo_cx_qvga_cmd.h"
 #include "include/panel_hx8394f_720p_video.h"*/
 #include "include/panel_cs400_272p_video.h"
+#include "include/panel_zs043_270p_video.h"
 
 #define DISPLAY_MAX_PANEL_DETECTION 1
 //#define ILI9806E_FWVGA_VIDEO_PANEL_POST_INIT_DELAY 68
@@ -87,6 +88,7 @@ enum {
 	AUO_CX_QVGA_CMD_PANEL,
 	HX8394F_720P_VIDEO_PANEL,*/
 	CS400_272P_VIDEO_PANEL,
+	ZS043_270P_VIDEO_PANEL,
 	UNKNOWN_PANEL
 };
 
@@ -108,6 +110,7 @@ static struct panel_list supp_panels[] = {
 	{"auo_cx_qvga_cmd", AUO_CX_QVGA_CMD_PANEL},
 	{"hx8394f_720p_video", HX8394F_720P_VIDEO_PANEL},*/
 	{"cs400_272p_video", CS400_272P_VIDEO_PANEL},
+	{"zs043_270p_video", ZS043_270P_VIDEO_PANEL},
 };
 
 static uint32_t panel_id;
@@ -393,26 +396,26 @@ static int init_panel_data(struct panel_struct *panelstruct,
 					hx8394f_720p_video_timings, TIMING_SIZE);
 		pinfo->mipi.signature = HX8394F_720P_VIDEO_SIGNATURE;
 		break;*/
-	case CS400_272P_VIDEO_PANEL:
-		panelstruct->paneldata	  = &cs400_272p_video_panel_data;
-		panelstruct->panelres	  = &cs400_272p_video_panel_res;
-		panelstruct->color	  = &cs400_272p_video_color;
-		panelstruct->videopanel   = &cs400_272p_video_video_panel;
-		panelstruct->commandpanel = &cs400_272p_video_command_panel;
-		panelstruct->state	  = &cs400_272p_video_state;
-		panelstruct->laneconfig   = &cs400_272p_video_lane_config;
+	case ZS043_270P_VIDEO_PANEL:
+		panelstruct->paneldata    = &zs043_270p_video_panel_data;
+		panelstruct->panelres     = &zs043_270p_video_panel_res;
+		panelstruct->color        = &zs043_270p_video_color;
+		panelstruct->videopanel   = &zs043_270p_video_video_panel;
+		panelstruct->commandpanel = &zs043_270p_video_command_panel;
+		panelstruct->state        = &zs043_270p_video_state;
+		panelstruct->laneconfig   = &zs043_270p_video_lane_config;
 		panelstruct->paneltiminginfo
-					 = &cs400_272p_video_timing_info;
+					= &zs043_270p_video_timing_info;
 		panelstruct->panelresetseq
-					 = &cs400_272p_video_reset_seq;
-		panelstruct->backlightinfo = &cs400_272p_video_backlight;
+					 = &zs043_270p_video_reset_seq;
+		panelstruct->backlightinfo = &zs043_270p_video_backlight;
 		pinfo->mipi.panel_cmds
-					= cs400_272p_video_on_command;
+					= zs043_270p_video_on_command;
 		pinfo->mipi.num_of_panel_cmds
-					= CS400_272P_VIDEO_ON_COMMAND;
+					= ZS043_270P_VIDEO_ON_COMMAND;
 		memcpy(phy_db->timing,
-				cs400_272p_video_timings, TIMING_SIZE);
-		pinfo->mipi.signature = CS400_272P_VIDEO_SIGNATURE;
+					zs043_270p_video_timings, TIMING_SIZE);
+		//pinfo->mipi.signature = CS400_272P_VIDEO_SIGNATURE;
 		break;		
 	case UNKNOWN_PANEL:
 	default:
@@ -478,8 +481,8 @@ int oem_panel_select(const char *panel_name, struct panel_struct *panelstruct,
 				break;
 			default:
 				//panel_id = HX8394D_720P_VIDEO_PANEL;
-				dprintf(CRITICAL, "    lcd_id == cs400	\n");
-				panel_id = CS400_272P_VIDEO_PANEL;
+				dprintf(CRITICAL, "    lcd_id == zs043	\n");
+				panel_id = ZS043_270P_VIDEO_PANEL;
 		}
 		break;
 	/*case HW_PLATFORM_QRD:
diff --git a/Android/bootable/bootloader/lk/target/msm8909/target_display.c b/Android/bootable/bootloader/lk/target/msm8909/target_display.c
index 5985fa8..ea2a0fd 100755
--- a/Android/bootable/bootloader/lk/target/msm8909/target_display.c
+++ b/Android/bootable/bootloader/lk/target/msm8909/target_display.c
@@ -322,14 +322,21 @@ int target_panel_reset(uint8_t enable, struct panel_reset_sequence *resetseq,
 			}
 		}
 
-		if (pinfo->mipi.use_enable_gpio) {
+		//if (pinfo->mipi.use_enable_gpio) {
+			gpio_tlmm_config(vccio_gpio.pin_id, 0,
+				vccio_gpio.pin_direction, vccio_gpio.pin_pull,
+				vccio_gpio.pin_strength,
+				vccio_gpio.pin_state);
+
+			gpio_set(vccio_gpio.pin_id, 2);
+					
 			gpio_tlmm_config(enable_gpio.pin_id, 0,
 				enable_gpio.pin_direction, enable_gpio.pin_pull,
 				enable_gpio.pin_strength,
 				enable_gpio.pin_state);
 
 			gpio_set(enable_gpio.pin_id, 2);
-		}
+		//}
 
 		gpio_tlmm_config(reset_gpio.pin_id, 0,
 				reset_gpio.pin_direction, reset_gpio.pin_pull,
@@ -347,8 +354,10 @@ int target_panel_reset(uint8_t enable, struct panel_reset_sequence *resetseq,
 		}
 	} else if(!target_cont_splash_screen()) {
 		gpio_set(reset_gpio.pin_id, 0);
-		if (pinfo->mipi.use_enable_gpio)
+		//if (pinfo->mipi.use_enable_gpio) {
 			gpio_set(enable_gpio.pin_id, 0);
+			gpio_set(vccio_gpio.pin_id, 0);
+		//}
 
 		if ((hw_id == HW_PLATFORM_QRD) && (hw_subtype == 0)) {
 			target_id = board_target_id();
diff --git a/Android/kernel/arch/arm/boot/dts/qcom/msm8909-mtp.dtsi b/Android/kernel/arch/arm/boot/dts/qcom/msm8909-mtp.dtsi
index c574c58..8fd4284 100755
--- a/Android/kernel/arch/arm/boot/dts/qcom/msm8909-mtp.dtsi
+++ b/Android/kernel/arch/arm/boot/dts/qcom/msm8909-mtp.dtsi

@@ -342,26 +392,27 @@
 };
 
 #include "dsi-panel-cs400-272p-video.dtsi"
+#include "dsi-panel-zs043-270p-video.dtsi"
 
 &mdss_mdp {
 	qcom,mdss-pref-prim-intf = "dsi";
 };
 
-&dsi_cs400_272p_video {
-    qcom,mdss-dsi-bl-pmic-control-type = "bl_ctrl_pwm";
-    qcom,mdss-dsi-bl-pmic-pwm-frequency = <100>;
-    qcom,mdss-dsi-bl-pmic-bank-select = <0>;
-    qcom,mdss-dsi-pwm-gpio = <&pm8909_mpps 2 0>;
-    qcom,cont-splash-enabled;
+&dsi_zs043_270p_video {
+	qcom,mdss-dsi-bl-pmic-control-type = "bl_ctrl_pwm";
+	qcom,mdss-dsi-bl-pmic-pwm-frequency = <100>;
+	qcom,mdss-dsi-bl-pmic-bank-select = <0>;
+	qcom,mdss-dsi-pwm-gpio = <&pm8909_mpps 2 0>;
+	qcom,cont-splash-enabled;
 };
 
 &mdss_dsi0 {
-	qcom,dsi-pref-prim-pan = <&dsi_cs400_272p_video>;
+	qcom,dsi-pref-prim-pan = <&dsi_zs043_270p_video>;
 	pinctrl-names = "mdss_default", "mdss_sleep";
 	pinctrl-0 = <&mdss_dsi_active &mdss_te_active>;
 	pinctrl-1 = <&mdss_dsi_suspend &mdss_te_suspend>;
+	qcom,platform-enable-gpio = <&msm_gpio 32 0>;
 	qcom,platform-reset-gpio = <&msm_gpio 25 0>;
-    qcom,mdss-dsi-lcd-en-gpio = <&msm_gpio 32 0>;
 	qcom,platform-bklight-en-gpio = <&msm_gpio 31 0>;
 };
 
diff --git a/Android/kernel/drivers/input/touchscreen/gsl9xx/gsl_ts_driver.c b/Android/kernel/drivers/input/touchscreen/gsl9xx/gsl_ts_driver.c
index bdbf111..27b48c0 100755
--- a/Android/kernel/drivers/input/touchscreen/gsl9xx/gsl_ts_driver.c
+++ b/Android/kernel/drivers/input/touchscreen/gsl9xx/gsl_ts_driver.c
@@ -43,6 +43,7 @@
 #include "gsl_ts_driver.h"
 
 #define DEBUG 1
+//#define IS8909
 
 
 #ifdef GSL_REPORT_POINT_SLOT
@@ -1663,8 +1664,15 @@ static void gsl_report_point(struct input_dev *idev, struct gsl_touch_info *cinf
 			input_mt_slot(idev, cinfo->id[i] - 1);
 			input_report_abs(idev, ABS_MT_TRACKING_ID, cinfo->id[i]-1);
 			input_report_abs(idev, ABS_MT_TOUCH_MAJOR, GSL_PRESSURE);
+
+			#ifdef IS8909
+			input_report_abs(idev, ABS_MT_POSITION_X, 480 - cinfo->x[i]);
+			input_report_abs(idev, ABS_MT_POSITION_Y, 272 - cinfo->y[i]);
+			#else
+			//带A
 			input_report_abs(idev, ABS_MT_POSITION_X, cinfo->x[i]);
 			input_report_abs(idev, ABS_MT_POSITION_Y, cinfo->y[i]);
+			#endif
 			//input_report_abs(idev, ABS_MT_POSITION_X, cinfo->y[i]);
 			//input_report_abs(idev, ABS_MT_POSITION_Y, 272-cinfo->x[i]);			
 			input_report_abs(idev, ABS_MT_WIDTH_MAJOR, 1);
@@ -1674,8 +1682,15 @@ static void gsl_report_point(struct input_dev *idev, struct gsl_touch_info *cinf
 			input_report_key(idev, BTN_TOUCH, 1);
 			input_report_abs(idev, ABS_MT_TRACKING_ID, cinfo->id[i]-1);
 			input_report_abs(idev, ABS_MT_TOUCH_MAJOR, GSL_PRESSURE);
+
+			#ifdef IS8909
+			input_report_abs(idev, ABS_MT_POSITION_X, 480 - cinfo->x[i]);
+			input_report_abs(idev, ABS_MT_POSITION_Y, 272 - cinfo->y[i]);
+			#else
+			//带A
 			input_report_abs(idev, ABS_MT_POSITION_X, cinfo->x[i]);
-			input_report_abs(idev, ABS_MT_POSITION_Y, cinfo->y[i]);	
+			input_report_abs(idev, ABS_MT_POSITION_Y, cinfo->y[i]);
+			#endif		
 			input_report_abs(idev, ABS_MT_WIDTH_MAJOR, 1);
 			input_mt_sync(idev);		
 		#endif
@@ -2591,8 +2606,8 @@ static int gsl_ts_probe(struct i2c_client *client, const struct i2c_device_id *i
 	}
 
 	/*request irq */
-	//err = request_irq(client->irq, gsl_ts_interrupt, IRQF_TRIGGER_FALLING, client->name, ts_data);
-	err = request_irq(client->irq, gsl_ts_interrupt, IRQF_TRIGGER_HIGH, client->name, ts_data);
+	err = request_irq(client->irq, gsl_ts_interrupt, IRQF_TRIGGER_FALLING, client->name, ts_data);
+	//err = request_irq(client->irq, gsl_ts_interrupt, IRQF_TRIGGER_HIGH, client->name, ts_data);
 	if (err < 0) {
 		dev_err(&client->dev, "gsl_g185d_probe: request irq failed\n");
 		GTP_INFO("request_irq error\n");
