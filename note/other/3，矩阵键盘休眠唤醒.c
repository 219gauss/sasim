diff --git a/Android/kernel/drivers/input/keyboard/matrix_keypad.c b/Android/kernel/drivers/input/keyboard/matrix_keypad.c
old mode 100644
new mode 100755
index 8357f51..e066133
--- a/Android/kernel/drivers/input/keyboard/matrix_keypad.c
+++ b/Android/kernel/drivers/input/keyboard/matrix_keypad.c
@@ -27,6 +27,7 @@
 #include <linux/of.h>
 #include <linux/of_gpio.h>
 #include <linux/of_platform.h>
+#include <linux/fb.h>
 
 struct matrix_keypad {
 	const struct matrix_keypad_platform_data *pdata;
@@ -38,11 +39,13 @@ struct matrix_keypad {
 	uint32_t last_key_state[MATRIX_MAX_COLS];
 	struct delayed_work work;
 	struct mutex lock;
+	struct notifier_block fb_notif;
 	bool scan_pending;
 	bool stopped;
 	bool gpio_all_disabled;
 };
 
+static int suspend_system = 0;
 /*
  * NOTE: normally the GPIO has to be put into HiZ when de-activated to cause
  * minmal side effect when scanning other columns, here it is configured to
@@ -176,6 +179,12 @@ static irqreturn_t matrix_keypad_interrupt(int irq, void *id)
 {
 	struct matrix_keypad *keypad = id;
 
+	if(suspend_system) {
+			suspend_system = 0;
+			input_report_key(keypad->input_dev, KEY_WAKEUP, 1);
+			input_report_key(keypad->input_dev, KEY_WAKEUP, 0);
+	}
+
 	mutex_lock(&keypad->lock);
 
 	/*
@@ -467,6 +476,24 @@ matrix_keypad_parse_dt(struct device *dev)
 }
 #endif
 
+static int fb_notifier_callback(struct notifier_block *self, unsigned long event, void *data)
+{
+	struct fb_event *evdata = data;
+	int *blank;
+	
+	if (evdata && evdata->data && event == FB_EVENT_BLANK ){
+		blank = evdata->data;
+		printk("fb_notifier_callback blank=%d\n",*blank);
+		if (*blank == FB_BLANK_UNBLANK) {			
+			suspend_system = 0;
+		}else if (*blank == FB_BLANK_POWERDOWN) {
+			suspend_system = 1;
+		}
+	}
+
+	return 0;
+}
+
 static int matrix_keypad_probe(struct platform_device *pdev)
 {
 	const struct matrix_keypad_platform_data *pdata;
@@ -519,7 +546,14 @@ static int matrix_keypad_probe(struct platform_device *pdev)
 		__set_bit(EV_REP, input_dev->evbit);
 	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
 	input_set_drvdata(input_dev, keypad);
-
+	//add by pzp
+	input_set_capability(input_dev, EV_KEY, KEY_WAKEUP);
+	keypad->fb_notif.notifier_call = fb_notifier_callback;
+	err = fb_register_client(&keypad->fb_notif);
+	if (err) {
+		dev_err(&pdev->dev, "Unable to register fb_notifier: %d\n", err);
+	}
+	//printk("--------------matrix_keypad_probe %d---------------------\n", __LINE__);
 	err = matrix_keypad_init_gpio(pdev, keypad);
 	if (err)
 		goto err_free_mem;
@@ -546,7 +580,9 @@ static int matrix_keypad_remove(struct platform_device *pdev)
 	struct matrix_keypad *keypad = platform_get_drvdata(pdev);
 
 	device_init_wakeup(&pdev->dev, 0);
-
+	if(fb_unregister_client(&keypad->fb_notif)) {
+		dev_err(&pdev->dev, "Error occurred while unregistering fb_notifier.\n");
+	}
 	matrix_keypad_free_gpio(keypad);
 	mutex_destroy(&keypad->lock);
 	input_unregister_device(keypad->input_dev);
