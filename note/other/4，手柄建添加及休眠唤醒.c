驱动位于该目录下
Z:\phy\sdk\msm8909_7.0_ch\Android\kernel\drivers\misc

sasin_gpio.c


修改Makefile
--- a/Android/kernel/drivers/misc/Makefile
+++ b/Android/kernel/drivers/misc/Makefile
@@ -68,3 +68,4 @@ obj-$(CONFIG_QPNP_MISC) += qpnp-misc.o
 obj-$(CONFIG_QCOM_LIQUID_DOCK) += qcom_liquid_dock.o
 obj-y                          += qcom/
 obj-$(CONFIG_UID_CPUTIME)      += uid_cputime.o
+obj-y                          += sasin_gpio.o
