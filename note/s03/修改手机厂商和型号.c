
--- a/tools/buildinfo.sh
+++ b/tools/buildinfo.sh
@@ -26,8 +26,10 @@ fi
 if [ -n "$AB_OTA_UPDATER" ] ; then
   echo "ro.build.ab_update=$AB_OTA_UPDATER"
 fi
-echo "ro.product.model=$PRODUCT_MODEL"
-echo "ro.product.brand=$PRODUCT_BRAND"
+#echo "ro.product.model=$PRODUCT_MODEL"
+echo "ro.product.model=EÂ·XUN G303"
+#echo "ro.product.brand=$PRODUCT_BRAND"
+echo "ro.product.brand=NJX"
 echo "ro.product.name=$PRODUCT_NAME"
 echo "ro.product.device=$TARGET_DEVICE"
 echo "ro.product.board=$TARGET_BOOTLOADER_BOARD_NAME"
@@ -44,7 +46,8 @@ echo "ro.product.cpu.abilist=$TARGET_CPU_ABI_LIST"
 echo "ro.product.cpu.abilist32=$TARGET_CPU_ABI_LIST_32_BIT"
 echo "ro.product.cpu.abilist64=$TARGET_CPU_ABI_LIST_64_BIT"
 
-echo "ro.product.manufacturer=$PRODUCT_MANUFACTURER"
+#echo "ro.product.manufacturer=$PRODUCT_MANUFACTURER"
+echo "ro.product.manufacturer=NJX"
 if [ -n "$PRODUCT_DEFAULT_LOCALE" ] ; then
   echo "ro.product.locale=$PRODUCT_DEFAULT_LOCALE"
 fi
